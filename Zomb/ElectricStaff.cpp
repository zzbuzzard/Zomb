#include "pch.h"
#include "ElectricStaff.h"
#include "GameState.h"
#include "PlayerShotNormal.h"
#include "Media.h"
#include "Util.h"
#include "Player.h"
#include "Weapon.h"

ElectricStaff::ElectricStaff() : Weapon(WeaponStats(T_ZAP, 1.0f, 2600.0f, 1500.0f, 8.0f, 48.0f, 80.0f, 0.2f, StatusEffect::PARALYZED)) {

}

ElectricStaff::~ElectricStaff()
{
}

void ElectricStaff::fire(GameState *state, float acc, float rad) {
	float angle = util::ang(getRelativeMousePos(state));
	state->addObject(new PlayerShotNormal(state->getPlayer()->getPosition() + getCircPoint(angle, rad),
		angle + util::rand(-acc, acc), weaponStats));
}
