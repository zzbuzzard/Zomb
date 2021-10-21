#include "pch.h"
#include "Shotgun.h"
#include "GameState.h"
#include "PlayerShotNormal.h"
#include "Media.h"
#include "Util.h"
#include "Player.h"

Shotgun::Shotgun() : Weapon(WeaponStats(T_BULLET, 1.0f, 2600.0f, 1075.0f, 2.0f, 10.0f))
{
}


Shotgun::~Shotgun()
{
}

const int burstSize = 20;
void Shotgun::fire(GameState *state, float acc, float rad) {
	float angle = util::ang(getRelativeMousePos(state));
	sf::Vector2f pos = state->getPlayer()->getPosition() + getCircPoint(angle, rad);
	for (int i = 0; i < 10; i++) {
		state->addObject(new PlayerShotNormal(
			pos, angle + util::rand(-acc*2.5f, acc*2.5f), weaponStats));
	}
}
