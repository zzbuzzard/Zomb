#include "pch.h"
#include "Special.h"
#include "GameState.h"
#include <iostream>
Special::Special(SpecialStats specialStats) : stats(specialStats)
{
	t = -10;
}


Special::~Special()
{
}

void Special::update(GameState *state, float intMultiplier, bool useSpecial) {
	if (t == -10) t = intMultiplier * stats.baseReloadTime;
	t -= deltaTime;
	if (useSpecial && t < 0) {
		t = intMultiplier * stats.baseReloadTime;
		fire(state);
	}
}
