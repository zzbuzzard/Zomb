#include "pch.h"
#include "ReinforcedZomb.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Media.h"
#include "GameState.h"
#include "Player.h"

const EnemyStats rz1_stats{ 10.0f, 0.35f, 180.0f, 0.75f, 3 };

std::vector<ITEMS> rz1_drops = { I_CHAINMAIL, I_HELMET, I_SHIELD };
std::vector<int> rz1_probs = { 300, 150, 150 };

ReinforcedZomb::ReinforcedZomb(sf::Vector2f pos, bool loot) : Enemy(pos, T_REINFORCED_ZOMB, loot, &rz1_stats, 45, 82)
{
	dropList = &rz1_drops;
	dropListProb = &rz1_probs;
}


ReinforcedZomb::~ReinforcedZomb()
{
}


void ReinforcedZomb::update(GameState *state) {
	moveTowards(state->getPlayer()->getPosition(), spd);
	lookAt(state->getPlayer()->getPosition());
	Enemy::update(state);
}