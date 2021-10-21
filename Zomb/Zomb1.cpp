#include "pch.h"
#include "Zomb1.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Media.h"
#include "GameState.h"
#include "Player.h"

// Old shoes : Zomb
// Cap : Zomb

const EnemyStats z1_stats{5.0f, 0.0f, 200.0f, 0.5f, 1};

std::vector<ITEMS> z1_drops = { I_CAP, I_SHIRT, I_OLD_SHOES };
std::vector<int> z1_probs = { 160, 150, 100 };

Zomb1::Zomb1(sf::Vector2f pos, bool loot) : Enemy(pos, T_ZOMB, loot, &z1_stats, 45, 82)
{
	dropList = &z1_drops;
	dropListProb = &z1_probs;
}


Zomb1::~Zomb1()
{
}

void Zomb1::update(GameState *state) {
	moveTowards(state->getPlayer()->getPosition(), spd);
	lookAt(state->getPlayer()->getPosition());
	Enemy::update(state);
}
