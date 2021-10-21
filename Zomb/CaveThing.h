#pragma once
#include "Enemy.h"
class CaveThing : public Enemy
{
public:
	CaveThing(sf::Vector2f pos, bool loot = true);
	~CaveThing();
	void update(GameState *state);
};

