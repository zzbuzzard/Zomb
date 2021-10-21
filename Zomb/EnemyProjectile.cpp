#include "pch.h"
#include "EnemyProjectile.h"
#include "Player.h"


EnemyProjectile::EnemyProjectile(sf::Vector2f pos, float angle, const WeaponStats &stats) :
	Projectile(pos, stats.texture, stats.lifetime, angle, stats.dmg, stats.rad, stats.spd, stats.imageRad),
	effect(stats.effect),
	effectTime(stats.effectTime)
{
}


EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::collide(CircleObj *other) {
	if (other->type == ObjectType::PLAYER) {
		hasHit = true;
		((Player*)other)->takeDamage(dmg);

		if (effect != StatusEffect::NONE)
			((Player*)other)->applyStatus(effect, effectTime);
	}
}