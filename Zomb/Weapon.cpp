#include "pch.h"
#include "Weapon.h"
#include "GameState.h"

Weapon::Weapon(WeaponStats wStats) : weaponStats(wStats) {
	t = 1 / weaponStats.shotsPerSecond;
}

Weapon::~Weapon()
{
}


sf::Vector2f Weapon::getRelativeMousePos(GameState *state) {
	return (sf::Vector2f)state->getMousePos() - state->getScreenCenter();
}

sf::Vector2f Weapon::getCircPoint(float angle, float rad) {
	return sf::Vector2f(cos(angle)*rad, sin(angle)*rad);
}

void Weapon::update(GameState *state, float accuracy, float playerRad) {
	t -= deltaTime;
	while (t < 0) {
		t += 1/weaponStats.shotsPerSecond;
		fire(state, accuracy, playerRad);
	}
}