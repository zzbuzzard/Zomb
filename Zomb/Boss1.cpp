#include "pch.h"
#include "Boss1.h"
#include "Media.h"
#include "GameState.h"
#include "Player.h"
#include "Util.h"

// 700 HP
// = 350 * 2
// = 175 * 4

const EnemyStats b1_stats{ 175, 0.75f, -1.0f, 5.0f, 2000 };
const WeaponStats b1_slowWStats{ T_BIG_BOI_SHOT, 0.4f, 1500, 1500, 0.8f, 32, 32, 2.3f, StatusEffect::SLOW };

std::vector<ITEMS> b1_drops = { };
std::vector<int> b1_probs = { };

Boss1::Boss1(sf::Vector2f pos, bool loot) : Enemy(pos, T_BOSS1, loot, &b1_stats, 120, 190.0f) {
	PHASE = 1;

	dropList = &b1_drops;
	dropListProb = &b1_probs;
}



Boss1::~Boss1()
{
}

// Yoinked from player.cpp
void Boss1::shoot(GameState *state) {
	float angle = (float)util::ang(state->getPlayer()->getPosition() - pos);

	float increase = 2 * shotGap / (numShots - 1);
	float angO = -shotGap;

	for (int i = 0; i < numShots; i++) {
		sf::Vector2f bpos = sf::Vector2f(pos.x + radius * cos(angle + angO), pos.y + radius * sin(angle + angO));
		shootNormal(state, bpos, b1_slowWStats, shotAccuracy);
		angO += increase;
	}
}

void Boss1::update(GameState *state) {
	if (PHASE == 1) {
		if (lifeOn/maxLife < 3.0f/7.0f) {
			shootCooldown = shootSpeed;
			PHASE = 2;

			// bit of a weird one to avoid phase 1 and 2 running
			update(state);
			return;
		}

		sf::Vector2f playerPos = state->getPlayer()->getPosition();

		p1_spawnT -= deltaTime;
		if (p1_spawnT < 0) {
			p1_spawnT = p1_spwnCool;
			state->spawn(p1_spawns[util::randint(0, p1_spawns_len - 1)], false);
		}

		if (rushing) {
			if (util::dist(pos + rushMovement * deltaTime, playerPos) > util::dist(pos, playerPos)) {
				rushing = false;
			}

			moveDisplacement(rushMovement);
			//pos += rushMovement * deltaTime;
			//snapToBorders(state);

			rushTime -= deltaTime;
			if (rushTime <= 0) {
				rushing = false;
			}
		}
		else {
			rushTimer -= deltaTime;

			sf::Vector2f displacement = playerPos  - pos;
			//float angle = atan2(displacement.y, displacement.x);
			//rot = (float)(angle * 180 / util::PI);
			lookAt(state->getPlayer()->getPosition());
			spd = 0;
			moveTowards(state->getPlayer()->getPosition(), spd);

			if (rushTimer <= 0) {
				sf::Vector2f goalPos = util::predictMovementLinear(pos, playerPos, state->getPlayer()->getVelocity(), rushSpeed);
				displacement = goalPos - pos;

				rushMovement = displacement * (float)(rushSpeed / util::mag(displacement));
				rushing = true;
				rushTimer = rushWait;
				
				rushTime = 2.0f; // max time
			}
		}
	}

	if (PHASE == 2) {
		if (beginWalkingTimer <= 0) {
			isWalkingTimer -= deltaTime;
			if (util::dist(state->getPlayer()->getPosition(), pos) < walkSpeedChangeBoundary)
				spd = walkSpeedClose;
			else
				spd = walkSpeedFar;

			if (isWalkingTimer < 0) {
				beginWalkingTimer = walkPauseTime;
				isWalkingTimer = walkTime;
			}
		}
		else {
			beginWalkingTimer -= deltaTime;
			spd = 0;

			if (beginWalkingTimer < 0) {
				isWalkingTimer = walkTime;
			}
		}
		lookAt(state->getPlayer()->getPosition());
		moveTowards(state->getPlayer()->getPosition(), spd);

		shootCooldown -= deltaTime;
		if (shootCooldown <= 0) {
			shootCooldown = shootSpeed;
			shoot(state);
			numShots += 2;
			shotGap += 0.2f;
			if (numShots >= 6) {
				numShots = 2;
				shotGap = 0.4f;
			}
		}
	}

	Enemy::update(state);
}