#pragma once
#include <tuple>
#include <string>
#include "Media.h"

// When adding a new level, you must add it to the bottom of the enum.
// The order that they show up in can be changed below (levelOrder)
enum LEVEL {
	L_HILLS,
	L_CAVE,
	L_HILLSTEST,

	L_NONE=-1
};

struct LevelAppearance {
	float mapSize;
	int mapGgRepeats;
	sf::Color outside;
	TEXTURE background;
	TEXTURE overlay;

	LevelAppearance(float mapSize_, TEXTURE background_, sf::Color outside_, int mapGgRepeats_, TEXTURE overlay_ = T_NONE)
		: mapSize(mapSize_), background(background_), outside(outside_), mapGgRepeats(mapGgRepeats_), overlay(overlay_)
	{
	}
};

void saveMaxWave(LEVEL level, int wave);
void loadMaxWaves();
int getMaxWave(LEVEL level);

bool isUnlocked(LEVEL level);

#define NUM_LEVELS 3
#define pli std::pair<LEVEL, int>

//                   name,     bg,       foreground,  {map size, in-game bg, bg col, in-game bg tile}   unlock requirement
typedef std::tuple<std::string, TEXTURE, TEXTURE, LevelAppearance, std::vector<pli> > levelType;
extern levelType levelTypes[NUM_LEVELS];
extern LEVEL levelOrder[NUM_LEVELS];

// Max wave, 1-based indexing
extern int levelMaxWaveBeaten[NUM_LEVELS];