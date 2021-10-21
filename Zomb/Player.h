#pragma once
#include "LivingObject.h"
#include <SFML/Graphics.hpp>
#include "Stats.h"
#include "Weapon.h"
#include "Special.h"

enum class Upgrade;

// Variables that define character that can be changed by upgrades
//  Number of shots, shot separation
//  Accuracy of shots
//  Damage of shots
//  Max life (in LivingObject)
//  Movement speed
//  Special (space):
//   Start as nothing, level 2
//   Can be one of a few:
//    Burst shot
//    Knockback
//    Grenade
//    Speed boost
//    Reload time decrease
//    Invincible / high defence for a few seconds
//    Slow

extern float playerRadius;

class Player : public LivingObject
{
public:
	Player(const Stats &stats, Weapon *weapon, Special *special);
	~Player();

	void update(GameState *state);
	void collide(CircleObj *other);
	float upgrade(Upgrade type);
	sf::Vector2f getVelocity() { return velocity; }
	const Stats &getStats() { return stats; }
	bool isAlive(GameState *state) const;
	void takeDamage(float dmg);
	void copyFrom(Player *p);
private:
	//void shoot(GameState *state);
public:
	//float spd = 500.0f;
	//float reload = 0.12f;

	Weapon *myWeapon;
	Special *mySpecial;

	//float bulletDamage = 1.0f;
	//int numShots = 1;
	//float shotGap = 1.0f; // angle in radians between furthest left and right shooter
	
	//float accuracy = 0.2f; // angle in radians += of every shot
private:
	Stats stats;

	//float t = 0.0f;
	sf::Vector2f velocity; // only used for position prediction by enemies
	
	bool autoFireButtonHeld = false;
	bool isAutoFire = false;

	bool spaceDown = false;
};

