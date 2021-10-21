#include "pch.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "LivingObject.h"
#include "GameState.h"
#include "Player.h"
#include "Util.h"
#include "ItemCrate.h"

#include <math.h>

Enemy::Enemy(sf::Vector2f pos, TEXTURE texture, bool dropLoot, const EnemyStats *enemyStats_, float radius, float imageRadius) :
	LivingObject(ObjectType::ENEMY, pos, texture, radius, enemyStats_->hp, imageRadius),
 dropsLoot(dropLoot), enemyStats(enemyStats_), spd(enemyStats_->spd)
{
}


Enemy::~Enemy()
{
}


void Enemy::update(GameState *state) {
	if (util::dist(state->getPlayer()->getPosition(), pos) <= radius * 3 + state->getPlayer()->getRadius())
		setLifeBarLowOpacity(true);
	else
		setLifeBarLowOpacity(false);

	LivingObject::update(state);	
	snapToBorders(state);
}

const float damp = 20.0f;
//const float timedamp = 0.1f;

void Enemy::moveBy(const sf::Vector2f &displacement){
	if (isStatic) return;
	CircleObj::moveBy(displacement);
}

float Enemy::takeDamage(float dmg) {
	return LivingObject::takeDamage(dmg * (1 - enemyStats->def));
}

//#define E 2.718281828459045

// Damage is always given, not taken
// So handle player collision here, and not bullet
void Enemy::collide(CircleObj *other) {
	float damp2 = damp * deltaTime;
	if (damp2 > 1)damp2 = 1;

	if (other->type == ObjectType::PLAYER) {
		((Player*)other)->takeDamage(deltaTime * enemyStats->dmg);

		sf::Vector2f disp = other->getPosition() - pos;
		float d = (float)util::mag(disp);
		if (d < 0.01f) d = 0.01f;
		float realmag = radius + other->getRadius();
		float move = (realmag - d) / 2.0f; // Distance that must be moved

		//float C = log(damp*move);
		//float s2 = 1 / damp * powf(E, C - deltaTime*damp);

		sf::Vector2f mover = damp2 * move * disp / d;
		//sf::Vector2f mover = deltaTime * mvspd * disp / d;
		//sf::Vector2f mover = (move-s2)/deltaTime * disp / d;

		other->moveBy(mover);
		moveBy(-mover);
	}
	if (other->type == ObjectType::ENEMY) {
		sf::Vector2f disp = other->getPosition() - pos;
		float d = (float)util::mag(disp);
		if (d < 0.01f) d = 0.01f;
		float realmag = radius + other->getRadius();
		float move = (realmag - d) / 2.0f;

		//float C = log(damp*move);
		//float s2 = 1 / damp * powf(E, C - deltaTime * damp);

		sf::Vector2f mover = damp2 * move * disp / d;
		//sf::Vector2f mover = deltaTime * move * disp / d;
		//sf::Vector2f mover = deltaTime * mvspd * disp / d;
		//sf::Vector2f mover = (move - s2) / deltaTime * disp / d;

		other->moveBy(mover);
		moveBy(-mover);
		//other->moveBy(damp * move * disp / d);
		//moveBy(-1 * damp * move * disp / d);
	}
}

// But one day you will die too
void Enemy::handleDeath(GameState *state) {
	if (dropsLoot) {
		spawnCrate(state);
		state->coinsEarned(enemyStats->coins);
		// xp?
	}
}

#include <iostream>
void Enemy::draw(sf::RenderWindow *window) const {
	LivingObject::draw(window);
}

void Enemy::spawnCrate(GameState *state) {
	if (dropList == nullptr) return;

	std::vector<ITEMS> dropped;

	for (int i = 0; i < (int)dropList->size(); i++) {
		int x = util::randint(1, (*dropListProb)[i]);
		if (x == 1) {
			dropped.push_back((*dropList)[i]);
		}
	}

	if (dropped.size() > 0) {
		state->addObject(new ItemCrate(pos, dropped));
	}
}