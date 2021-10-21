#pragma once
#include "Enemy.h"
#include "GameState.h"

class ZombieFarmer : public Enemy
{
public:
	ZombieFarmer(sf::Vector2f pos, bool loot);
	~ZombieFarmer();

	void update(GameState *state);

private:

public:
private:
	int PHASE = 1;

	float p1_spd = 150.0f;
	int p1_burstSize = 45;
	float p1_burstAcc = 0.4f;
	float p1_shCool = 3.35f;
	float p1_shT = 3.35f;

	float p2_spd = 400.0f;
	int p2_shotgunSize = 50;
	float p2_shCool = 0.5f;
	float p2_shT = 0.5f;

	EnemyType p2_spawns[10] = {RUNNER, RUNNER, RUNNER, RUNNER, RUNNER, RUNNER, RUNNER, RUNNER, RUNNER, BIGBOI};
	int p2_spawnsLen = 10;
	float p2_spT = 0.5f;
	int p2_spC = 6;
	float p2_spCool = 6.0f;
};

// He has and drops a shotgun (high probability but blue box)
// Phase 1: He walks towards you slowly, firing stupidly
// Phase 2: He runs at you, firing very short bursts intelligently at you
