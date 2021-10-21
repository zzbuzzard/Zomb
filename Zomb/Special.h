#pragma once
#include <SFML/Graphics.hpp>

class GameState;

// Best to have a struct in case we decide on a new thing that all specials must have
// E.g. mp cost, boolean about something
struct SpecialStats {
	float baseReloadTime;
	SpecialStats(float baseReloadTime_) : baseReloadTime(baseReloadTime_) {}
	SpecialStats() {}
};

class Special
{
public:
	Special(SpecialStats specialStats);
	~Special();

	virtual void fire(GameState *state) = 0;
	virtual void update(GameState *state, float intMultiplier, bool useSpecial);
private:
public:
	SpecialStats stats;
	float t;
private:
};

// Specials are used with space
// They have a base cooldown, then intelligence provides a multiplier
//  takes intelligence multiplier as an input


