#pragma once
#include <tuple>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Media.h"

// A special has a list of unlock requirements
//  These are the IDs of other specials (enum)
// There may also be a list of level unlock requirements
//  These are pairs: (level ID (enum), level that must be reached)

// 1) The above information is stored in an array of typedef_specials, just like items.
// 2) We also store an enum stating our current special.
// 3) SpecialController provides a function which checks if a given special is unlocked
// 4) When we want to get the current special, we use a switch case on the enum with the actual type.

enum SPECIAL : int;
enum LEVEL : int;
#define NUM_SPECIALS 5

// A special has 1 or 2 parents
// A special has 1 level requirement

//                   Name        Desc   Requirements (first is parent)  texture  COST, Level  Wave requirement
typedef std::tuple<std::string, std::string, std::vector<SPECIAL>, TEXTURE,  int, std::pair<LEVEL, int> > specialType;

extern specialType specialTypes[NUM_SPECIALS];

class Special;
Special *getSpecialFrom(SPECIAL a);
Special *getSpecial();
const specialType &getSpecialType();

void loadUnlockedSpecials();
bool specialUnlocked(SPECIAL specialIndex);
bool specialEquipped(SPECIAL specialIndex);
void saveUnlockedSpecials();
void equipSpecial(SPECIAL equip);
void buySpecial(SPECIAL equip);

bool isUnlockable(SPECIAL specialIndex);

class SpecialController
{
public:
	SpecialController();
	~SpecialController();
};




