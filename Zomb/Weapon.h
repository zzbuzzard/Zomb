#pragma once
#include <SFML/Graphics.hpp>
#include "LivingObject.h"

class GameState;

struct WeaponStats {
	float shotsPerSecond;
	float dmg, spd, lifetime, rad, imageRad;
	TEXTURE texture;

	StatusEffect effect;
	float effectTime;

	WeaponStats(TEXTURE texture_, float dmg_, float spd_, float range_, float shotsPerSecond_, float rad_, float imageRad_ = -1,
		float effectTime_ = 0, StatusEffect effect_ = StatusEffect::NONE) :
		texture(texture_), dmg(dmg_), spd(spd_), rad(rad_), imageRad(imageRad_), shotsPerSecond(shotsPerSecond_),
		effectTime(effectTime_), effect(effect_)
	{
		lifetime = range_ / spd;
	}
	WeaponStats() {}
};

class Weapon
{
public:
	Weapon(WeaponStats wStats);
	~Weapon();

	virtual void fire(GameState *state, float acc, float rad) = 0;

	void update(GameState *state, float accuracy, float playerRadius);
	sf::Vector2f getRelativeMousePos(GameState *state);
	sf::Vector2f getCircPoint(float angle, float rad);
private:
public:
	float t;
	WeaponStats weaponStats;
private:
};

// Weapons need to store
//  Bullet damage
//  Bullet speed
//  Bullet texture, radius and imageRadius
//  Bullet range => bullet life time

//  Fire method.


// A weapon has a 
//   Bullet texture
//   Bullet radius
//   Bullet fire type : This is an enum representing a class. Type examples are normal, curved, orbital, splits into more type, ...
//   Bullet damage
//   Base reload speed - oh wait, this is just dexterity
//   Number of shots
//   Fire function ( ) ? Would be useful for doing weird shit

// Two ways of doing projectiles
//  1) Separate class for each one, with hardcoded values
//  2) Different movement types, and they take damage, speed, texture, radius, imageradius as inputs.

// Ok. Two ways of doing weapons.
//  1) WeaponStats. Categorise everything.
//  2) One class per weapon, inheriting from Weapon. 
//     Each one provides a fire function, that takes state as input. 
//     Weapon could provide some standard functionality (shoot, shotgun, ...)


// myWeapon = getWeapon(id)
// switch statement and return the right one

// weapon update(state) : 
//  Takes some time off. This is handled by the base class. Constructor requires the acc and dex stats.

// weapon fire(state) :
//  Fire a bullet. Pure virtual function in base class, as each one will be different.
//  However, weapon can provide some functions that allow you to get some stuff.

// Projectiles can also have alt fire, with right click


