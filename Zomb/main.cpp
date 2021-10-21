#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Anim.h"
#include "Media.h"

#include "Controller.h"
#include "Inventory.h"

#include "GameState.h"
#include "LevelSelectState.h"
#include "InventoryState.h"
#include "LoadingState.h"
#include "SpecialUpgradeTreeState.h"

// Documentation:
//   Items are defined in Item.h/cpp
//   Levels are defined in Levels.h/cpp
//   Enemy waves are defined in GameState.h/cpp
//   Textures and fonts are defined in Media.h/cpp
//   Specials are defined in SpecialController.h/cpp

//  General overview:
//   There is one active State at a time. This could be GameState, InventoryState, ...
//   And it has functions called by the game loop (just below) such as draw, update, resize...
//   GameState is the complex one.
//    All game objects inherit from CircleObj, directly or indirectly
//    Key subclasses: Enemy, Projectile, Player.

// Game final goal:
//   Level system: 
//     30 Waves. Boss at 10, 20, 30. Complete level 20 to unlock the next area. 
//   Characters:
//     Characters appear in certain waves.
//     They will have some dialogue.
//     They then either spawn and need protecting

// Todo
//  BOSS1 NEEDS DROPS
//  ROCKGOLEM NEEDS MAKING + DROPS
//  SCIENCEZOMB NEEDS MOVING + DROPS
//  OTHER BOSSES
//  Bestiary where you can see drops and stats of different enemies
//  Upgrade specials. Otherwise, after nearly beating a wave but dying, you feel like you gain nothing.
//   So money has to be more important. 
//  Restrict weapon changes on in-game inventory?
//  Currency image
//  UI when you earn money in-game. Text appears 1) above you or 2) above the deceased
//  Inventory save/load needs to be encrypted, or verified (using hash, whatever). Currently you can just open up the text file and fuck with it.
//     (Inventory, Coins, Level unlocks, Special unlocks)

// Todo: Possibly
//  Death screen is ugly. Look at some other games, talk to Hannah, change it. Maybe just scrap the red screen.
//  Crates can overlap and then the UI overlaps.
//    Either make them collide (interesting idea) or new drops land in crates that are already there
//  Better UI for locked levels? Lock symbol?

//  Rectangular objects that can form part of a map
//  Hannah doesnt like the health bars ;(

// Specials: MINES AND STUFF

using std::cout;
using std::endl;

const sf::Color background = sf::Color(100, 100, 100);

void Normalize(sf::Vector2f &v) {
	float m = sqrt(v.x*v.x + v.y*v.y);
	v.x /= m;
	v.y /= m;
}

// HOWEVER, IN RELEASE MODE:
// Check all pairs:
//  1250 : 90fps
//  2470 : 30fps
// Other method:
//  1250 : 174fps         Holy shit
//  6000 : 30fps          Amazing

// This was really early on, so a *lot* less stuff was happening. Worth retrying now.

int main()
{
	Media::LoadAssets();

	loadMaxWaves();
	loadCoins();
	loadUnlockedSpecials();

	// DEBUG ONLY
	auto style = sf::Style::Default;
	//auto style = sf::Style::Fullscreen;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Zomb", style);
	window.setVerticalSyncEnabled(true);
	sf::View view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	float aspect = window.getSize().x / (float)window.getSize().y;
	view.setSize(VIEW_HEIGHT * aspect, VIEW_HEIGHT);

	window.setView(view);

	sf::Clock clock;
	inventory = new Inventory();

	//g_state = new LevelSelectState(&window);
	//g_state = new InventoryState(&window, false);
	//g_state = new SpecialUpgradeTreeState(&window);
	g_state = new LoadingState(&window);

	// Main loop
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds() * timeScale;

		// Lag mode when you press space
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		//	int x = (int)(220 * deltaTime);
		//	for (int i = 0; i < 10000000; i++) {
		//		x++;
		//		if (x % 7482 == 0) {
		//			x += 6;
		//		}
		//	}
		//	if (x == 534) {
		//		cout << "haha what" << endl;
		//	}
		//}

		sf::Event event;
		while (window.pollEvent(event))
 		{
			switch (event.type) {
				float aspect;
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				aspect = window.getSize().x / (float)window.getSize().y;
				view.setSize(VIEW_HEIGHT * aspect, VIEW_HEIGHT);
				window.setView(view);
				g_state->resize(&view);
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))window.close();

		g_state->update();
		view.setCenter(g_state->whereToCenter());
		window.setView(view);
		g_state->draw(&view);
		window.display();
	}

	return 0;
}


// New game concept:
//  You have a permanent inventory that you keep after death.
//  There's a menu, then you have the choice between different locations. You start with 1 or 2 unlocked.
//  You level up slowly to a maximum level.
//  You get gear drops during the waves which you keep forever.
//  You add to inventory etc and can equip new stuff. There are also rare drops from specific enemies, especially bosses.
//  You beat locations and unlock new ones immediately, though it is not 1 -> 1.
//  There are also locations that unlock only when you hit a certain level, or find a certain rare drop (e.g. lab key -> underground lab)

// 30 Waves, then you unlock the sick 40th wave after beating the game or something
// LEVEL CONCEPTS:
//  Countryside / hills
//  Cave
//  Prison
//  Zoo / wilderness (animal place)
//  Volcano
//  Lab  and an extra secret lab sequel
//  Sewer

// STATS:
//  Health (HP)
//  Defense (damage multiplier)
//  Agility (speed)
//  Accuracy
//  Intelligence (special reload time - multiplier)

// When player is made, he sets his base stats using Controller.

// EQUIP LOCATIONS:
//  Face / head : Hats, helmets
//  Torso : Armor
//  Feet : Shoes
//  Hands: Weapon in one, misc in other (e.g. ring)
//  Special : Special items

// Various item concepts
//  Shoes: skis, speedy running shoes, fire retardant, slippers, slippery socks
//  Torso: 
//  Head:  

// Weapon concepts:
//  Pistol
//  Shotgun: needs override
//  Machine gun: +30 dex
//  Swarm controller. A swarm of little flying dudes follows your mouse. Needs override
//  Laser gun: enemy piercing shots
//  Bad idea: shotguns out eveywhere
//  Cosmic power: asteroids shoot out in a spiral around you
//  Homing missile launcher
//  Grenade launcher: splash damage
//  Shrapnel gun: Shoots out a blob that bursts into bullets
//  Satan's staff: Fires inaccurate bursts of spikes, and occasionally shotguns
//  Ice wand: Fires icy spikes that slow enemies
//  Thunder staff: Fires an electric thing that bounces between enemies and paralyzes them momentarily.


// MISC ITEM CONCEPTS:
//  Healthbox: Gives you one max heal per game. Could be a special I guess
//  Radar: Tells you what zombies are coming next, how many, and when
//  Holy something: Increases max hp
//  Various rings

// Specials:
//   Grenade -> Bomb
//   Knockback
//   Burst shot
//   Mines
//   Shotgun like boss2
//   Speed boost
//   Reload time decrease temporarily
//   Invincible / high defence for a few seconds
//   Slow enemies
//   Apply debuffs: Slow, paralyze (sick electric animation), etc
//    Note that bosses currently dont really get status effected

// Enemies
//  Zombie: Just a little green man. Walks towards you slowly.
//  Runner zombie: Moves a lot faster, but a bit weaker. Faster than player.
//  Big boi: Fat boi, slow but throws shit at you that slows you down
//  Fortified zombie: Slightly bigger, tougher zombie

//  Cave thing: Walks slowly until you're close then it sprints

//  Monstrosity: Huge ugly thing, runs at you but takes a while to change direction
//  Electrified zombie: Shoots zaps of electricity that paralyze you.
//  Spirit: floating wispy boi, shoots at you intelligently (predicts direction)
//  Shielder zomb: Big shield in front of it, takes a while to destroy. 
//  Parasite: Tiny, hooks onto another zombie and makes them faster and stronger
//  Demon: Once he gets close to you, speeds up massively
//  Zombie policeman: Shoots at you but accuracy is poor

// Boss concepts

// Grasslands
// Farmer zombie (ZombieFarmer):
//  Phase 1: Shoots his shotgun at you
//  Phase 2: Shotguns outwards and runs at you, spawning enemies

// Rotten monstrosity (Boss1):
//  Phase 1: Charges at you intelligently.
//  Phase 2: Shoots slowing bullets at you and walks at you

// Mutated bull:
//  

// Cave
// Rock golem:
//  Phase 1: Moves slowly towards player, firing rocks stupidly.
//   Slow moving enemies spawn from the outside constantly.
//  Phase 2: Fires 3 bursts of rocks intelligently, then pauses and walks towards you. Repeats.
//  Phase 3: Spawns shields around body and walks towards you, enemies spawn in again.

// Rock worm:
//  Phase 1: Moves around the outside of the room. Only head vulnerable. Spawns in enemies. 
//  Phase 2: Spirals in towards the middle. Only head vulnerable.
//   Once it reaches the middle, 
//  Phase 3: Charges towards player, but it can only turn slowly. When it hits the wall, it changes direction.
//   Whole body is vulnerable, and not the head.
//   Once only the head remains,
//  Phase 4: Invincible, and the head grows.
//  Phase 5: Fires rocks at the player and slowly moves towards it until death.

// Ancient spirit:
//  

// DONE
// Deformed science zombie:
//  Phase 1: Shoots electric bolts at you but with terrible accuracy. Stands in middle. 
//  Phase 2: Teleports randomly a few times, each time shooting out damaging bullets. Eventually runs at you, shooting electric behind.
//            Stops running when he hits you or after a few seconds.
//  Phase 3: Spawns spinning shields and becomes invincible. Runner zombies spawn in continuously. Shoots electric bursts at you intelligently.
//  Phase 4: Runs away from you, firing damaging bullets with terrible accuracy.

// Necromancer:
//   Phase 1: Stands in middle and shoots damaging stuff intelligently at you
//   Phase 2: Spawns in zombies from perimeter at a constant rate. Shoots fast non-intelligent bursts at you and walks towards you.
//   Phase 3: Fires homing bullets at you which you have to shoot down. A dead boss1 appears next to her and she revives it slowly.
//            The quicker you end phase 3, the lower life the boss 1 has.
//   Phase 4: Runner zombies spawn at a constant rate while she is alive. She runs away from the player and shoots intelligently when within range.

// Witch:
//   Phase 1: Flies in large circles around you, exiting through the walls if need be. Fires at you.
//   Phase 2: Flies to middle then lands. Shoots out a spread shot of slowing bullets.
//   Phase 3: Walks towards you, firing bullet bursts
//   Phase 4: Spawns loads of fake witches and they all fly about. They all shoot rarely.
//   Phase 5: Remove all fake witches. Lands in middle and stands still shooting intelligently at you. Runners spawn.

// Behemoth: Massive zombie
//   Phase 1: Walks at you slowly. Spawns in other enemies.
//   Phase 2: Spawns a fuck tonne of zombies around him, then shoots a fuck tonne of poison bullets randomly. Stands in middle stationary.
//   Phase 3: Glows red and sprints at you, rotating slowly though. 

// Satan final boss :
//   Phase 1 : Stands in middle and demons spawn at edges. Satan shoots groups of spikes at you intelligently.
//   Phase 2 : Runs at you, dashing to the side when hit. When he gets to you, deals big damage and smashes you away.
//   Phase 3 : Spinning shields spawn around him. Invincible until they all die. He fires all over the place and enemies spawn.
//   Phase 4 : Spawns enemies around him and shoots single big fire shots at you intelligently. Walking towards you.
//   Phase 5 : Moves to middle, and grows in size for a few seconds while shooting little fire shots randomly. Invincible.
//   Phase 6 : Shoots fast fire bullets either side of you, closing in, trapping you. Stays in middle
//             spawns a number of demons in front of it, which you have to kill. If you get em all then he is stunned for a sec.
//   Phase 7 : Dashes at you intelligently like boss1. Each time he sprints, he fires a shotgun of fireballs.
//   Phase 8 : Walks at you, firing spikes unintelligently but loads. Demons spawn at edges.
//   Phase 9 : All enemies die, he shrinks to your size. Then he runs at you firing intelligently and dashing to walls, sometimes shotgunning
//   Phase 10: Dramatic death

// HANNAH BOSS CONCEPTS :
//   Big sombrero boss
//   Mutated animal thing

// Upgrade concepts
//  Shot damage up
//  Reload time down
//  Shot accuracy up (also reduces shot separation)
//  Number of shots up
//  Max life up
//  Movement speed up
//  Add a little helper dude
//  Change special (Different rarities. Level moves down one when you change)
//  Reduce special cooldown
//  Increase special level
//  Utility:
//   Display minimap
//   Show time until next enemy and enemy type
//   Show progress through wave (remaining enemies)
//   One reshuffle each time you get an upgrade choice



// Implementation:
// All colliders are circular, makes for easy collision detection.
// All gameobjects inherit from CircleObj

// CircleObj ->
//              Player
//              Projectile (TODO) ->
//                             PlayerShoot
//              Enemy ->
//                       Zombie
//                       Runner
//                       Boss1 (TODO)
//                       BigBoi (TODO)
//                       ZombGunner (TODO)
//                       Parasite (TODO)
//                       Demon (TODO)

// Waves have a list of bursts

// A burst is, an enemy type, a count and a timer
// So we will represent a burst as a trp = std::tuple<int, int, float>
// And a wave as a list of bursts

// GameStatus checks in update whether the wave is over.
// If so, it begins the next wave



// Buttons::
//  In game buttons::
//    Game status stores a list of buttons
//    Checks each one (isPressed(input vector)) and does the thing if true
//    Draws each one relative to view
