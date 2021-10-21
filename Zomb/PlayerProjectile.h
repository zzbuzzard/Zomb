#pragma once
#include "Projectile.h"
#include "Weapon.h"

class CircleObj;

class PlayerProjectile : public Projectile
{
public:
	PlayerProjectile(sf::Vector2f pos, float angle, const WeaponStats &stats);
	~PlayerProjectile();
	void collide(CircleObj *other);
private:
public:
protected:
	StatusEffect effect;
	float effectTime;
private:
};

