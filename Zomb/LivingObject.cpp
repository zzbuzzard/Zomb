#include "pch.h"
#include "LivingObject.h"
#include <iostream>
#include "GameState.h"
#include "Util.h"
#include "Weapon.h"
#include "EnemyShotNormal.h"
#include "EnemyShield.h"

inline float lifeBarMaxWidth(const float &radius) {
	return radius * 4.0f;
}

LivingObject::LivingObject(ObjectType myType, sf::Vector2f pos, TEXTURE texture, float rad, float life, float imageRadius) :
	CircleObj(myType, pos, texture, rad, imageRadius)
{
	maxLife = life;
	lifeOn = maxLife;

	resizeLifeBar();


	feet.setScale(radius);
}

float LivingObject::lookAt(sf::Vector2f position) {
	float angle = util::ang(position - pos);
	rot = (float)(angle * 180 / util::PI);
	return angle;
}

void LivingObject::lookDirection(float dir) {
	rot = (float)(dir * 180 / util::PI);
}

void LivingObject::moveTowards(sf::Vector2f point, float spd) {
	float angle = util::ang(point - pos);

	float realspd = spd;
	if (hasStatus(StatusEffect::SLOW)) realspd *= 0.5f;
	if (hasStatus(StatusEffect::PARALYZED)) realspd = 0.0f;
	if (hasStatus(StatusEffect::DASHING_5k)) realspd = 5000;
	if (hasStatus(StatusEffect::DASHING_15k)) realspd = 15000; //overrides paralysis / slow temporarily

	pos.x += realspd * cos(angle) * deltaTime;
	pos.y += realspd * sin(angle) * deltaTime;

	feet.setAngle(angle);
	feet.update(realspd);
}



void LivingObject::moveDisplacement(sf::Vector2f disp) {
	//if (hasStatus(StatusEffect::SLOW)) disp *= 0.5f;
	//if (hasStatus(StatusEffect::PARALYZED)) disp *= 0.0f;

	pos += disp * deltaTime;

	feet.setAngle(util::ang(disp));
	feet.update(util::mag(disp));
}

void LivingObject::snapToBorders(GameState *state) {
	// find point as (r, theta) and shorten r
	float r = util::mag(pos);
	if (r == 0) return;
	if (r + radius > state->getGameRadius()) {
		pos = pos * ((state->getGameRadius() - radius) / r);
	}

	//if (pos.y > state->getGameHeight() - radius) pos.y = state->getGameHeight() - radius;
	//if (pos.y < -state->getGameHeight() + radius) pos.y = -state->getGameHeight() + radius;
	//if (pos.x > state->getGameWidth() - radius) pos.x = state->getGameWidth() - radius;
	//if (pos.x < -state->getGameWidth() + radius) pos.x = -state->getGameWidth() + radius;
}

float LivingObject::getLifeOn() const {
	return lifeOn;
}

void LivingObject::setMana(float t) {
	float width = t * manaSizeMul * lifeBarMaxWidth(radius);
	lifeBars[0].setSize(sf::Vector2f(width, lifeBarHeight));
	lifeBars[0].setFillColor(sf::Color::White);
}


const float PLAYER_LIFEBAR_WIDTH_MUL = 0.25f;
void LivingObject::resizeLifeBar() {
	float widthRemaining = pixelsPerUnitLife * maxLife;
	
	if (type == ObjectType::PLAYER) {
		widthRemaining *= PLAYER_LIFEBAR_WIDTH_MUL;
	}

	numBars = (int)(widthRemaining / lifeBarMaxWidth(radius)) + 1;

	if (hasMana)numBars++;
	lifeBarBoxes.clear();
	lifeBars.clear();

	float w, h = lifeBarHeight;

	for (int i = 0; i < numBars; i++) {
		if (i == numBars - 1)
			w = widthRemaining;
		else
			w = lifeBarMaxWidth(radius);

		if (hasMana && i == 0) w = lifeBarMaxWidth(radius)*manaSizeMul;

		sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(w, h));
		sf::RectangleShape bar = sf::RectangleShape(sf::Vector2f(w, h));

		box.setFillColor(sf::Color::Black);
		bar.setFillColor(sf::Color::Green);

		box.setOrigin(w / 2, h / 2);
		bar.setOrigin(w / 2, h / 2);

		lifeBarBoxes.push_back(box);
		lifeBars.push_back(bar);

		if (!(hasMana && i == 0))
			widthRemaining -= lifeBarMaxWidth(radius);
	}
}

// Distance underneath
const float lifeBarDisplacementMultiplier = 1.3f;
void LivingObject::update(GameState *state) {
	CircleObj::update(state);

	float y1 = radius * lifeBarDisplacementMultiplier;
	float lifeWidthRemaining = pixelsPerUnitLife * lifeOn;
	if (type == ObjectType::PLAYER) lifeWidthRemaining *= PLAYER_LIFEBAR_WIDTH_MUL;

	for (int i = 0; i < numBars; i++) {
		lifeBarBoxes[i].setPosition(pos + sf::Vector2f(0, y1 + i * lifeBarSeparation));
		lifeBars[i].setPosition(pos + sf::Vector2f(0, y1 + i * lifeBarSeparation));

		if (hasMana && i == 0) {
		}
		else {
			lifeBars[i].setSize(sf::Vector2f(std::min(lifeWidthRemaining, lifeBarMaxWidth(radius)), lifeBarHeight));
			lifeWidthRemaining -= lifeBarMaxWidth(radius);
			if (lifeWidthRemaining < 0) lifeWidthRemaining = 0;
		}
	}

	for (int i = statusEffects.size() - 1; i >= 0; i--) {
		// Permanent status effects
		if (statusEffects[i].second != -10) {
			statusEffects[i].second -= deltaTime;
			if (statusEffects[i].second <= 0) statusEffects.erase(statusEffects.begin() + i);
		}
	}

	if (hasStatus(StatusEffect::POISONED)) takeDamage(0.5f*deltaTime);

	feet.setPosition(pos);
}

void LivingObject::applyStatus(StatusEffect status, float time) {
	for (auto &i : statusEffects) {
		if (i.first == status) {
			if (time == -10)
				i.second = -10;
			else {
				if (i.second != -10)
					i.second = std::max(time, i.second);
			}
			return;
		}
	}
	statusEffects.push_back(std::pair<StatusEffect, float>(status, time));
}

void setAlpha(sf::RectangleShape &shape, float alpha) {
	sf::Color col = shape.getFillColor();
	col.a = (sf::Uint8)alpha;
	shape.setFillColor(col);
}

const float lowOpacityValue = 0.3f;
void LivingObject::setLifeBarLowOpacity(bool isLow) {
	if (isLow == lifebarLowOpacity) return;
	lifebarLowOpacity = isLow;
	if (lifebarLowOpacity) {
		for (int i = 0; i < numBars; i++) {
			setAlpha(lifeBars[i], lowOpacityValue *255);
			setAlpha(lifeBarBoxes[i], lowOpacityValue *255);
		}
	}
	else {
		for (int i = 0; i < numBars; i++) {
			setAlpha(lifeBars[i], 1.0f*255);
			setAlpha(lifeBarBoxes[i], 1.0f*255);
		}
	}
}

void LivingObject::draw(sf::RenderWindow *window) const {
	if (hasFeet)
		feet.draw(window);
	CircleObj::draw(window);

	if (!invincible){
		for (int i = 0; i < numBars; i++) {
			window->draw(lifeBarBoxes[i]);
			window->draw(lifeBars[i]);
		}
	}
}

float LivingObject::takeDamage(float dmg) {
	if (!invincible) {
		lifeOn -= dmg;
		return dmg;
	}
	return 0;
}

bool LivingObject::isAlive(GameState *state) const {
	return lifeOn > 0;
}

LivingObject::~LivingObject()
{
}

void LivingObject::shootNormal(GameState *state, sf::Vector2f goal, const WeaponStats &stats, float acc) {
	state->addObject(new EnemyShotNormal(pos, util::ang(goal - pos)+util::rand(-acc,acc), stats));
}

void LivingObject::shootNormal(GameState *state, float angle, const WeaponStats &stats, float acc) {
	state->addObject(new EnemyShotNormal(pos, angle+util::rand(-acc,acc), stats));
}

void LivingObject::shootNormalShotgun(GameState *state, int count, const WeaponStats &stats) {
	float angle = util::rand(0, 2 * util::PI);
	float angChange = (2 * util::PI) / count;
	for (int i = 0; i < count; i++) {
		state->addObject(new EnemyShotNormal(pos + radius*sf::Vector2f(cos(angle), sin(angle)), angle, stats));
		angle += angChange;
	}
}


void LivingObject::spawnShields(GameState *state, int count, int *shieldCounter, float orbitRadiusMultiplier, float life, float spd) {
	float angle = util::rand(0, 2 * util::PI);
	float angChange = (2 * util::PI) / count;
	for (int i = 0; i < count; i++) {
		state->addObject(new
			EnemyShield(pos + sf::Vector2f(cos(angle), sin(angle))*radius*orbitRadiusMultiplier, this,
				shieldCounter, life, spd));
		angle += angChange;
	}
}

