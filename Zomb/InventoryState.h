#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "StatHoverWindow.h"

#include "Media.h"

class Button;

class InventoryState : public State
{
public:
	InventoryState(sf::RenderWindow *window, bool gameInProgress_);
	~InventoryState();

	void update();
	void draw(const sf::View *v);
	sf::Vector2f whereToCenter();

	void resize(const sf::View *v);
private:
	void recalc(const sf::View *v);
	void inventorySwap(int a, int b);
	void setOverallStatsText();
	void setCoinText();
	void setSellCost(int itemIndex);
public:
private:
	bool gameInProgress;

	StatHoverWindow hoverWindow;

	Button backButton;

	Button special, sellButton;
	Button equip[5];
	int itemIn[5];

	TEXTURE icons[5] = { T_ICON_WEAPON, T_ICON_HEAD, T_ICON_TORSO, T_ICON_MISC, T_ICON_FEET };

	Button inv[20];
	int repr[20]; // button at x, y represents item in inventory with index repr[x+5y]

	sf::RectangleShape dragBox;

	bool dragging = false;
	sf::Texture *dragTexture;
	int dragInd = -1;

	sf::Text overallStatsTitle, overallStatsText;
	sf::Text coinsText;

	sf::RectangleShape confirmSellPanel;
	sf::Text confirmSellText;
	Button sellYes, sellNo;
	int sellingIndex = -1;
};

// A fuck tonne of buttons. How is this going to work??

// 20 Inventory spaces, 5 x 4
// And then 5 equipment slots on the left.

// Inventory is centered in the middle right


// Okay, we have 3 boxes on the left, then a gap the size of a box

 
// When we click down, 
// If we are hovering over a RIGHT box:
//   Set 
//       dragRight = true
//       dragInd = BOX ind that we grabbed
//       dragTexture = texture of that ind

// In drawing, if index is dragInd then no foreground

// If we release, and we are touching nothing, drag = false, ind = -1
// If we release, and we are touching a right button
//   Swap them in inventory and noDrag()
// If we release, and we are touching a button
//   Check the button's index against our type's index
//   If false, noDrag()
//   If true, swap our things, set them to false and us to true.
//   Update repr[]


