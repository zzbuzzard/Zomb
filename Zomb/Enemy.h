#pragma once
#include "LivingObject.h"
#include <SFML/Graphics.hpp>

#include "Inventory.h"
#include "Controller.h"
#include "EnemyStats.h"

class Enemy : public LivingObject
{
public:
	Enemy(sf::Vector2f pos, TEXTURE texture, bool dropLoot, const EnemyStats *enemyStats_, float radius, float imageRadius = -1);
	//Enemy(sf::Vector2f pos, sf::Texture *texture, bool dropLoot, int coins, float radius, float speed, float life, float dmg, float imageRadius = -1);
	~Enemy();

	void collide(CircleObj *other);
	void update(GameState *state);
	void moveBy(const sf::Vector2f &displacement);
	void draw(sf::RenderWindow *window) const;

	float takeDamage(float dmg);

	void handleDeath(GameState *state); //you'll get over it in time bro <3
private:
	void spawnCrate(GameState *state);
public:
	const EnemyStats *enemyStats;
protected:
	bool isStatic = false;
	float spd;

	std::vector<ITEMS> *dropList = nullptr;
	std::vector<int> *dropListProb = nullptr;
private:
	bool dropsLoot;
	//int dropCoins;
	//const float collideDmg;
};

// When an enemy dies, it loops through its dropList and takes a chance for each one.
// Droplist should be sorted good to bad, if there are multiple drops (not a great idea, generally)
// It adds the ones it picks to a list.
// If the list has length > 0 ie there are drops
//   Make a Crate object, with the list as input. Add the crate object to objects.


