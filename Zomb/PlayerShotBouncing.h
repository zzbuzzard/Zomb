#pragma once
#include "PlayerProjectile.h"
class PlayerShotBouncing : public PlayerProjectile
{
public:
	PlayerShotBouncing(sf::Vector2f pos, float angle, const WeaponStats &stat, int bounces);
	void collide(CircleObj *other);
private:
	int bounce_remain;
};

