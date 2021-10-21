#include "pch.h"
#include "SDash_Multiple_Shotgun.h"
#include "GameState.h"
#include "Player.h"
#include "PlayerShotNormal.h"
#include "Util.h"


SDashMultipleShotgun::SDashMultipleShotgun() : Special(SpecialStats(25.0f))
{
}


SDashMultipleShotgun::~SDashMultipleShotgun()
{
}


WeaponStats shotStats = WeaponStats(T_ZAP, 2.8f, 2500.0f, 2000.0f, -1, 32, 45);
int sdms_N = 50;
int sdms_numShotguns = 6;
float sdms_dashTime = 0.1f;

void SDashMultipleShotgun::update(GameState *state, float intMultiplier, bool useSpecial) {
	Special::update(state, intMultiplier, useSpecial);
	tx -= deltaTime;
	while (ns>0 && tx < 0) {
		tx += sdms_dashTime / sdms_numShotguns;
		shotgun(state);
		ns--;
	}
}

void SDashMultipleShotgun::shotgun(GameState *state) {
	float a = util::rand(0, 2 * util::PI);
	float inc = 2 * util::PI / sdms_N;

	sf::Vector2f pos = state->getPlayer()->getPosition();
	for (int i = 0; i < sdms_N; i++) {
		state->addObject(new PlayerShotNormal(pos, a, shotStats));
		a += inc;
	}
}

void SDashMultipleShotgun::fire(GameState *state) {
	Player *p = state->getPlayer();
	ns = sdms_numShotguns;
	tx = sdms_dashTime / sdms_numShotguns;

	p->applyStatus(StatusEffect::DASHING_5k, sdms_dashTime);
}

