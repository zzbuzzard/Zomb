#pragma once
#include "CircleObj.h"
#include "Inventory.h"
#include <vector>
#include "Button.h"

class GameState;

class ItemCrate : public CircleObj
{
public:
	ItemCrate(sf::Vector2f pos, const std::vector<ITEMS> &containedItems);
	~ItemCrate();
	void update(GameState *state);
	bool isAlive(GameState *state) const;
	void draw(sf::RenderWindow *window) const;
	void collide(CircleObj *obj) {}
private:
	void updateUI();
	void drawUI(sf::RenderWindow *window) const;
	void addItemAt(int i);
public:
private:
	float crateTime;
	bool playerInRange;
	std::vector<ITEMS> crateItems;
	std::vector<Button> crateItemButtons;
	sf::RectangleShape panel;
	sf::Text lifeText;
};


// Crate
// Constructor: Take a list of item indices
// 1) Decide sprite based on item rarities
// 2) Create UI instances
// 3) In update, check if the player is within radius
//    If so, set display UI to true
// 4) In update, draw UI and check for clicks if its enabled.
//    If clicked, try adding to inventory, and destroy
