#include "pch.h"
#include "RustyPistol.h"
#include "GameState.h"
#include "PlayerShotNormal.h"
#include "Media.h"
#include "Util.h"
#include "Player.h"


RustyPistol::RustyPistol() : Weapon(WeaponStats(T_BULLET, 0.85f, 2200.0f, 1000.0f, 4.0f, 12.0f))
{
}


RustyPistol::~RustyPistol()
{
}

void RustyPistol::fire(GameState *state, float acc, float rad) {
	float angle = util::ang(getRelativeMousePos(state));
	state->addObject(new PlayerShotNormal(state->getPlayer()->getPosition() + getCircPoint(angle, rad), angle + util::rand(-acc, acc), weaponStats));
}