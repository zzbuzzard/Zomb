#include "pch.h"
#include "Runner.h"
#include "Media.h"
#include "GameState.h"
#include "Player.h"

const EnemyStats rn_stats{ 4.0f, 0.02f, 550.0f, 1.0f, 3 };

std::vector<ITEMS> rn_drops = { I_TRAINERS, I_WOODEN_SHIELD };
std::vector<int> rn_probs = { 200, 60 };

Runner::Runner(sf::Vector2f pos, bool loot) : Enemy(pos, T_RUNNER, loot, &rn_stats, 46, 80)
{
	dropList = &rn_drops;
	dropListProb = &rn_probs;
}


Runner::~Runner()
{
}

void Runner::update(GameState *state) {
	moveTowards(state->getPlayer()->getPosition(), spd);
	lookAt(state->getPlayer()->getPosition());

	Enemy::update(state);
}

