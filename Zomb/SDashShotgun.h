#pragma once
#include "Special.h"
class SDashShotgun :
	public Special
{
public:
	SDashShotgun();
	~SDashShotgun();
	void fire(GameState *state);
};

