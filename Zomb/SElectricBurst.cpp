#include "pch.h"
#include "SElectricBurst.h"
#include "GameState.h"
#include "PlayerShotNormal.h"
#include "Player.h"
#include "Util.h"

SElectricBurst::SElectricBurst() : Special(SpecialStats(20.0f))
{
}


SElectricBurst::~SElectricBurst()
{
}

const float randAmount = 0.7f;
const int numShots = 45;
WeaponStats zapStats = WeaponStats(T_ZAP, 2.0f, 3000.0f, 2000.0f, -1, 58, 96);
void SElectricBurst::fire(GameState *state) {
	float ang = util::ang(state->getMousePosWorld() - state->getPlayer()->getPosition());
	for (int i = 0; i < numShots; i++) {
		state->addObject(new PlayerShotNormal(state->getPlayer()->getPosition(), util::rand(-randAmount, randAmount) + ang, zapStats));
	}
}
