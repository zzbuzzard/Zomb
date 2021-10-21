#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"

#include "Media.h"
#include "Button.h"

#include "Levels.h"


class LevelSelectState : public State
{
public:
	LevelSelectState(sf::RenderWindow *window);
	~LevelSelectState();

	void update();
	void draw(const sf::View *v);
	void resize(const sf::View *v);

	sf::Vector2f whereToCenter();

private:
	void setTextures();
	void textFocus();
	void textNoFocus();

	void setLButtons(LEVEL lev);

	void moveScreen(int n);
public:

private:
	sf::RectangleShape foreground, background;
	sf::Text centerText, maxLevelText;
	std::vector<sf::Text> unlockTexts;

	Button L1, L11, L21;
	int Lmode;

	bool leftDown = false;
	bool rightDown = false;

	//static LEVEL levelViewing;
	static int levelViewingIndex;
	static bool levelViewingUnlocked;

	//sf::Texture *bgs[2] = { &g_hillsBg, &g_caveBg };
	//sf::Texture *fgs[2] = { &g_hillsFg, &g_caveFg };
	//std::string names[2] = { "The hills", "The cave" };
	//int numLevels = 2;

	Button inventoryButton;
};

