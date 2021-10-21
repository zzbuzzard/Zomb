#include "pch.h"
#include "EnemyShield.h"
#include "Media.h"
#include "Util.h"
#include "GameState.h"

const EnemyStats eshield_stats{10.0f, 0.9f, 0.0f, 0.0f, 0};

EnemyShield::EnemyShield(sf::Vector2f pos, CircleObj *follow, int *shieldCounter, float shieldLife, float orbitSpeed) :
	Enemy(pos, T_ENEMY_SHIELD, true, &eshield_stats, 60),
	orbitSpd(orbitSpeed)
{
	maxLife = shieldLife;
	lifeOn = shieldLife;
	resizeLifeBar();
	hasFeet = false;

	this->shieldCounter = shieldCounter;
	(*shieldCounter)++;
	this->follow = follow;
	orbitRad = util::dist(follow->getPosition(), pos);
	currentAng = (float)util::ang(follow->getPosition() - pos);
}


EnemyShield::~EnemyShield()
{
	(*shieldCounter)--;
}


void EnemyShield::update(GameState *state) {
	Enemy::update(state);
	currentAng += orbitSpd * deltaTime;
	if (currentAng < 0) currentAng += 2 * (float)util::PI;
	if (currentAng > 2 * util::PI) currentAng -= 2 * (float)util::PI;
	pos = follow->getPosition() + sf::Vector2f(orbitRad * cos(currentAng), orbitRad * sin(currentAng));
}


