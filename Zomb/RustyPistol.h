#pragma once
#include "Weapon.h"
class RustyPistol : public Weapon
{
public:
	RustyPistol();
	~RustyPistol();
	void fire(GameState *state, float acc, float rad);
};

