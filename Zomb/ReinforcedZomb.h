#pragma once
#include "Enemy.h"
class ReinforcedZomb : public Enemy
{
public:
	ReinforcedZomb(sf::Vector2f pos, bool loot);
	~ReinforcedZomb();
	void update(GameState *state);
};

