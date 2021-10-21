#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
class Runner : public Enemy
{
public:
	Runner(sf::Vector2f pos, bool loot=true);
	~Runner();
	void update(GameState *state);
};

