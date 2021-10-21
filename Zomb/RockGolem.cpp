#include "pch.h"
#include "RockGolem.h"
#include "Media.h"
#include "GameState.h"
#include "Player.h"
#include "Util.h"

const EnemyStats rg_stats{ 225, 0.8f, -1.0f, 5.0f, 5000 };
const WeaponStats rg_rockStats{ T_ROCK, 3.0f, 1200, 2500, -1, 75, 80 };
const WeaponStats rg_rockStatsFast{ T_ROCK, 2.5f, 1800, 2500, -1, 60, 70 };

std::vector<ITEMS> rg_drops = { I_EARTH_STAFF, I_HEAVY_ARMOUR, I_ANCIENT_BOOK };
std::vector<int> rg_probs = { 5, 3, 2 };

RockGolem::RockGolem(sf::Vector2f pos, bool loot) : Enemy(pos, T_ROCK_GOLEM, loot, &rg_stats, 150, 267.0f) {
	PHASE = 1;

	dropList = &rg_drops;
	dropListProb = &rg_probs;
}

// Rock golem:
//  Phase 1: Moves slowly towards player, firing rocks stupidly.
//   Slow moving enemies spawn from the outside constantly. 2/5
//  Phase 2: Fires 3 bursts of rocks intelligently, then pauses and walks towards you. Repeats. 4/5
//  Phase 3: Spawns shields around body and walks towards you, enemies spawn in again. 1/5
void RockGolem::update(GameState *state) {
	sf::Vector2f playerPos = state->getPlayer()->getPosition();
	lookAt(playerPos);

	if (PHASE == 1) {
		if (lifeOn / maxLife < 3.5f / 5.0f) {
			PHASE = 2;
			update(state);
			return;
		}

		spd = p1_walkSpd;
		moveTowards(playerPos, spd);

		p1_spawnT -= deltaTime;
		if (p1_spawnT < 0) {
			p1_spawnT = p1_spawnCool;
			state->spawn(p1_spawns[util::randint(0, p1_spawns_len - 1)], false);
		}

		p1_shootT -= deltaTime;
		if (p1_shootT < 0) {
			p1_shootT = p1_shootCool;
			shootNormal(state, playerPos, rg_rockStats, p1_shootAcc);
		}
	}

	if (PHASE == 2) {
		if (lifeOn / maxLife < 1.0f / 5.0f) {
			PHASE = 3;
			spawnShields(state, p3_numShields, &p3_shieldCount, 1.5, p3_shieldLife, p3_shieldSpd);
			update(state);
			return;
		}

		if (p2_shooting) {
			p2_shootT2 -= deltaTime;
			if (p2_shootT2 < 0) {
				p2_shootT2 = p2_shootCool2;
				sf::Vector2f shootPos = util::predictMovementLinear(pos, playerPos,
					state->getPlayer()->getVelocity(), rg_rockStatsFast.spd);
				shootNormal(state, shootPos, rg_rockStatsFast, p2_acc);

				p2_shootN--;
				if (p2_shootN <= 0) {
					p2_shootN = p2_shootNum;
					p2_shooting = false;
				}
			}
		}
		else {

			if (p2_walkT > 0) {
				p2_walkT -= deltaTime;
				spd = p2_walkSpd;
				moveTowards(playerPos, spd);

				if (p2_walkT <= 0) {
					p2_shootT = p2_shootCool;
					p2_burstCount = 0;
				}
			}
			else {
				p2_shootT -= deltaTime;
				if (p2_shootT < 0) {
					p2_shootT = p2_shootCool;

					p2_shooting = true;
					p2_shootT2 = p2_shootCool2;
					p2_shootN = p2_shootNum;

					p2_burstCount++;
					if (p2_burstCount >= p2_burstMaxCount) {
						p2_walkT = p2_walkTime;
					}
				}
			}
		}
	}

	if (PHASE == 3) {
		invincible = (p3_shieldCount > 0);

		spd = p3_walkSpd;
		moveTowards(playerPos, spd);

		p3_spawnT -= deltaTime;
		if (p3_spawnT < 0) {
			p3_spawnT = p3_spawnCool;
			state->spawn(p3_spawns[util::randint(0, p3_spawns_len - 1)], false);
		}
	}

	Enemy::update(state);
}


