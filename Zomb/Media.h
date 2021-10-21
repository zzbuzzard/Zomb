#pragma once
#include <SFML/Graphics.hpp>

enum TEXTURE {
	T_PLAYER, T_ENEMY_FOOT,

	T_ZOMB, T_RUNNER, T_BIG_BOI, T_REINFORCED_ZOMB, T_CAVE_THING,
	T_BOSS1, T_SCIENCE_ZOMB, T_ZOMB_FARMER, T_ROCK_GOLEM,

	T_BULLET, T_BIG_BOI_SHOT, T_ZAP, T_ENEMY_SHIELD, T_RED_SPIKE, T_ROCK,
	
	T_CRATE1, T_CRATE2, T_CRATE3, T_CRATE4,
	T_RUSTY_PISTOL, T_PISTOL, T_LIGHTNING_GUN, T_SHOTGUN, T_ELECTRIC_STAFF, T_EARTH_STAFF,
	T_CAP, T_HELMET, T_VIKING_HELMET, T_SHIRT, T_RIPPED_SHIRT, T_WIZARD_HAT, T_INTRICATE_HAT, T_CARDBOARD_BOX, T_CONCRETE_BOX, T_CHAINMAIL,
	T_HEAVY_ARMOUR, T_SLIME_ARMOUR, T_ROBE, T_INTRICATE_ROBE, T_OLD_SHOES, T_TRAINERS, T_SLIMY_SHOES, T_WOODEN_SHIELD, T_SCOPE,
	T_FARMER_HAT, T_TEXTBOOK, T_WISE_BOOK,

	T_CAVE_BG, T_CAVE_FG, T_CAVE_GG,
	T_HILLS_BG, T_HILLS_FG, T_HILLS_GG,

	T_FADE_CIRCLE,

	T_BUTTON, T_BUTTON2, T_ICON_HEAD, T_ICON_TORSO, T_ICON_FEET, T_ICON_WEAPON, T_ICON_MISC,

	T_NONE = -1
};
#define NUM_TEXTURES 63

extern sf::Font g_candara;

extern sf::Texture textures[NUM_TEXTURES];
extern std::string texturePaths[NUM_TEXTURES];

//extern sf::Texture g_playerTexture, g_zombTexture, g_bulletTexture, g_runnerTexture, g_bigBoiTexture, g_bigBoiShotTexture,
//g_boss1Texture, g_scienceZombTexture, g_zapTexture, g_enemyShieldTexture, g_redSpikeTexture, g_zombFarmerTexture,
//g_reinforcedZombTexture,
//
//g_enemyFootTexture,
//
//g_crateTexture1, g_crateTexture2, g_crateTexture3, g_crateTexture4,
//
//g_pistolTexture, g_lightningGunTexture, g_electricStaffTexture, g_shotgunTexture,
//g_vikingHelmetTexture, g_shirtTexture, g_rippedShirtTexture, g_helmetTexture,
//g_capTexture, g_wizardHatTexture, g_intricateHatTexture, g_cardboardBoxTexture,
//g_concreteBoxTexture, g_chainmailTexture, g_heavyArmourTexture, g_slimeArmourTexture,
//g_robeTexture, g_intricateRobeTexture, g_oldShoesTexture, g_trainersTexture, 
//g_slimyShoesTexture, g_woodenShieldTexture, g_scopeTexture, g_rustyPistolTexture,
//g_farmerHatTexture, g_textbookTexture, g_wiseBookTexture,
//
//g_caveBg, g_caveFg, g_hillsBg, g_hillsFg,
//
//g_caveGg, g_hillsGg,
//
//g_buttonTexture, g_button2Texture, g_iconHead, g_iconTorso, g_iconFeet, g_iconWeapon, g_iconMisc;

class Media
{
public:
	static void LoadAssets();
	static void LoadNextTexture();
	static void FinishUp();
private:
	//static void LoadTextures();
	static void LoadFonts();
};

