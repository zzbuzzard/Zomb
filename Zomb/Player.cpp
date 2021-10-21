#include "pch.h"
#include "Player.h"
#include "Media.h"
#include "GameState.h"
#include "Util.h"
#include <iostream>

float playerRadius = 50;

Player::Player(const Stats &stats, Weapon *weapon, Special *special) : LivingObject(ObjectType::PLAYER, sf::Vector2f(0, 0), T_PLAYER, playerRadius, stats.getHP(), 92) {
	this->stats = stats;
	myWeapon = weapon;
	mySpecial = special;

	if (mySpecial != nullptr) {
		hasMana = true;
		resizeLifeBar();
	}
}

Player::~Player()
{
	if (myWeapon != nullptr)
		delete myWeapon;
	if (mySpecial != nullptr)
		delete mySpecial;
}

void Player::copyFrom(Player *p) {
	if (mySpecial != nullptr && p->mySpecial != nullptr)
		mySpecial->t = p->mySpecial->t;
	isAutoFire = p->isAutoFire;
	pos = p->pos;
	lifeOn = p->lifeOn;
	if (lifeOn > maxLife) lifeOn = maxLife;
	for (const auto &pair : p->statusEffects) {
		if (pair.second != -10)
			applyStatus(pair.first, pair.second);
	}
}

void Player::takeDamage(float dmg) {
	LivingObject::takeDamage(dmg * stats.getDef());
}

//void Player::shoot(GameState *state) {
//	sf::Vector2f mousePos = (sf::Vector2f)state->getMousePos();
//	mousePos -= state->getScreenCenter();
//
//	float angle = (float)atan2(mousePos.y, (double)mousePos.x);
//
//	float increase = (numShots > 1) ? 2*shotGap / (numShots - 1) : 0;
//	float angO = (numShots > 1)?-shotGap:0;
//
//	for (int i = 0; i < numShots; i++) {
//		sf::Vector2f bpos = sf::Vector2f(pos.x + radius * cos(angle+angO), pos.y + radius * sin(angle+angO));
//		state->addObject(new PlayerShot(bpos, angle + angO + util::rand(-stats.getAcc(), stats.getAcc()), bulletDamage));
//		angO += increase;
//	}
//}

void Player::update(GameState *state) {
	sf::Vector2f m = sf::Vector2f(0, 0);
	//t -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (!autoFireButtonHeld) {
			autoFireButtonHeld = true;
			isAutoFire = !isAutoFire;
		}
	}
	else autoFireButtonHeld = false;

	if (isAutoFire || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (myWeapon != nullptr)
			myWeapon->update(state, stats.getAcc(), getRadius());
		//if (t <= 0) {
		//	t = stats.getShootCooldown();
		//	shoot(state);
		//}
	}

	if (mySpecial != nullptr) {
		setMana(std::min(1.0f, 1 - mySpecial->t / (stats.getSpecialMultiplier() * mySpecial->stats.baseReloadTime)));
	}

	bool useSpecial = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!spaceDown) useSpecial = true;
		spaceDown = true;
	}
	else spaceDown = false;

	if (mySpecial != nullptr)
		mySpecial->update(state, stats.getSpecialMultiplier(), useSpecial);

	// Face the mouse
	//sf::Vector2f mousePos = (sf::Vector2f)state->getMousePos();
	//mousePos -= state->getScreenCenter();
	//float angle = (float)atan2(mousePos.y, (double)mousePos.x);
	//rot = (float)(angle * 180 / util::PI);
	if (!state->isPaused)
		lookAt(state->getMousePosWorld());

	float prevR = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m.x = 1;
	}

	float realspd = stats.getSpeed();
	if (hasStatus(StatusEffect::SLOW)) realspd *= 0.5f;
	if (hasStatus(StatusEffect::PARALYZED)) realspd = 0.0f;
	if (hasStatus(StatusEffect::DASHING_5k)) realspd = 5000;
	if (hasStatus(StatusEffect::DASHING_15k)) realspd = 15000; //overrides paralysis / slow temporarily

	if (m.x != 0 && m.y != 0) m *= 0.75f;

	if (!state->isPaused)
		moveDisplacement(m * realspd);	
	velocity = m * realspd;

	snapToBorders(state);
	LivingObject::update(state);
}

// Handle dealing, not taking damage
// But we have nobody to damage so empty
void Player::collide(CircleObj *other) {
	
}

// Returns the new probability
float Player::upgrade(Upgrade type) {
	return 1;
	//switch (type) {
	//case Upgrade::BULLET_DAMAGE:
	//	bulletDamage += 0.5f;
	//	return 0.8f;
	//case Upgrade::RELOAD:
	//	reload *= 0.75f;
	//	return 0.75f;
	//case Upgrade::ACCURACY:
	//	accuracy *= 0.5f;
	//	shotGap *= 0.7f;
	//	return 0.6f;
	//case Upgrade::NUM_SHOTS:
	//	numShots++;
	//	return 0.5f;
	//case Upgrade::LIFE:
	//	maxLife += 5;
	//	lifeOn = maxLife;
	//	resizeLifeBar();
	//	// Todo; rescale
	//	return 0.7f;
	//case Upgrade::SPEED:
	//	spd *= 1.3f;
	//	return 0.6f;
	//}
	return 0.0f;
}


bool Player::isAlive(GameState *state) const {
	if (lifeOn < 0)
		state->playerDeath();
	return true;
}
