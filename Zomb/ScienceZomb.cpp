#include "pch.h"
#include "Media.h"
#include "ScienceZomb.h"
#include "GameState.h"
#include "Player.h"

//#include "EnemySpike.h"

#include "Util.h"
#include "EnemyShield.h"

#include <iostream>

const EnemyStats sz_stats{ 1000.0f, 0.5f, -1, 7.0f, 8000 };
const WeaponStats sz_zapStats{ T_ZAP, 0.5f, 2000, 2000, -1, 48, 80, 0.3f, StatusEffect::PARALYZED };
const WeaponStats sz_spikeStats{ T_RED_SPIKE, 1.25f, 1750, 1500, -1, 28, 40 };
const WeaponStats sz_spikeStatsSnipe{ T_RED_SPIKE, 1.0f, 1950, 3000, -1, 28, 40 };

std::vector<ITEMS> sz_drops = { };
std::vector<int> sz_probs = { };

ScienceZomb::ScienceZomb(sf::Vector2f pos, bool loot) : Enemy(pos, T_SCIENCE_ZOMB, loot, &sz_stats, 180, 240) {
	PHASE = 1;

	dropList = &sz_drops;
	dropListProb = &sz_probs;
}


ScienceZomb::~ScienceZomb()
{
}


void ScienceZomb::shootSpikeClever(GameState *state, float accuracy) {
	Player *p = state->getPlayer();
	sf::Vector2f goal = util::predictMovementLinear(pos, p->getPosition(), p->getVelocity(), sz_zapStats.spd);

	shootNormal(state, goal, sz_spikeStats, accuracy);
}

//void ScienceZomb::shootSpikeClever(GameState *state, float accuracy) {
//	Player *p = state->getPlayer();
//
//	sf::Vector2f goal = util::predictMovementLinear(pos, p->getPosition(), p->getVelocity(), spikeSpd);
//
//	float angle = util::ang(goal - pos);
//	angle += util::rand(-accuracy, accuracy);
//
//	state->addObject(new EnemySpike(pos, angle));
//}

//void ScienceZomb::shootZapShotgun(GameState *state, int count) {
//	float angle = util::rand(0, 2 * util::PI);
//	float angChange = (2 * util::PI) / count;
//	for (int i = 0; i < count; i++) {
//		state->addObject(new Zap(pos + sf::Vector2f(cos(angle), sin(angle))*radius, angle));
//		angle += angChange;
//	}
//}

//void ScienceZomb::shootSpikeShotgun(GameState *state, int count) {
//	float angle = util::rand(0, 2 * util::PI);
//	float angChange = (2 * util::PI) / count;
//	for (int i = 0; i < count; i++) {
//		state->addObject(new EnemySpike(pos + sf::Vector2f(cos(angle), sin(angle))*radius, angle));
//		angle += angChange;
//	}
//}



// Deformed science zombie:
//   1.0  ...  0.75
//   Phase 1: Shoots electric bolts at you but with terrible accuracy. Stands in middle. 
//    Moves towards middle for a fixed amount of time, invulnerable (so while timer > 0, move)
//    Timer hits 0, we start shooting randomly. Also sets invun to false
//    Another timer spawns a mf from a list of mfs

//   0.75 ... 0.45
//   Phase 2: Teleports randomly a few times, each time shooting out damaging bullets. Eventually runs at you, shooting electric behind.
//            Stops running when he hits you or after a few seconds.
//    Picks a random number of times to teleport
// 
//   0.45 ... 0.15
//   Phase 3: Spawns spinning shields and becomes invincible. Runner zombies spawn in continuously.
//     Shoots periodic electric shotguns and intelligent spike bursts

//    0.15 ... 0
//   Phase 4: Runs away from you, firing damaging bullets with terrible accuracy.
//    Runs slowly to prevent squishing into wall
//    Shoots spike shotguns
//    Shoots intelligent zaps

void ScienceZomb::update(GameState *state) {
	if (PHASE == 1) {
		if (lifeOn / maxLife < 0.75f) {
			isStatic = false;
			PHASE = 2;
			update(state);
			return;
		}

		LivingObject::update(state);

		if (!p1_init) {
			isStatic = true;

			p1_init = true;
			p1_moveTime = (float)(util::dist(pos, state->getGameCenter()) / p1_move1spd);

			p1_shT = p1_shCool;
			p1_spawnT = p1_spwnCool;

			spd = p1_move1spd;
			p1_moveV = (state->getGameCenter() - pos) / p1_moveTime;

			lookAt(state->getGameCenter());
		}

		p1_spawnT -= deltaTime;
		if (p1_spawnT < 0) {
			p1_spawnT = p1_spwnCool;
			state->spawn(p1_spawns[util::randint(0, p1_spawns_len-1)], false);
		}

		if (p1_moveTime > 0) {
			p1_moveTime -= deltaTime;
			moveDisplacement(p1_moveV);
			//pos += p1_moveV * deltaTime;
			//snapToBorders(state);
		}
		else {
			lookAt(state->getPlayer()->getPosition());

			p1_shT -= deltaTime;
			if (p1_shT < 0) {
				p1_shT = p1_shCool;
				shootNormal(state, util::rand(0, 2 * util::PI), sz_zapStats);
			}
		}
	}

	if (PHASE == 2) {
		if (lifeOn / maxLife < 0.45f) {
			PHASE = 3;
			isStatic = true;
			invincible = true;
			spd = p3_spd;
			spawnShields(state, p3_numShields, &shieldCount, p3_shieldOrbitMul, p3_shieldLife, p3_shieldSpd);
			update(state);
			return;
		}

		spd = p2_speed;

		// if current run time > 0, we are currently running
		// else, tp wait reduce
		if (p2_currentRunTime > 0) {
			p2_currentRunTime -= deltaTime;
			lookAt(state->getPlayer()->getPosition());
			moveTowards(state->getPlayer()->getPosition(), spd);
		}
		else {
			p2_tpT -= deltaTime;
			if (p2_tpT < 0) {
				p2_tpT = p2_tpCool;

				if (p2_numTeleports <= 0) {
					p2_numTeleports = util::randint(p2_minTP, p2_maxTP);
					p2_currentRunTime = p2_runTime;
				}
				else {
					p2_numTeleports--;

					float w = state->getGameRadius(), h = state->getGameRadius();

					shootNormalShotgun(state, p2_shotgunSize, sz_zapStats);

					pos = sf::Vector2f(util::rand(-w + radius, w - radius), util::rand(-h + radius, h - radius));
					snapToBorders(state);
				}				
			}
		}
	}

	if (PHASE == 3){
		if (lifeOn / maxLife < 0.15f) {
			isStatic = false;
			invincible = false;

			p4_ang = util::rand(0, 2 * util::PI); rot = p4_ang * 180 / util::PI;
			p4_runMove = p4_runSpd * sf::Vector2f(cos(p4_ang), sin(p4_ang));

			PHASE = 4;
			update(state);
			return;
		}

		lookAt(state->getPlayer()->getPosition());
		moveTowards(state->getPlayer()->getPosition(), spd);

		p3_spawnT -= deltaTime;
		if (p3_spawnT < 0) {
			p3_spawnT = p3_spwnCool;
			state->spawn(p3_spawns[util::randint(0, p3_spawns_len - 1)], false);
		}

		if (shieldCount > 0) {
//			std::cout << "Shields: " << shieldCount << std::endl;
			invincible = true;
			spd = p3_shieldSpd;
		}
		else {
			invincible = false;
			spd = p3_spd;
		}

		p3_shotgunT -= deltaTime;
		if (p3_shotgunT < 0) {
			p3_shotgunT = p3_shotgunCool;
			shootNormalShotgun(state, p2_shotgunSize, sz_zapStats);
		}

		p3_shT -= deltaTime;
		if (p3_shT < 0) {
			p3_shT = p3_shCool;
			for (int i = 0; i < p3_shBurst; i++) {
				shootNormal(state, state->getPlayer()->getPosition(), sz_spikeStats, p3_shAcc);
			}
		}
	}

	if (PHASE == 4) {
		//if (pos.x + radius > state->getGameWidth() || 
		//	pos.x - radius < -state->getGameWidth()) {
		//	p4_runMove.x *= -1;
		//	p4_ang = util::ang(p4_runMove);
		//}

		//if (pos.y + radius > state->getGameHeight() ||
		//	pos.y - radius < -state->getGameHeight()) {
		//	p4_runMove.y *= -1;
		//	p4_ang = util::ang(p4_runMove);
		//}

		p4_dirChange -= deltaTime;
		if (p4_dirChange < 0) {
			p4_dirChange = p4_dirChangeCool;

			sf::Vector2f goal = sf::Vector2f(util::rand(-500, 500), util::rand(-500, 500));
			p4_ang = util::ang(goal - pos);
		}

		//p4_ang += p4_angChange * deltaTime;
		//rot = p4_ang * 180 / util::PI;
		p4_runMove = p4_runSpd * sf::Vector2f(cos(p4_ang), sin(p4_ang));
		moveDisplacement(p4_runMove);
		lookDirection(p4_ang);
		//pos += p4_runMove * deltaTime;
		//snapToBorders(state);

		//float angle = lookAt(pos * 2.0f - state->getPlayer()->getPosition());

		//pos.x += p4_runSpd * cos(angle) * deltaTime;
		//pos.y += p4_runSpd * sin(angle) * deltaTime;

//		snapToBorders(state);

		p4_shotgunT -= deltaTime;
		if (p4_shotgunT < 0) {
			p4_shotgunT = p4_shotgunCool;
			shootNormalShotgun(state, p2_shotgunSize, sz_zapStats);
		}

		p4_shT -= deltaTime;
		if (p4_shT < 0) {
			p4_shT = p4_shCool;
			for (int i = 0; i < p4_shBurst; i++) {
				shootSpikeClever(state, p4_shAcc);
			}
		}
	}

	Enemy::update(state);
}