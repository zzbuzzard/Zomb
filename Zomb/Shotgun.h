#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
public:
	Shotgun();
	~Shotgun();
	void fire(GameState *state, float acc, float rad);
};

