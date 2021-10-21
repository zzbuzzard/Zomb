#include "pch.h"
#include "Media.h"
#include <iostream>

// 1) Enum and reference all textures by index in array
//    Advantage: they're all close together in memory, prevents pointer hopping when drawing the scene

sf::Font g_candara;
sf::Texture textures[NUM_TEXTURES];

//sf::Texture g_playerTexture, g_zombTexture, g_bulletTexture, g_runnerTexture, g_bigBoiTexture, g_bigBoiShotTexture,
//g_boss1Texture, g_scienceZombTexture, g_zapTexture, g_enemyShieldTexture, g_redSpikeTexture, g_zombFarmerTexture,
//g_reinforcedZombTexture,
//
//g_enemyFootTexture,
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
//g_buttonTexture, g_button2Texture, g_iconHead, g_iconMisc, g_iconTorso, g_iconFeet, g_iconWeapon;

void Media::LoadAssets() {
	for (int i = 0; i < NUM_TEXTURES; i++) textures[i] = sf::Texture();
	LoadFonts();
}

void Media::FinishUp() {
	textures[T_BUTTON].setSmooth(true);
	textures[T_BUTTON2].setSmooth(true);
	textures[T_HILLS_GG].setRepeated(true);
	textures[T_CAVE_GG].setRepeated(true);
}


// All have Textures/ at the start
std::string texturePaths[NUM_TEXTURES] = {
	"Textures/player.png","Textures/enemyfoot.png",
	
	"Textures/Enemies/zomb.png", "Textures/Enemies/runner.png", "Textures/Enemies/bigboi.png", "Textures/Enemies/reinforced_zomb.png", "Textures/Enemies/cave_thing.png",
	"Textures/Enemies/boss1.png", "Textures/Enemies/science_zomb.png", "Textures/Enemies/zomb_farmer.png", "Textures/Enemies/rock_golem.png",
	
	"Textures/bullet1.png", "Textures/bigboi_shot.png", "Textures/zap.png", "Textures/shield.png", "Textures/spike.png", "Textures/rock.png",
	
	"Textures/Crates/crate1.png", "Textures/Crates/crate2.png", "Textures/Crates/crate3.png", "Textures/Crates/crate4.png",
	
	"Textures/Items/rusty_pistol.png", "Textures/Items/pistol_400.png", "Textures/Items/lightning_gun_400.png", "Textures/Items/shotgun.png", "Textures/Items/electric_staff.png", "Textures/Items/earth_staff.png",
	"Textures/Items/cap.png", "Textures/Items/helmet.png", "Textures/Items/god_helm.png", "Textures/Items/shirt_400.png", "Textures/Items/ripped_shirt_400.png", "Textures/Items/wizard_hat.png", "Textures/Items/intricate_hat.png", "Textures/Items/cardboard_box.png", "Textures/Items/concrete_box.png", "Textures/Items/chainmail.png", "Textures/Items/heavy_armour.png", "Textures/Items/slime_armour.png", "Textures/Items/robe.png", "Textures/Items/intricate_robe.png", "Textures/Items/old_shoes.png", "Textures/Items/trainers.png", "Textures/Items/slimy_shoes.png", "Textures/Items/wooden_shield.png", "Textures/Items/scope.png", "Textures/Items/farmer_hat.png", "Textures/Items/textbook.png", "Textures/Items/wise_book.png",

	"Textures/cave_bg.png", "Textures/cave_fg.png", "Textures/rockTiles1.png",
	"Textures/hills_bg.png", "Textures/hills_fg.png", "Textures/grassTile1.png",

	"Textures/fade.png",

	"Textures/UI/button.png", "Textures/UI/button2.png", "Textures/Icons/icon_head.png", "Textures/Icons/icon_torso.png", "Textures/Icons/icon_feet.png", "Textures/Icons/icon_weapon.png", "Textures/Icons/icon_feet.png",
};

void Media::LoadNextTexture() {
	static int i = 0;
	textures[i].loadFromFile(texturePaths[i]);
	i++;
}

//void Media::LoadTextures() {
	//std::cout << "Loading textures" << std::endl;

	//textures[T_PLAYER].loadFromFile("Textures/player.png");

	//textures[T_ZOMB].loadFromFile("Textures/Enemies/zomb.png");
	//textures[T_RUNNER].loadFromFile("Textures/Enemies/runner.png");
	//textures[T_BIG_BOI].loadFromFile("Textures/Enemies/bigboi.png");
	//g_reinforcedZombTexture.loadFromFile("Textures/Enemies/reinforced_zomb.png");

	//g_enemyFootTexture.loadFromFile("Textures/enemyfoot.png");

	//g_boss1Texture.loadFromFile("Textures/Enemies/boss1.png");
	//g_scienceZombTexture.loadFromFile("Textures/Enemies/science_zomb.png");
	//g_zombFarmerTexture.loadFromFile("Textures/Enemies/zomb_farmer.png");

	//g_enemyShieldTexture.loadFromFile("Textures/shield.png");

	//g_bulletTexture.loadFromFile("Textures/bullet1.png");
	//g_bigBoiShotTexture.loadFromFile("Textures/bigboi_shot.png");
	//g_zapTexture.loadFromFile("Textures/zap.png");
	//g_redSpikeTexture.loadFromFile("Textures/spike.png");

	//g_crateTexture1.loadFromFile("Textures/Crates/crate1.png");
	//g_crateTexture2.loadFromFile("Textures/Crates/crate2.png");
	//g_crateTexture3.loadFromFile("Textures/Crates/crate3.png");
	//g_crateTexture4.loadFromFile("Textures/Crates/crate4.png");

	//g_caveBg.loadFromFile("Textures/cave_bg.png");
	//g_caveFg.loadFromFile("Textures/cave_fg.png");
	//g_caveGg.loadFromFile("Textures/rockTiles1.png"); g_caveGg.setRepeated(true);

	//g_hillsBg.loadFromFile("Textures/hills_bg.png");
	//g_hillsFg.loadFromFile("Textures/hills_fg.png");
	//g_hillsGg.loadFromFile("Textures/grassTile1.png"); g_hillsGg.setRepeated(true);

	//g_rustyPistolTexture.loadFromFile("Textures/Items/rusty_pistol.png");
	//g_pistolTexture.loadFromFile("Textures/Items/pistol_400.png");
	//g_lightningGunTexture.loadFromFile("Textures/Items/lightning_gun_400.png");
	//g_shotgunTexture.loadFromFile("Textures/Items/shotgun.png");
	//g_electricStaffTexture.loadFromFile("Textures/Items/electric_staff.png");

	//g_capTexture.loadFromFile("Textures/Items/cap.png");
	//g_helmetTexture.loadFromFile("Textures/Items/helmet.png");
	//g_vikingHelmetTexture.loadFromFile("Textures/Items/god_helm.png");
	//g_shirtTexture.loadFromFile("Textures/Items/shirt_400.png");
	//g_rippedShirtTexture.loadFromFile("Textures/Items/ripped_shirt_400.png");
	//g_wizardHatTexture.loadFromFile("Textures/Items/wizard_hat.png");
	//g_intricateHatTexture.loadFromFile("Textures/Items/intricate_hat.png");
	//g_cardboardBoxTexture.loadFromFile("Textures/Items/cardboard_box.png");
	//g_concreteBoxTexture.loadFromFile("Textures/Items/concrete_box.png");
	//g_chainmailTexture.loadFromFile("Textures/Items/chainmail.png");
	//g_heavyArmourTexture.loadFromFile("Textures/Items/heavy_armour.png");
	//g_slimeArmourTexture.loadFromFile("Textures/Items/slime_armour.png");
	//g_robeTexture.loadFromFile("Textures/Items/robe.png");
	//g_intricateRobeTexture.loadFromFile("Textures/Items/intricate_robe.png");
	//g_oldShoesTexture.loadFromFile("Textures/Items/old_shoes.png");
	//g_trainersTexture.loadFromFile("Textures/Items/trainers.png");
	//g_slimyShoesTexture.loadFromFile("Textures/Items/slimy_shoes.png");
	//g_farmerHatTexture.loadFromFile("Textures/Items/farmer_hat.png");
	//g_textbookTexture.loadFromFile("Textures/Items/textbook.png");
	//g_wiseBookTexture.loadFromFile("Textures/Items/wise_book.png");

	//g_woodenShieldTexture.loadFromFile("Textures/Items/wooden_shield.png");
	//g_scopeTexture.loadFromFile("Textures/Items/scope.png");

	//g_buttonTexture.loadFromFile("Textures/UI/button.png"); g_buttonTexture.setSmooth(true);
	//g_button2Texture.loadFromFile("Textures/UI/button2.png"); g_button2Texture.setSmooth(true);

	//g_iconFeet  .loadFromFile("Textures/Icons/icon_feet.png");
	//g_iconMisc  .loadFromFile("Textures/Icons/icon_feet.png");
	//g_iconHead  .loadFromFile("Textures/Icons/icon_head.png");
	//g_iconTorso .loadFromFile("Textures/Icons/icon_torso.png");
	//g_iconWeapon.loadFromFile("Textures/Icons/icon_weapon.png");

	//std::cout << "Textures loaded" << std::endl;
//}

void Media::LoadFonts() {
	g_candara = sf::Font();
	g_candara.loadFromFile("Fonts/candara.ttf");
}
