#pragma once
#include "Enemy.h"
#include "GameState.h"

class ScienceZomb : public Enemy
{
public:
	ScienceZomb(sf::Vector2f pos, bool loot = true);
	~ScienceZomb();

	void update(GameState *state);

private:
	//void shootZapShotgun(GameState *state, int count);
	
	void shootSpikeClever(GameState *state, float accuracy);
	//void shootSpikeStupid(GameState *state, float accuracy);
	//void shootSpikeShotgun(GameState *state, int count);

	//void spawnShields(GameState *state, int count, int *shieldCounter);
public:
private:
	int PHASE = 1;
	int shieldCount = 0;

	// PHASE 1
	bool p1_init = false;
	sf::Vector2f p1_moveV;
	float p1_move1spd = 600.0f;
	float p1_moveTime;
	float p1_shCool = 0.04f;
	float p1_shT = 0.04f;

	float p1_spwnCool = 0.4f;
	float p1_spawnT = 0.4f;
	EnemyType p1_spawns[8] = {ZOMBIE, ZOMBIE, ZOMBIE, ZOMBIE, RUNNER, RUNNER, RUNNER, BIGBOI};
	int p1_spawns_len = 8;

	// PHASE 2
	int p2_numTeleports = 4;
	int p2_minTP = 3, p2_maxTP = 6;
	int p2_shotgunSize = 25;

	float p2_tpCool = 1.8f;
	float p2_tpT = 1.8f;

	float p2_runTime = 3.65f;
	float p2_currentRunTime = -1.0f;
	float p2_speed = 950.0f;

	// PHASE 3
	int p3_numShields = 8;
	float p3_shieldOrbitMul = 1.7f;
	float p3_shieldLife = 40.0f;
	float p3_shieldOrbitSpeed = 2.1f; //rad

	float p3_spwnCool = 0.25f;
	float p3_spawnT = 0.25f;
	EnemyType p3_spawns[1] = { RUNNER };
	int p3_spawns_len = 1;

	float p3_shotgunCool = 3.8f;
	float p3_shotgunT = 3.8f;
	int p3_shotgunSize = 20;
	
	float p3_shCool = 0.7f;
	float p3_shT = 0.7f;
	int p3_shBurst = 6;
	float p3_shAcc = 0.3f;

	float p3_spd = 420.0f;
	float p3_shieldSpd = 300.0f;

	int p3_shieldCount = 0;

	// PHASE 4
	float p4_runSpd = 1200.0f;
	sf::Vector2f p4_runMove;
	float p4_dirChange = 3.0f;
	float p4_dirChangeCool = 3.0f;
	float p4_ang;

	float p4_shCool = 1.4f;
	float p4_shT = 1.4f;
	float p4_shAcc = 0.13f;
	int p4_shBurst = 8;

	float p4_shotgunCool = 2.4f;
	float p4_shotgunT = 2.4f;
	int p4_shotgunSize = 60;
};