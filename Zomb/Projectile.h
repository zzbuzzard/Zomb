#pragma once
#include "CircleObj.h"
#include <SFML/Graphics.hpp>

class GameState;

class Projectile : public CircleObj
{
public:
	Projectile(sf::Vector2f pos, TEXTURE texture, float life, float angle, float damage, float radius, float speed, float imageRadius = -1);
	~Projectile();

	void update(GameState *state);
	bool isAlive(GameState *state) const;
private:
public:
	sf::Vector2f moveV;
	float spd;
	float dmg;
	bool hasHit = false;

private:
	float life; // -10 means projectile never times out
};

