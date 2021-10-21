#pragma once
#include "Special.h"
class SDash : public Special
{
public:
	SDash();
	~SDash();
	void fire(GameState *state);
};

