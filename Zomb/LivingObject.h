#pragma once
#include "CircleObj.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "FootWalk.h"

const float pixelsPerUnitLife = 10.0f, lifeBarHeight = 18.0f, lifeBarSeparation = 22.0f;

const float manaSizeMul = 0.8f;

// 700.0f
inline float lifeBarMaxWidth(const float &radius);

enum class StatusEffect {
	SLOW,
	PARALYZED,
	POISONED,
	DASHING_15k, //sets speed
	DASHING_5k,

	NONE=-1,
};

struct WeaponStats;

class LivingObject : public CircleObj
{
public:
	LivingObject(ObjectType myType, sf::Vector2f pos, TEXTURE texture, float rad, float life, float imageRadius = -1);
	~LivingObject();

	void update(GameState *state);
	void draw(sf::RenderWindow *window) const;
	float takeDamage(float dmg);
	void applyStatus(StatusEffect status, float time);
	bool isAlive(GameState *state) const;
	void resizeLifeBar();
	void snapToBorders(GameState *state);

	float lookAt(sf::Vector2f position); // returns angle in radians to player
	void lookDirection(float ang); // in radians
	void moveDisplacement(sf::Vector2f disp);
	void moveTowards(sf::Vector2f point, float spd);

	void shootNormal(GameState *state, sf::Vector2f pos, const WeaponStats &stats, float acc=0);
	void shootNormal(GameState *state, float angle, const WeaponStats &stats, float acc=0);
	void shootNormalShotgun(GameState *state, int num, const WeaponStats &stats);

	float getLifeOn() const;
protected:
	bool invincible = false;

	bool hasStatus(StatusEffect effect) {
		for (const auto &i : statusEffects) {
			if (i.first == effect) return true;
		}
		return false;
	}

	void spawnShields(GameState *state, int count, int *shieldCounter, float orbitRadiusMultiplier, float life, float spd);
	void setLifeBarLowOpacity(bool isLow);

	// 1 is max, 0 is min
	void setMana(float t);

	bool hasFeet = true;
	FootWalk feet;

private:
public:
protected:
	bool hasMana = false;

	float maxLife;
	float lifeOn;

	std::vector<std::pair<StatusEffect, float> > statusEffects;
private:
	bool lifebarLowOpacity;
	int numBars;
	std::vector<sf::RectangleShape> lifeBarBoxes, lifeBars;
};

