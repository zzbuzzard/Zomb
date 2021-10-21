#include "pch.h"
#include "SpecialController.h"
#include "Special.h"
#include "IncludeSpecials.h"
#include "Levels.h"
#include "Controller.h"

#include "Media.h"

#include <fstream>

#define pli std::pair<LEVEL, int>

enum SPECIAL
{
	S_ELECTRIC_BURST,
	S_DASH,
	S_DASH_SHOTGUN,
	S_ELECTRIC_SHOTGUN,
	S_DASH_SHOTGUN_MULTIPLE,
};

SPECIAL equippedSpecial = (SPECIAL)0;

specialType specialTypes[NUM_SPECIALS] = {
	specialType("Electric burst", "Fires a burst of electric shots",
		{}, T_ZAP, 0, pli(L_NONE, 0)),
	specialType("Dash", "Dash forwards in the direction you're moving",
		{S_ELECTRIC_BURST}, T_ICON_FEET, 500, pli(L_HILLS, 5)),
	specialType("Shotgun dash", "Fires a shotgun of damaging spikes then dashes away",
		{S_DASH}, T_RED_SPIKE, 2000, pli(L_HILLS, 10)),
	specialType("Electric shotgun", "Fires electric shots outwards in every direction",
		{S_ELECTRIC_BURST}, T_SCIENCE_ZOMB, 400, pli(L_CAVE, 5)),
	specialType("Multiple shotgun dash", "Fires multiple shotguns while dashing",
		{S_DASH_SHOTGUN}, T_CAVE_FG, 10000, pli(L_HILLS, 15)),
};

Special *getSpecialFrom(SPECIAL a) {
	switch (a) {
	case S_ELECTRIC_BURST:
		return new SElectricBurst();
	case S_DASH:
		return new SDash();
	case S_DASH_SHOTGUN:
		return new SDashShotgun();
	case S_DASH_SHOTGUN_MULTIPLE:
		return new SDashMultipleShotgun();
	case S_ELECTRIC_SHOTGUN:
		return new SElectricBurst();
	}
	return nullptr;
}

bool specialsUnlocked[NUM_SPECIALS];

void loadUnlockedSpecials() {
	specialsUnlocked[0] = true;
	for (int i = 1; i < NUM_SPECIALS; i++) {
		specialsUnlocked[i] = false;
	}
	std::ifstream fin("specials");
	if (fin.good()) {
		int x; fin >> x;
		equippedSpecial = (SPECIAL)x;
		//std::cout << "Special equipped: " << std::get<0>(specialTypes[x]) << std::endl;

		int a;
		int i = 0;
		while (true) {
			fin >> a;
			if (a == -1) break;
			if (a == 1) {
				//std::cout << "Special unlocked: " << std::get<0>(specialTypes[i]) << std::endl;
				specialsUnlocked[i] = true;
			}
			i++;
		}
	}
}

bool specialUnlocked(SPECIAL specialIndex) {
	if (specialIndex < 0 || specialIndex >= NUM_SPECIALS) return false;
	return specialsUnlocked[specialIndex];
}

bool specialEquipped(SPECIAL specialIndex) {
	return specialIndex == equippedSpecial;
}

void saveUnlockedSpecials() {
	std::ofstream fout("specials");
	fout << equippedSpecial << " ";
	for (int i = 0; i < NUM_SPECIALS; i++) fout << (specialsUnlocked[i] ? 1 : 0) << " ";
	fout << "-1";
}

const specialType &getSpecialType() {
	return specialTypes[equippedSpecial];
}

Special *getSpecial() {
	return getSpecialFrom(equippedSpecial);
}

void equipSpecial(SPECIAL equip) {
	equippedSpecial = equip;
	saveUnlockedSpecials();
}

void buySpecial(SPECIAL equip) {
	int cost = std::get<4>(specialTypes[equip]);

	if (getCoins() >= cost) {
		addCoins(-cost);
		specialsUnlocked[equip] = true;
		saveUnlockedSpecials();
	}
}

// 1 is a list of requirements
// 4 is (level, wave)
bool isUnlockable(SPECIAL specialIndex) {
	const auto &vec = std::get<2>(specialTypes[specialIndex]);
	for (const SPECIAL &mustBeBought : vec) {
		if (!specialUnlocked(mustBeBought)) return false;
	}
	const auto &pair = std::get<5>(specialTypes[specialIndex]);
	if (pair.first != L_NONE)
		if (getMaxWave(pair.first) < pair.second) return false;
	return true;
}

SpecialController::SpecialController() {

}

SpecialController::~SpecialController() {

}