#pragma once
#include "Enemy.h"

class GameState;

class BigBoi :
	public Enemy
{
public:
	BigBoi(sf::Vector2f pos, bool loot=true);
	~BigBoi();

	void update(GameState *state);
public:
private:
	float range = 2500.0f;

	float t = 2.0f;
	float shootTime = 1.2f;
};

