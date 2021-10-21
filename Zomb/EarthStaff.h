#pragma once
#include "Weapon.h"
class EarthStaff : public Weapon
{
public:
	EarthStaff();
	void fire(GameState *state, float acc, float rad);
};

