#pragma once
#include "PlayerProjectile.h"

class PlayerShotLife : public PlayerProjectile
{
public:
	PlayerShotLife(sf::Vector2f pos, float angle, const WeaponStats &stat);
	void collide(CircleObj *other);
private:
	float life;
};

