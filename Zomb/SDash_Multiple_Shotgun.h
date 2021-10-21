#pragma once
#include "Special.h"
class SDashMultipleShotgun : public Special
{
public:
	SDashMultipleShotgun();
	~SDashMultipleShotgun();
	void fire(GameState *state);
	void update(GameState *state, float intMultiplier, bool useSpecial);
private:
	void shotgun(GameState *state);
	float tx = 0;
	int ns = 0;
};

