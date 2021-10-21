#include "pch.h"
#include "GameState.h"
#include "Player.h"
#include "Controller.h"
#include "Inventory.h"

#include "IncludeEnemies.h"

#include "Media.h"

#include "LevelSelectState.h"
#include "InventoryState.h"

#include "SpecialController.h"

#include "Button.h"
#include "Util.h"

#include <set>
#include <list>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const extern float VIEW_HEIGHT = 1650.0f;

const std::vector<std::vector<wave> > wavesets = {
	// THE HILLS
	{
	{ burst(ZOMBIE, 10, 0.0f) },
	{ burst(ZOMBIE, 20, 1.0f), burst(RUNNER, 6, 0.0f) },
	{ burst(RUNNER, 20, 5.0f), burst(ZOMBIE, 40, 0.0f) },
	{ burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 1.0f), burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 1.0f),
	burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 1.0f), burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 1.0f),
	burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 1.0f), burst(RUNNER, 3, 1.0f), burst(ZOMBIE, 10, 4.0f)},
	{ burst(BIGBOI, 1, 3.0f), burst(RUNNER, 10, 0.1f), burst(BIGBOI, 2, 0.0f) },
	// 5

	{ burst(ZOMBIE, 35, 0.5f), burst(BIGBOI, 5, 5.0f), burst(ZOMBIE, 10, 5.0f), burst(BIGBOI, 2, 0.0f) },
	{ burst(RUNNER, 10, 2.0f), burst(RUNNER, 10, 2.0f), burst(RUNNER, 10, 2.0f), burst(RUNNER, 10, 2.0f), burst(RUNNER, 10, 2.0f),
	burst(RUNNER, 10, 2.0f) },
	{ burst(BIGBOI, 10, 5.0f), burst(RUNNER, 5, 3.0f), burst(RUNNER, 5, 3.0f), burst(RUNNER, 5, 3.0f), burst(RUNNER, 8, 3.0f) },
	{ burst(ZOMBIE, 30, 5.0f), burst(RUNNER, 25, 5.0f), burst(RUNNER, 10, 0.0f) },
	{ burst(ZOMBFARMER, 1, 0.0f) },
	// 10

	{ burst(REINFORCED_ZOMB, 20, 5.0f), burst(BIGBOI, 8, 0.0f) },
	{ burst(ZOMBIE, 60, 0.5f), burst(BIGBOI, 4, 5.0f), burst(ZOMBIE, 30, 10.0f), burst(RUNNER, 20, 0.5f), burst(BIGBOI, 3, 0.0f) },
	{ burst(REINFORCED_ZOMB, 10, 2.0f), burst(RUNNER, 15, 2.0f), burst(REINFORCED_ZOMB, 10, 2.0f), burst(RUNNER, 15, 2.0f),
	burst(REINFORCED_ZOMB, 20, 2.0f), burst(RUNNER, 30, 0.0f), },
	{ burst(BIGBOI, 5, 0.5f), burst(RUNNER, 20, 0.5f), burst(BIGBOI, 3, 0.5f), burst(RUNNER, 15, 1.0f), burst(BIGBOI, 1, 1.0f), burst(RUNNER, 5, 0.5f) },
	{ burst(ZOMBFARMER, 1, 3.0f), burst(ZOMBFARMER, 1, 0.0f), burst(REINFORCED_ZOMB, 30, 0.0f) },
	// 15

	{ burst(ZOMBIE, 20, 1.0f), burst(BIGBOI, 5, 1.0f), burst(RUNNER, 30, 1.0f), burst(BIGBOI, 3, 2.0f), burst(RUNNER, 20, 2.0f), burst(ZOMBIE, 30, 3.0f), burst(RUNNER, 30, 5.0f) },
	{ burst(BIGBOI, 5, 1.0f), burst(RUNNER, 15, 2.0f), burst(BIGBOI, 5, 1.0f), burst(RUNNER, 20, 2.0f), burst(BIGBOI, 5, 5.0f), burst(RUNNER, 30, 0.0f) },
	{ burst(REINFORCED_ZOMB, 30, 5.0f), burst(BIGBOI, 20, 5.0f), burst(REINFORCED_ZOMB, 40, 0.0f), burst(RUNNER, 40, 0.0f) },
	{ burst(RUNNER, 50, 2.0f), burst(RUNNER, 50, 2.0f), burst(RUNNER, 30, 2.0f) },
	{ burst(BOSS1, 1, 0.5f) },
	// 20
	},

	// THE CAVE
	{
	{ burst(ROCK_GOLEM, 1, 0.0f) },
	{ burst(CAVE_THING, 1, 2.0f), burst(BIGBOI, 5, 4.0f), burst(CAVE_THING, 2, 0.0f) },
	{ burst(ZOMBIE, 20, 3.0f), burst(ZOMBIE, 20, 2.0f), burst(ZOMBIE, 20, 1.5f), burst(ZOMBIE, 20, 0.0f), },
	{ burst(BIGBOI, 5, 1.0f), burst(BIGBOI, 4, 1.0f), burst(BIGBOI, 3, 1.0f), burst(BIGBOI, 2, 1.0f), burst(BIGBOI, 1, 3.0f),
	burst(CAVE_THING, 5, 0.0f) },
	{ burst(REINFORCED_ZOMB, 10, 5.0f), burst(REINFORCED_ZOMB, 15, 4.0f), burst(REINFORCED_ZOMB, 15, 3.0f),
	burst(CAVE_THING, 5, 2.0f), burst(BIGBOI, 5, 2.0f) },
	{ burst(CAVE_THING, 2, 2.0f), burst(CAVE_THING, 2, 2.0f), burst(ZOMBIE, 20, 0.0f), burst(CAVE_THING, 2, 2.0f), burst(CAVE_THING, 2, 2.0f),
	burst(CAVE_THING, 2, 2.0f), burst(ZOMBIE, 20, 0.0f), burst(CAVE_THING, 2, 2.0f) },
	// 5

	{ burst(RUNNER, 15, 0.5f), burst(CAVE_THING, 5, 2.0f), burst(RUNNER, 15, 2.0f), burst(RUNNER, 30, 2.0f), burst(BIGBOI, 15, 0.0f) },

	},

	// TEST
	{
	{ burst(ZOMBIE, 1, 0.5f) },
	{ burst(ZOMBFARMER, 1, 5.0f), burst(BOSS1, 1, 0.0f) },
	{ burst(ZOMBFARMER, 2, 0.0f) },
	{ burst(BOSS1, 2, 10.0f), burst(ZOMBFARMER, 2, 0.0f)},
	}
};

GameState::GameState(sf::RenderWindow *window, int startWave) : State(window) {
	timeScale = 1.0f;

	playerDead = false;

	currentWave = startWave - 1;
	currentBurst = 0;
	spawnCoolDown = 2;

	Stats playerStats = getOverallPlayerStats();

	Weapon *weapon = inventory->getWeapon();
	Special *special = getSpecial();
	Player *p = new Player(playerStats, weapon, special);

	inventory->applyStatusEffects(p);
	addObject(p);

	const LevelAppearance &appearance = std::get<3>(levelTypes[currentLevel]);

	background = sf::CircleShape(appearance.mapSize, 200);
	background.setFillColor(sf::Color::White);

	background.setTexture(&textures[appearance.background]);
	background.setTextureRect(sf::IntRect(0, 0,	
		textures[appearance.background].getSize().x * appearance.mapGgRepeats,
		textures[appearance.background].getSize().y * appearance.mapGgRepeats));

	background.setOrigin(getGameRadius(), getGameRadius());
	background.setPosition(0, 0);

	if (appearance.overlay != T_NONE) {
		hasOverlay = true;
		overlay = sf::RectangleShape(sf::Vector2f(getGameRadius()*2, getGameRadius()*2));
		overlay.setOrigin(overlay.getSize()*0.5f);

		overlay.setTexture(&textures[appearance.overlay]);
		overlay.setPosition(0, 0);
	}

	//initialiseWaves();
	//initialiseUpgradeP();

	//upgradeButton1 = Button(sf::Vector2f(400, 400), sf::Vector2f(-500, 0) + whereToCenter());
	//upgradeButton1.setString("A");
	//upgradeButton1.setVisible(false);

	//upgradeButton2 = Button(sf::Vector2f(400, 400), sf::Vector2f(0, 0) + whereToCenter());
	//upgradeButton2.setString("B");
	//upgradeButton2.setVisible(false);

	//upgradeButton3 = Button(sf::Vector2f(400, 400), sf::Vector2f(500, 0) + whereToCenter());
	//upgradeButton3.setString("C");
	//upgradeButton3.setVisible(false);

	displayText = sf::Text("", g_candara, 60);
	displayText.setFillColor(sf::Color::Black);
	displayText.setOrigin(-15, -15);

	deathText.setFont(g_candara);
	deathText.setCharacterSize(200);
	deathText.setString("You died");
	auto g = deathText.getGlobalBounds();
	deathText.setOrigin(g.left + g.width / 2, g.top + g.height / 2);

	inventoryButton.setString("Inventory");
	inventoryButton.setSize(sf::Vector2f(300, 100));
	inventoryButton.setVisible(true);
	inventoryButton.setBackgroundColor(sf::Color(150, 150, 150));

	quitButton.setString("Quit");
	quitButton.setSize(sf::Vector2f(300, 100));
	quitButton.setVisible(true);
	quitButton.setBackgroundColor(sf::Color(150, 150, 150));

	resize(&window->getView());
}

void GameState::reloadInventory() {
	Stats playerStats = getOverallPlayerStats();
	Weapon *weapon = inventory->getWeapon();
	Special *special = getSpecial();
	Player *p2 = new Player(playerStats, weapon, special);
	p2->copyFrom(getPlayer());
	inventory->applyStatusEffects(p2);

	// Make a brand new player, with the same lifeOn
	// And the same status effects UNLESS they permanent
	delete getPlayer();
	objects.erase(objects.begin());
	objects.push_front(p2);
}

void GameState::resize(const sf::View *v) {
	State::resize(v);
	deathPanel.setSize(v->getSize());
	deathPanel.setOrigin(v->getSize()*0.5f);
}

Player *GameState::getPlayer() {
	return (Player*)(*objects.begin());
}

sf::Vector2f GameState::whereToCenter() {
	return getPlayer()->getPosition();
}

void GameState::addObject(CircleObj *obj) {
	objects.push_back(obj);
}

bool hasCollided(CircleObj *a, CircleObj *b) {
	return util::dist(a->getPosition(), b->getPosition()) <= a->getRadius() + b->getRadius();
}

void GameState::playerDeath() {
	if (!playerDead) {
		playerDead = true;
		deathScreenWait = 1.0f;
		deathTextAlpha = 0.0f;
		deathPanelAlpha = 0.0f;
	}
}

void GameState::update() {
	State::update();

	spawnEnemies();
	updateAll();
	collide();
	removeDead();
}

void GameState::draw(const sf::View *view) {
	window->clear(std::get<3>(levelTypes[currentLevel]).outside);
	drawAll();
	drawUI(view);
}

//  0) Add all objects to a vector, which already exists
//  
//  1) Sort by left_start left to right
//     And priority queue of right_end
//
//  2) Loop through and add to set, which sorts em by top_start, and to pq, which sorts em by right_end
//
//  3) When we reach a new boi, left_start = x
//     For everyone in PQ with end < left_start, pop em(and remove from set)
//
//  4) Loop through the set and check for collisions until top_start becomes greater than my bottom_end

struct LeftStartComp {
	bool operator()(const CircleObj *a, const CircleObj *b) {
		return a->getPosition().x - a->getRadius() < b->getPosition().x - b->getRadius();
	}
};

typedef std::pair<float, int> pf;
void GameState::collide() {
	float maxRadius = 0;

	int ind = 0;
	for (auto i : objects) {
		if (i->type == ObjectType::NOCOLLISION) continue;
		if (ind == objectVector.size()) objectVector.push_back(i);
		else objectVector[ind] = i;
		ind++;
		maxRadius = std::max(maxRadius, i->getRadius());
	}

	sort(objectVector.begin(), objectVector.begin() + ind, LeftStartComp());

	int cind = 0;
	// collisionVector

	// Set which sorts by top_start : float, int
	// PQ which sorts by right_end : float, int
	std::set<pf> top_starts;
	std::priority_queue<pf> right_ends;

	for (int i = 0; i < ind; i++) {
		float myTopStart = objectVector[i]->getPosition().y - objectVector[i]->getRadius();
		float myLeftStart = objectVector[i]->getPosition().x - objectVector[i]->getRadius();

		// Pop everyone who ends before I start, on the x axis
		while (right_ends.size() && right_ends.top().first < myLeftStart) {
			int index = right_ends.top().second;
			float theirTopStart = objectVector[index]->getPosition().y - objectVector[index]->getRadius();
			right_ends.pop();
			auto iter = top_starts.find(pf(theirTopStart, index));

			// On the off chance that there's a floating point issue and we get different numbers, don't erase and it just becomes a minor inefficiency
			if (iter != top_starts.end())
				top_starts.erase(iter);
		}

		float myTopEnd = myTopStart + objectVector[i]->getRadius() * 2;

		// Their start must be before my end
		// Their start must be after my start - 2 * max radius
		auto startIt = top_starts.lower_bound(pf(myTopStart - maxRadius * 2, 0));

		for (; startIt != top_starts.end(); ++startIt) {
			const pf &p = *startIt;
			if (p.first > myTopEnd) break;
			if (hasCollided(objectVector[p.second], objectVector[i])) {
				if (cind == collisionVector.size()) collisionVector.push_back(std::pair<int, int>(p.second, i));
				else collisionVector[cind] = std::pair<int, int>(p.second, i);
				cind++;
			}
		}

		top_starts.insert(pf(myTopStart, i));
		right_ends.push(pf(myLeftStart + objectVector[i]->getRadius() * 2, i));
	}

	for (int col = 0; col < cind; col++) {
		const auto &p = collisionVector[col];

		// objects may have moved apart in the duration of this loop
		if (hasCollided(objectVector[p.first], objectVector[p.second])) {
			objectVector[p.first]->collide(objectVector[p.second]);
			objectVector[p.second]->collide(objectVector[p.first]);
		}
	}
}

// TODO: Change to sweep algorithm, but first time this one
//void GameState::collide() {
//	for (auto it = objects.begin(); it != objects.end(); ++it) {
//		auto it2 = it; ++it2;
//		for (; it2 != objects.end(); ++it2) {
//			if (hasCollided(*it, *it2)) {
//				(*it)->collide(*it2);
//				(*it2)->collide(*it);
//			}
//		}
//	}
//}

bool spaceDown = false;

void GameState::togglePaused() {
	if (isPaused) {
		// resume
		timeScale = 1.0f;
	}
	else {
		// pause
		timeScale = 0.0f;
	}

	isPaused = !isPaused;
}

void GameState::updateAll() {
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	//	upgrade();
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		if (!spaceDown)
			togglePaused();
		spaceDown = true;
	}
	else spaceDown = false;

	enemiesExist = false;
	for (auto it : objects) {
		if (playerDead && (it->type == ObjectType::ENEMY || it->type == ObjectType::PLAYER)) continue;
		it->update(this);
		if (it->type == ObjectType::ENEMY)
			enemiesExist = true;
	}
}

void GameState::removeDead() {
	for (auto it = objects.begin(); it != objects.end(); ) {
		if (!(*it)->isAlive(this)) {
			// Enemies need to know when they die for crate spawning etc
			if ((*it)->type == ObjectType::ENEMY) {
				((Enemy*)(*it))->handleDeath(this);
			}

			auto previt = it;
			++it;
			delete (*previt);
			objects.erase(previt);
		}
		else ++it;
	}
}

void GameState::drawAll() {
	window->draw(background);
	for (const auto &it : objects) {
		if (it->type==ObjectType::PLAYER && playerDead) continue;
		it->draw(window);
	}
	if (hasOverlay) window->draw(overlay);
}

GameState::~GameState()
{
	for (auto i : objects) {
		delete i;
	}
}

void GameState::spawnEnemies() {
	if (playerDead) return;

	spawnCoolDown -= deltaTime;
	if (spawnCoolDown < 0) {
		if (currentWave < (int)wavesets[currentLevel].size()){
			if (currentBurst < (int)wavesets[currentLevel][currentWave].size()) {
				int c = std::get<1>(wavesets[currentLevel][currentWave][currentBurst]);
				for (int i=0; i<c; i++)
					spawn(std::get<0>(wavesets[currentLevel][currentWave][currentBurst]));
				spawnCoolDown = std::get<2>(wavesets[currentLevel][currentWave][currentBurst]);
				
				currentBurst++;
				if (currentBurst == wavesets[currentLevel][currentWave].size()) {
					spawnCoolDown = 0.0f;
				}
			}
			else {
				if (!enemiesExist) {
					spawnCoolDown = 5.0f;
					nextWave();
				}
			}
		}
	}
}

void GameState::nextWave() {
	saveMaxWave(currentLevel, currentWave + 1);

	currentBurst = 0;
	currentWave++;

	// After every 5th wave
	//if (currentWave % 1 == 0) {
	//	upgrade();
	//}
}

//void GameState::upgrade() {
//	return;
//	float tot = 0;
//	for (float t : upgradeProb) tot += t;
//
//	float r = util::rand(0, tot);
//	for (int i = 0; i < (int)upgradeProb.size(); i++) {
//		if (upgradeProb[i] >= r) {
//			a = i;
//			break;
//		}
//		r -= upgradeProb[i];
//	}
//
//	tot -= upgradeProb[a];
//	r = util::rand(0, tot);
//	for (int i = 0; i < (int)upgradeProb.size(); i++) {
//		if (i == a) continue;
//		if (upgradeProb[i] >= r) {
//			b = i;
//			break;
//		}
//		r -= upgradeProb[i];
//	}
//
//	tot -= upgradeProb[b];
//	r = util::rand(0, tot);
//	for (int i = 0; i < (int)upgradeProb.size(); i++) {
//		if (i == a || i == b) continue;
//		if (upgradeProb[i] >= r) {
//			c = i;
//			break;
//		}
//		r -= upgradeProb[i];
//	}
//
//	upgradeButton1.setString(upgradeDesc[a]); upgradeButton1.setVisible(true);
//	upgradeButton2.setString(upgradeDesc[b]); upgradeButton2.setVisible(true);
//	upgradeButton3.setString(upgradeDesc[c]); upgradeButton3.setVisible(true);
//}

void GameState::spawn(EnemyType type, bool loot) {
	float ang = (float)util::rand(0, 2 * util::PI);
	float X = cos(ang)*getGameRadius(),
		Y = sin(ang)*getGameRadius();

	sf::Vector2f pos(X, Y);
	spawnAt(type, sf::Vector2f(X, Y), loot);
}
void GameState::spawnAt(EnemyType type, sf::Vector2f pos, bool loot){
	switch (type) {
	case ZOMBIE:
		addObject(new Zomb1(pos, loot));
		break;
	case RUNNER:
		addObject(new Runner(pos, loot));
		break;
	case BIGBOI:
		addObject(new BigBoi(pos, loot));
		break;
	case BOSS1:
		addObject(new Boss1(pos, loot));
		break;
	case SCIENCEZOMB:
		addObject(new ScienceZomb(pos, loot));
		break;
	case ZOMBFARMER:
		addObject(new ZombieFarmer(pos, loot));
		break;
	case REINFORCED_ZOMB:
		addObject(new ReinforcedZomb(pos, loot));
		break;
	case CAVE_THING:
		addObject(new CaveThing(pos, loot));
		break;
	case ROCK_GOLEM:
		addObject(new RockGolem(pos, loot));
		break;
	}
}

void GameState::drawUI(const sf::View *v) {
	inventoryButton.setPosition(whereToCenter() + v->getSize()*0.5f + sf::Vector2f(-180, -80));
	quitButton.setPosition(whereToCenter() + v->getSize()*0.5f + sf::Vector2f(180 - v->getSize().x, -80));

	//upgradeButton1.setPosition(sf::Vector2f(-500, 0) + whereToCenter());
	//upgradeButton2.setPosition(sf::Vector2f(0, 0) + whereToCenter());
	//upgradeButton3.setPosition(sf::Vector2f(500, 0) + whereToCenter());

	//upgradeButton1.draw(window);
	//upgradeButton2.draw(window);
	//upgradeButton3.draw(window);

	inventoryButton.draw(window);

	displayText.setPosition(v->getCenter() - v->getSize() * 0.5f);
	displayText.setString("Wave: " + std::to_string(currentWave + 1));
	window->draw(displayText);

	if (mouseClicked && inventoryButton.isClicked(getMousePosWorld())) {
		moveStateToSave();
		sf::RenderWindow *w = window;
		g_state = new InventoryState(w, true);
		return;
	}

	if (isPaused) {
		quitButton.draw(window);
		if (mouseClicked && quitButton.isClicked(getMousePosWorld())) {
			sf::RenderWindow *w = window;
			deleteState();
			g_state = new LevelSelectState(w);
			return;
		}
	}

	//if (mouseClicked && a != -1) {
	//	// Position relative to window top left corner of the cursor
	//	// We want it relative to the centre though
	//	sf::Vector2i mousePos = getMousePos();
	//	sf::Vector2f pos = (sf::Vector2f)mousePos - (sf::Vector2f)(window->getSize()) * 0.5f;

	//	bool w = false;

	//	if (upgradeButton1.isClicked(pos) && !w) {
	//		upgradeProb[a] *= getPlayer()->upgrade(upgrades[a]);
	//		w = true;
	//	}
	//	if (upgradeButton2.isClicked(pos) && !w) {
	//		upgradeProb[b] *= getPlayer()->upgrade(upgrades[b]);
	//		w = true;
	//	}
	//	if (upgradeButton3.isClicked(pos) && !w) {
	//		upgradeProb[c] *= getPlayer()->upgrade(upgrades[c]);
	//		w = true;
	//	}

	//	if (w) {
	//		upgradeButton1.setVisible(false);
	//		upgradeButton2.setVisible(false);
	//		upgradeButton3.setVisible(false);
	//		a = -1; b = -1; c = -1;
	//	}
	//}

	if (playerDead) {
		deathPanel.setPosition(v->getCenter());
		deathText.setPosition(v->getCenter());

		deathPanelAlpha += deathPanelAlphaSpeed * deltaTime;
		deathPanelAlpha = std::min(deathPanelAlpha, 1.0f);
		deathTextAlpha += deathTextAlphaSpeed * deltaTime;
		deathTextAlpha = std::min(deathTextAlpha, 1.0f);

		deathPanel.setFillColor(sf::Color(155, 0, 0, (sf::Uint8)(255*deathPanelAlpha)));
		deathText.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(255 * deathPanelAlpha)));

		window->draw(deathPanel);
		window->draw(deathText);

		deathScreenWait -= deltaTime;
		if (deathScreenWait < 0 && mouseClicked) {
			sf::RenderWindow *w = window;
			deleteState();
			g_state = new LevelSelectState(w);
			return;
		}
	}
}

void GameState::coinsEarned(int coins) {
	addCoins(coins);
}
