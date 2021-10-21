#include "pch.h"
#include "PlayerProjectile.h"
#include "Enemy.h"

PlayerProjectile::PlayerProjectile(sf::Vector2f pos, float angle, const WeaponStats &stats)
	: Projectile(pos, stats.texture, stats.lifetime, angle, stats.dmg, stats.rad, stats.spd, stats.imageRad),
	effect(stats.effect),
	effectTime(stats.effectTime)
{
}


PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::collide(CircleObj *other) {
	if (other->type == ObjectType::ENEMY) {
		// Damage enemy
		if (((Enemy*)other)->getLifeOn() > 0) {
			hasHit = true;
			((Enemy*)other)->takeDamage(dmg);
			if (effect != StatusEffect::NONE)
				((Enemy*)other)->applyStatus(effect, effectTime);
		}
	}
}