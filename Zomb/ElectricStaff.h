#pragma once
#include "Weapon.h"
class ElectricStaff : public Weapon
{
public:
	ElectricStaff();
	~ElectricStaff();
	void fire(GameState *state, float acc, float rad);
};

