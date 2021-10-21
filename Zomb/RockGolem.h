#pragma once
#include "Enemy.h"
#include "GameState.h"

class RockGolem : public Enemy
{
public:
	RockGolem(sf::Vector2f pos, bool loot = true);

	void update(GameState *state);

public:
private:
	int PHASE = 1;

	// Phase 1
	float p1_walkSpd = 150.0f;
	float p1_shootT = 0;
	float p1_shootCool = 0.3f;

	EnemyType p1_spawns[1] = { REINFORCED_ZOMB };
	int p1_spawns_len = 1;

	//float p1_turnSpd = 1.0f;
	//float p1_ang = 0;

	float p1_spawnT = 0;
	float p1_spawnCool = 1.4f;

	float p1_shootAcc = 0.3f;

	// Phase 2
	int p2_burstCount = 0;
	int p2_burstMaxCount = 3;
	float p2_walkT = 4.0f;
	float p2_walkTime = 4.0f;
	float p2_walkSpd = 300.0f;

	float p2_shootT = 0;
	float p2_shootCool = 2.0f;


	bool p2_shooting = false;
	int p2_shootNum = 8;
	int p2_shootN;
	float p2_shootT2 = 0;
	float p2_shootCool2 = 0.05f;
	float p2_acc = 0.05f;

	// Phase 3
	int p3_numShields = 6;
	int p3_shieldCount = 0;
	EnemyType p3_spawns[2] = { REINFORCED_ZOMB, CAVE_THING };
	int p3_spawns_len = 2;
	float p3_walkSpd = 280.0f;
	float p3_spawnT = 0.0f;
	float p3_spawnCool = 2.0f;

	float p3_shieldLife = 4.0f;
	float p3_shieldSpd = 1.5f;
};
