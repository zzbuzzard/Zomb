#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class CircleObj;

class EnemyShield :
	public Enemy
{
public:
	// orbitSpeed is in radians / sec
	EnemyShield(sf::Vector2f pos, CircleObj *follow, int *shieldCounter, float shieldLife, float orbitSpeed);
	~EnemyShield();
	void update(GameState *state);
private:
public:
private:
	int *shieldCounter;
	CircleObj *follow;
	float orbitRad, orbitSpd, currentAng;
};

