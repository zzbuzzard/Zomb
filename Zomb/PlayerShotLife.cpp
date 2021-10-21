#include "pch.h"
#include "PlayerShotLife.h"
#include "Enemy.h"
#include "GameState.h"
#include "CircleObj.h"

PlayerShotLife::PlayerShotLife(sf::Vector2f pos, float angle, const WeaponStats &stats)
	: PlayerProjectile(pos, angle, stats) {
	life = stats.dmg;
}

void PlayerShotLife::collide(CircleObj *other) {
	if (other->type == ObjectType::ENEMY) {
		// Damage enemy
		if (((Enemy*)other)->getLifeOn() > 0) {
			life -= ((Enemy*)other)->takeDamage(dmg);
			if (effect != StatusEffect::NONE)
				((Enemy*)other)->applyStatus(effect, effectTime);
			if (life < 0)
				hasHit = true;
		}
	}
}