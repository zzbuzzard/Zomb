#include "pch.h"
#include "EarthStaff.h"
#include "GameState.h"
#include "PlayerShotBouncing.h"
#include "Media.h"
#include "Util.h"
#include "Player.h"
#include "Weapon.h"

EarthStaff::EarthStaff() : Weapon(WeaponStats(T_ROCK, 1.5f, 2300.0f, 3000.0f, 6.0f, 50.0f, 55.0f)) {

}

void EarthStaff::fire(GameState *state, float acc, float rad) {
	float angle = util::ang(getRelativeMousePos(state));
	state->addObject(new PlayerShotBouncing(state->getPlayer()->getPosition() + getCircPoint(angle, rad),
		angle + util::rand(-acc, acc), weaponStats, 3));
}
