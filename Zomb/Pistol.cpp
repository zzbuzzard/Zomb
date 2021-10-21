#include "pch.h"
#include "Pistol.h"
#include "GameState.h"
#include "PlayerShotNormal.h"
#include "Media.h"
#include "Util.h"
#include "Player.h"

Pistol::Pistol() : Weapon(WeaponStats(T_BULLET, 1.2f, 2200.0f, 1100.0f, 6.0f, 12.0f))
{
}


Pistol::~Pistol()
{
}

void Pistol::fire(GameState *state, float acc, float rad) {
	float angle = util::ang(getRelativeMousePos(state));
	state->addObject(new PlayerShotNormal(state->getPlayer()->getPosition()+getCircPoint(angle, rad), angle + util::rand(-acc, acc), weaponStats));
}