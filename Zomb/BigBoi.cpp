#include "pch.h"
#include "BigBoi.h"
#include "Media.h"
#include "Player.h"
#include "GameState.h"
#include "Util.h"
#include <SFML/Graphics.hpp>
#include "Weapon.h"

const EnemyStats bb_stats{ 20.0f, 0.2f, 90.0f, 1.75f, 10 };
const WeaponStats bb_wStats{T_BIG_BOI_SHOT, 0.4f, 1000, 1300, 0.8f, 32, 32, 2.5f, StatusEffect::SLOW};

std::vector<ITEMS> bb_drops = { I_PISTOL, I_TEXTBOOK, I_CARDBOARD_BOX, I_OLD_SHOES };
std::vector<int> bb_probs = { 35, 25, 18, 10 };

BigBoi::BigBoi(sf::Vector2f pos, bool loot) : Enemy(pos, T_BIG_BOI, loot, &bb_stats, 80, 145)
{
	dropList = &bb_drops;
	dropListProb = &bb_probs;

	t = util::rand(0, shootTime);
}


BigBoi::~BigBoi()
{
}

void BigBoi::update(GameState *state) {
	moveTowards(state->getPlayer()->getPosition(), spd);
	lookAt(state->getPlayer()->getPosition());

	Enemy::update(state);
	t -= deltaTime;

	if (t <= 0) {
		Player *p = state->getPlayer();
		if (util::dist(pos, p->getPosition()) <= range) {
			//shoot(state);
			shootNormal(state, p->getPosition(), bb_wStats);
			t = shootTime;
		}
	}
}

//void BigBoi::shoot(GameState *state) {
//	Player *p = state->getPlayer();
//	sf::Vector2f displacement = p->getPosition() - pos;
//
//	float angle = atan2(displacement.y, displacement.x);
//
//	state->addObject(new BigBoiShot(pos, angle));
//}

