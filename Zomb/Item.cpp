#include "pch.h"
#include "Item.h"
#include "Media.h"

#define pb std::pair<int, bool>

//	item("Paralysis defender", &g_lightningGunTexture, E_WEAPON, Stats(0, 0, 5, 0, 0), 1, 500),

// Pistol : Big boi
// Cardboard box : Big boi
// Wooden shield : Runner
// Old shoes : Zomb
// Cap : Zomb

item itemTypes[NUM_ITEMS] = {
	item("Rusty pistol", T_RUSTY_PISTOL, E_WEAPON, Stats(0, 0, 0, -5, 0), COMMON, 5, "You've had this for decades."),
	item("Pistol", T_PISTOL, E_WEAPON, Stats(0, 0, 0, 0, 0), UNCOMMON, 150, ""),
	item("Shotgun", T_SHOTGUN, E_WEAPON, Stats(0, 0, 0, 0, 0), UNCOMMON, 300, "Fires bursts of 20 shots."),
	// nb nd
	item("Electric staff", T_ELECTRIC_STAFF, E_WEAPON, Stats(0, 0, 0, 0, 5), RARE, 2000, "Fires electric bolts which paralyze enemies."),
	// nb
	item("Earth staff", T_EARTH_STAFF, E_WEAPON, Stats(0, 0, 0, 0, 0), RARE, 2000, "Fires boulders that bounce between enemies"),

	item("Cap", T_CAP, E_HELMET, Stats(5, 3, 0, 5, 0), COMMON, 25, ""),
	// nb
	item("Helmet", T_HELMET, E_HELMET, Stats(20, 8, -2, 0, 0), COMMON, 30, ""),
	// nb nd
	item("Viking helmet", T_VIKING_HELMET, E_HELMET, Stats(40, 10, -3, -10, 0), UNCOMMON, 200, ""),
	// nb nd
	item("Wizard hat", T_WIZARD_HAT, E_HELMET, Stats(0, 0, 3, 5, 8), COMMON, 35, "Maybe this will cheer you up."),
	// nb nd
	item("Intricate hat", T_INTRICATE_HAT, E_HELMET, Stats(10, 5, -3, -2, 15), UNCOMMON, 200, ""),
	// nb
	item("Possessed farmer's hat", T_FARMER_HAT, E_HELMET, Stats(0, -10, 30, 30, 30), RARE, 700, "An evil soul lives on in this hat"),

	// nd
	item("Ripped shirt", T_RIPPED_SHIRT, E_TORSO, Stats(5, 2, 0, 0, 0), COMMON, 10, ""),
	item("Shirt", T_SHIRT, E_TORSO, Stats(10, 3, 2, 0, 0), COMMON, 50, ""),
	item("Cardboard box", T_CARDBOARD_BOX, E_TORSO, Stats(25, 15, -12, -10, 0), COMMON, 60, "You feel safe in here."),
	// nb nd
	item("Concrete box", T_CONCRETE_BOX, E_TORSO, Stats(50, 45, -30, -20, 0), UNCOMMON, 275, "This thing sure is heavy."),
	// nb
	item("Chainmail", T_CHAINMAIL, E_TORSO, Stats(30, 20, -5, 0, 0), UNCOMMON, 250, ""),
	// nb nd
	item("Heavy armour", T_HEAVY_ARMOUR, E_TORSO, Stats(40, 35, -10, -3, 0), RARE, 650, ""),
	// nb nd
	item("Slime armour", T_SLIME_ARMOUR, E_TORSO, Stats(0, 15, 20, 0, 5), UNCOMMON, 350, "Ew."),
	// nb
	item("Robe", T_ROBE, E_TORSO, Stats(10, 5, 0, 5, 15), UNCOMMON, 400, ""),
	// nb nd
	item("Intricate robe", T_INTRICATE_ROBE, E_TORSO, Stats(16, 8, 15, 20, 30), RARE, 650, ""),

	item("Old shoes", T_OLD_SHOES, E_SHOES, Stats(0, 4, 8, 0, -2), COMMON, 10, ""),
	item("Trainers", T_TRAINERS, E_SHOES, Stats(0, 2, 15, 0, 0), UNCOMMON, 120, ""),
	// nb nd
	item("Slimy shoes", T_SLIMY_SHOES, E_SHOES, Stats(0, -5, 25, 0, -10), UNCOMMON, 1, "Why the hell did you pick these up?"),

	item("Wooden shield", T_WOODEN_SHIELD, E_MISC, Stats(0, 12, -5, 0, -2), COMMON, 50, ""),
	// nb nd
	item("Shield", T_ENEMY_SHIELD, E_MISC, Stats(25, 10, -4, -4, 0), COMMON, 100, ""),
	// nd
	item("Scope", T_SCOPE, E_MISC, Stats(0, 0, -5, 30, 5), UNCOMMON, 250, ""),
	item("Textbook", T_TEXTBOOK, E_MISC, Stats(0, 0, 0, 5, 30), COMMON, 60, ""),
	// nb nd
	item("Book of ancient wisdoms", T_WISE_BOOK, E_MISC, Stats(0, 0, 5, 10, 60), RARE, 600, "It's completely unintelligible"),
};

