#include "pch.h"
#include "ZombieFarmer.h"
#include "Player.h"
#include "Util.h"
#include "Weapon.h"

const EnemyStats zf_stats{ 100.0f, 0.6f, -1, 5.0f, 1000 };
const WeaponStats zf_shotStats{ T_BULLET, 0.5f, 2200, 1000, -1, 18 };
const WeaponStats zf_shotStatsPainful{ T_BULLET, 0.8f, 1800, 800, -1, 30 };

std::vector<ITEMS> zf_drops = { I_FARMER_HAT, I_SHOTGUN };
std::vector<int> zf_probs = { 25, 3 };

ZombieFarmer::ZombieFarmer(sf::Vector2f pos, bool loot) : Enemy(pos, T_ZOMB_FARMER, loot, &zf_stats, 90, 160)
{
	PHASE = 1;

	dropList = &zf_drops;
	dropListProb = &zf_probs;
}


ZombieFarmer::~ZombieFarmer()
{
}

//float p1_spd = 200.0f;
//int p1_burstSize = 20;
//float p1_burstAcc = 0.5f;
//float p1_shCool = 0.8f;
//float p1_shT = 0.8f;

void ZombieFarmer::update(GameState *state) {
	Player *p = state->getPlayer();

	if (PHASE == 1) {
		if (lifeOn / maxLife < 0.375f) {
			PHASE = 2;
			update(state);
			return;
		}
		moveTowards(p->getPosition(), p1_spd);

		p1_shT -= deltaTime;
		if (p1_shT < 0) {
			p1_shT = p1_shCool;
			for (int i = 0; i < p1_burstSize; i++) {
				shootNormal(state, p->getPosition(), zf_shotStats, p1_burstAcc);
			}
		}
	}

	if (PHASE == 2) {
		moveTowards(p->getPosition(), p2_spd);
		
		p2_shT -= deltaTime;
		if (p2_shT < 0) {
			p2_shT = p2_shCool;
			shootNormalShotgun(state, p2_shotgunSize, zf_shotStatsPainful);
		}

		p2_spT -= deltaTime;
		if (p2_spT < 0) {
			p2_spT = p2_spCool;
			for (int i = 0; i < p2_spC; i++) {
				state->spawnAt(p2_spawns[util::randint(0, p2_spawnsLen - 1)], pos, false);
			}			
		}
	}

	lookAt(p->getPosition());

	Enemy::update(state);
}

