#include "pch.h"
#include "Controller.h"
#include "State.h"
#include "Inventory.h"
#include "SElectricBurst.h"
#include "LevelSelectState.h"

#include <fstream>

State *g_state, *g_savedState;
bool g_savedStateExists = false;

LEVEL currentLevel;
Inventory *inventory;
float DISTANCE_MUL = 0.05f;

int Coins;
void loadCoins() {
	std::ifstream fin("coins");
	if (fin.good()) {
		fin >> Coins;
	}
	else Coins = 10;
}
void saveCoins() {
	std::ofstream fout("coins");
	fout << Coins;
}
int getCoins() { return Coins; }
void addCoins(int a) {
	Coins += a;
	saveCoins();
}

void moveStateToSave() {
	g_savedStateExists = true;
	g_savedState = g_state;
	g_state = nullptr;
}

void loadSavedState() {
	delete g_state;
	g_state = g_savedState;
	g_savedStateExists = false;
	g_savedState = nullptr;
}

void deleteState() {
	delete g_state;
}

Stats getBasePlayerStats() {
	return Stats(25, 0, 10, 10, 10);
}

Stats getOverallPlayerStats() {
	Stats playerStats = getBasePlayerStats();
	playerStats.addStats(inventory->getEquipmentStats());
	return playerStats;
}

Controller::Controller()
{
}
Controller::~Controller()
{
}
