#include "pch.h"
#include "Inventory.h"
#include "Player.h"
#include "GameState.h"

#include "IncludeWeapons.h"

#include <fstream>

#define pb std::pair<int, bool>

Inventory::Inventory()
{
	loadInventory();
}


Inventory::~Inventory()
{
}

bool Inventory::inventoryFull() {
	int spaces = INV_MAX_SIZE;
	// count non-equipped items
	for (const auto &i : items) {
		if (!i.second) spaces--;
	}
	return spaces == 0;
}

void Inventory::addToInventory(ITEMS itemType) {
	if (!inventoryFull()) {
		items.push_back(pb(itemType, false));
		saveInventory();
	}
}


void Inventory::applyStatusEffects(Player *p) {
	for (const auto &i : items) {
		if (i.second) {
			switch (i.first) {
			//case I_PARALYSIS_DEFENDER:
			//	p->applyStatus(StatusEffect::SLOW, -10);
			//	break;
			}
		}
	}
}

Weapon *Inventory::getWeapon() {
	for (const auto &i : items) {
		if (i.second) {
			ITEMS itemType = (ITEMS)i.first;
			if (std::get<2>(itemTypes[itemType]) == 0) {
				return getWeaponFrom(itemType);
			}
		}
	}
	return nullptr;
}

Weapon *Inventory::getWeaponFrom(ITEMS type) {
	switch (type) {
	case I_PISTOL:
		return new Pistol();
	case I_RUSTY_PISTOL:
		return new RustyPistol();
	case I_SHOTGUN:
		return new Shotgun();
	case I_ELECTRIC_STAFF:
		return new ElectricStaff();
	case I_EARTH_STAFF:
		return new EarthStaff();
	}
	return nullptr;
}

const std::vector<std::pair<int, bool> > &Inventory::getItems() {
	return items;
}

Stats Inventory::getEquipmentStats() {
	Stats s = Stats();
	std::vector<bool> done = std::vector<bool>(5, false);
	for (const auto &i : items) {
		if (i.second) {
			int loc = std::get<2>(itemTypes[i.first]);
			if (loc == -1) continue;
			if (done[loc]) continue;
			done[loc] = true;
			s.addStats(std::get<3>(itemTypes[i.first]));
		}
	}
	return s;
}

void Inventory::saveInventory() {
	std::ofstream fout("inventory");
	for (const auto &i : items) {
		fout << i.first << " " << (i.second ? 1 : 0) << " ";
	}
	fout << -1 << " " << -1;
}

void Inventory::loadInventory() {
	std::ifstream fin("inventory");
	int a, b;
	if (fin.good()) {
		while (true) {
			fin >> a >> b;
			if (a == -1) break;
			items.push_back(pb(a, b == 1));
		}
	}
	else {
		items = { pb(I_RUSTY_PISTOL, true), pb(I_RIPPED_SHIRT, true) };
	}
	//items = { pb(I_RUSTY_PISTOL, true), pb(I_RIPPED_SHIRT, true) };
	//items = { pb(I_PISTOL, false), pb(I_RUSTY_PISTOL, true), pb(I_CAP, true), pb(I_CARDBOARD_BOX, true), pb(I_CHAINMAIL, false), pb(I_CONCRETE_BOX, false),
	//	pb(I_ELECTRIC_STAFF, false), pb(I_HEAVY_ARMOUR, false), pb(I_INTRICATE_HAT, false), pb(I_INTRICATE_ROBE, false),
	//pb(I_OLD_SHOES, false), pb(I_ROBE, false), pb(I_SCOPE, false), pb(I_TRAINERS, false), pb(I_WOODEN_SHIELD, false),
	//pb(I_SHOTGUN, false), pb(I_SLIME_ARMOUR, false), pb(I_SLIMY_SHOES, false), pb(I_SHIRT, false), pb(I_VIKING_HELMET, false) };
}

void Inventory::sellItem(int index) {
	item t = itemTypes[items[index].first];
	int c = std::get<5>(t);
	items.erase(items.begin()+index);
	saveInventory();
	addCoins(c);
}

