#pragma once
#include "Projectile.h"
#include "Weapon.h"

class CircleObj;

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile(sf::Vector2f pos, float angle, const WeaponStats &stats);
	~EnemyProjectile();
	void collide(CircleObj *other);
private:
public:
private:
	StatusEffect effect;
	float effectTime;
};
