#include "pch.h"
#include "CaveThing.h"
#include "GameState.h"
#include "Player.h"
#include "Util.h"

std::vector<ITEMS> ct_drops = { I_ROBE };
std::vector<int> ct_probs = { 80 };

float normalSpd = 40, closeSpd = 850, spdChangeBoundary = 850;

const EnemyStats ct_stats{ 18.0f, 0.3f, closeSpd, 2.5f, 10 };

CaveThing::CaveThing(sf::Vector2f pos, bool loot) : Enemy(pos, T_CAVE_THING, loot, &ct_stats, 54, 98)
{
	dropList = &ct_drops;
	dropListProb = &ct_probs;
}


CaveThing::~CaveThing()
{
}

void CaveThing::update(GameState *state) {
	sf::Vector2f ppos = state->getPlayer()->getPosition();

	spd = util::dist(pos, ppos) < spdChangeBoundary ? closeSpd : normalSpd;

	moveTowards(ppos, spd);
	lookAt(ppos);

	Enemy::update(state);
}
