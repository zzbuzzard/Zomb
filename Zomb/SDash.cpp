#include "pch.h"
#include "SDash.h"
#include "GameState.h"
#include "Player.h"
#include "Util.h"

SDash::SDash() : Special(SpecialStats(8.5f))
{
}


SDash::~SDash()
{
}


void SDash::fire(GameState *state) {
	Player *p = state->getPlayer();
	p->applyStatus(StatusEffect::DASHING_15k, 0.07f);
}
