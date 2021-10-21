#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"

// Phase 1
//  Look at player.
//  Timer counts down. When it hits 0, stop rotating and rush at player real quick.
//  Stop rushing when we pass the goal position
//  Stop, rotate (slowly) and repeat

// Phase 2 : life below 25%
//  Run towards player with constant speed
//  Fire bigboi shots, using numshots = 4, spread = 0.8

class Boss1 : public Enemy
{
public:
	Boss1(sf::Vector2f pos, bool loot=true);
	~Boss1();

	void update(GameState *state);

private:
	void shoot(GameState *state);
public:
private:
	int PHASE = 1;
	// Phase 1
	float rushSpeed = 2500.0f;

	float p1_spwnCool = 0.8f;
	float p1_spawnT = 0.8f;
	EnemyType p1_spawns[8] = { ZOMBIE, ZOMBIE, ZOMBIE, ZOMBIE, RUNNER, RUNNER, RUNNER, BIGBOI };
	int p1_spawns_len = 8;

	float rushTimer = 2.4f;
	float rushWait = 2.4f;
	bool rushing = false;

	float rushTime;
	sf::Vector2f rushMovement;

	// Phase 2
	int numShots = 2; // Cycles 2 and 4
	float walkSpeedFar = 800.0f;
	float walkSpeedClose = 400.0f;
	float walkSpeedChangeBoundary = 1800.0f;

	float shootCooldown = 0.8f;
	float shootSpeed = 0.78f;
	float shotGap = 0.85f; // gap in radians between leftmost and rightmost shot
	float shotAccuracy = 0.08f;

	float walkPauseTime = 2.0f, walkTime = 6.0f;
	float beginWalkingTimer = 3.5f;
	float isWalkingTimer = 5.0f;
};



