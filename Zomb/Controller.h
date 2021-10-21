#pragma once

class State;
class Inventory;
class Stats;
class Special;
enum LEVEL : int;

extern State *g_state, *g_savedState;
extern LEVEL currentLevel;
extern float DISTANCE_MUL;
extern Inventory *inventory;

void deleteState();
Stats getBasePlayerStats();
Stats getOverallPlayerStats();

void moveStateToSave();
void loadSavedState();

void loadCoins();
int getCoins();
void addCoins(int a);

class Controller
{
public:
	Controller();
	~Controller();
};

