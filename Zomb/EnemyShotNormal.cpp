#include "pch.h"
#include "EnemyShotNormal.h"

EnemyShotNormal::EnemyShotNormal(sf::Vector2f pos, float angle, const WeaponStats &stats) :
	EnemyProjectile(pos, angle, stats)
{
}


EnemyShotNormal::~EnemyShotNormal()
{
}
