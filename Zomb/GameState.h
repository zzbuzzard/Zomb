#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <tuple>
#include "Button.h"
#include "State.h"
#include "Media.h"
#include "Controller.h"
#include "LevelSelectState.h"

class Player;
class CircleObj;

//enum class Upgrade {
//	BULLET_DAMAGE,
//	RELOAD,
//	ACCURACY,
//	NUM_SHOTS,
//	LIFE,
//	SPEED
//};

// To add a new enemy
//   1) Add to enum (and to waves)
//   2) Add to switch statement
enum EnemyType {
	ZOMBIE,
	RUNNER,
	BIGBOI,
	BOSS1,
	SCIENCEZOMB,
	ZOMBFARMER,
	REINFORCED_ZOMB,
	CAVE_THING,
	ROCK_GOLEM,
};
typedef std::tuple<EnemyType, int, float> burst;
typedef std::vector<burst> wave;

const extern float VIEW_HEIGHT;

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, int startWave);
	~GameState();

	void update();
	void draw(const sf::View *v);

	void coinsEarned(int coins);

	sf::Vector2f getGameCenter() {
		return sf::Vector2f(0, 0);
	}

	void addObject(CircleObj *obj);

	Player *getPlayer();

	float getGameRadius() const {
		return std::get<3>(levelTypes[currentLevel]).mapSize;
	}
	int getWave() const {
		return currentWave;
	}
	sf::Vector2f whereToCenter();

	void spawn(EnemyType type, bool loot = true);
	void spawnAt(EnemyType type, sf::Vector2f pos, bool loot = true);

	void playerDeath();
	void resize(const sf::View *v);

	void reloadInventory();

	sf::RenderWindow* getWindow() { return window; }
private:
	void nextWave();
	//void upgrade();

	void drawUI(const sf::View *v);
	void drawAll();

	void spawnEnemies();
	void updateAll();
	void collide();
	void removeDead();

	void togglePaused();
public:
	bool isPaused = false;

private:
	bool playerDead = false;
	float deathScreenWait;
	float deathTextAlpha; float deathTextAlphaSpeed = 0.6f;
	float deathPanelAlpha; float deathPanelAlphaSpeed = 0.8f;
	sf::RectangleShape deathPanel;
	sf::Text deathText;

	std::list<CircleObj*> objects;
	std::vector<CircleObj*> objectVector;
	std::vector<std::pair<int, int> > collisionVector;
	bool enemiesExist;

	sf::Text displayText;
	Button inventoryButton;
	Button quitButton;

	sf::CircleShape background;
	sf::RectangleShape overlay;

	bool hasOverlay = false;

	int currentWave;
	int currentBurst;
	float spawnCoolDown;

	// Tileable background texture
	//sf::Texture* mapGgs[2] = { &g_hillsGg, &g_caveGg };
	//int mapGgRepeats[2] = { 15, 10 };

	//float mapSizes[2] = { 2000.0f, 1000.0f };
	//sf::Color mapBgs[2] = { sf::Color::Black, sf::Color::Black };
};

