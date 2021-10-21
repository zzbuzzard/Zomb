#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class GameState;

class Zomb1 : public Enemy
{
public:
	Zomb1(sf::Vector2f pos, bool loot=true);
	~Zomb1();
	void update(GameState *state);
private:
public:
private:
};

