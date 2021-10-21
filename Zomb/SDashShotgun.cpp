#include "pch.h"
#include "SDashShotgun.h"
#include "GameState.h"
#include "Player.h"
#include "PlayerShotNormal.h"
#include "Util.h"

SDashShotgun::SDashShotgun() : Special(SpecialStats(16.0f))
{
}


SDashShotgun::~SDashShotgun()
{
}

WeaponStats spikeStats = WeaponStats(T_RED_SPIKE, 3.2f, 3000.0f, 2500.0f, -1, 28, 40);
int N = 150;

void SDashShotgun::fire(GameState *state) {
	Player *p = state->getPlayer();

	float a = util::rand(0, 2 * util::PI);
	float inc = 2 * util::PI / N;

	for (int i = 0; i < N; i++) {
		state->addObject(
			new PlayerShotNormal(p->getPosition(), a, spikeStats));
		a += inc;
	}

	p->applyStatus(StatusEffect::DASHING_15k, 0.04f);
}

