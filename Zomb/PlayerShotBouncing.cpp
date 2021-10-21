#include "pch.h"
#include "PlayerShotBouncing.h"
#include "Enemy.h"
#include "GameState.h"
#include "CircleObj.h"
#include "Util.h"

PlayerShotBouncing::PlayerShotBouncing(sf::Vector2f pos, float angle, const WeaponStats &stats, int bounces)
	: PlayerProjectile(pos, angle, stats), bounce_remain(bounces) {
}

void PlayerShotBouncing::collide(CircleObj *other) {
	if (other->type == ObjectType::ENEMY) {
		// Damage enemy
		if (((Enemy*)other)->getLifeOn() > 0) {
			if (effect != StatusEffect::NONE)
				((Enemy*)other)->applyStatus(effect, effectTime);

			((Enemy*)other)->takeDamage(dmg);

			moveV = util::bounce(pos, moveV, other->getPosition());
			bounce_remain--;

			if (bounce_remain <= 0)
				hasHit = true;
		}
	}
}