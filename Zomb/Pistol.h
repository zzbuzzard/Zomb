#pragma once
#include "Weapon.h"
class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol();
	void fire(GameState *state, float acc, float rad);
};

