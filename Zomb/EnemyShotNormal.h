#pragma once
#include "EnemyProjectile.h"
#include "LivingObject.h"
struct WeaponStats;
class EnemyShotNormal : public EnemyProjectile
{
public:
	EnemyShotNormal(sf::Vector2f pos, float angle, const WeaponStats &stats);
	~EnemyShotNormal();
private:
};

