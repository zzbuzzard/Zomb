#pragma once
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>
#include "Stats.h"
#include "Media.h"

enum ItemRarity
{
	COMMON,
	UNCOMMON,
	RARE,
	LEGENDARY
};

enum EquipType {
	E_WEAPON,
	E_HELMET,
	E_TORSO,
	E_MISC,
	E_SHOES,
	E_NONE = -1
};

enum ITEMS {
	I_RUSTY_PISTOL,
	I_PISTOL,
	I_SHOTGUN,
	I_ELECTRIC_STAFF,
	I_EARTH_STAFF,

	I_CAP,
	I_HELMET,
	I_VIKING_HELMET,
	I_WIZARD_HAT,
	I_INTRICATE_HAT,
	I_FARMER_HAT,

	I_RIPPED_SHIRT,
	I_SHIRT,
	I_CARDBOARD_BOX,
	I_CONCRETE_BOX,
	I_CHAINMAIL,
	I_HEAVY_ARMOUR,
	I_SLIME_ARMOUR,
	I_ROBE,
	I_INTRICATE_ROBE,

	I_OLD_SHOES,
	I_TRAINERS,
	I_SLIMY_SHOES,

	I_WOODEN_SHIELD,
	I_SHIELD,
	I_SCOPE,
	I_TEXTBOOK,
	I_ANCIENT_BOOK,
};
#define NUM_ITEMS 28
#define INV_MAX_SIZE 20

class Player;
class Weapon;
class GameState;

// String (name)
// Texture* (appearance)
// EquipType (where it is equipped, E_NONE if unequipable)
// Stats (bonus when worn)
// ItemRarity (rarity level - 0..3)
// Int (sell price)
// String (description, often empty)
typedef std::tuple<std::string, TEXTURE, EquipType, Stats, ItemRarity, int, std::string> item;

extern item itemTypes[NUM_ITEMS];
