#include "pch.h"
#include "InventoryState.h"
#include "Controller.h"
#include "Inventory.h"
#include "Util.h"
#include "LevelSelectState.h"
#include "Weapon.h"
#include "Special.h"
#include "GameState.h"
#include "SpecialController.h"
#include "SpecialUpgradeTreeState.h"

#include <iostream>

const float itemSpriteSizeMul = 0.8f;
InventoryState::InventoryState(sf::RenderWindow *window, bool gameInProgress_) : State(window)
{
	gameInProgress = gameInProgress_;

	hoverWindow = StatHoverWindow();

	for (int i = 0; i < 20; i++) {
		inv[i] = Button();
		inv[i].setTexture(&textures[T_BUTTON]);
		inv[i].setBackgroundColor(sf::Color(180, 180, 180));
		inv[i].setForegroundScale(itemSpriteSizeMul);
	}

	for (int i = 0; i < 5; i++) {
		equip[i] = Button();
		equip[i].setTexture(&textures[T_BUTTON]);
		equip[i].setBackgroundColor(sf::Color(180, 180, 180));
		equip[i].setForegroundScale(itemSpriteSizeMul);
	}

	special = Button();
	special.setTexture(&textures[T_BUTTON]);
	special.setBackgroundColor(sf::Color(150, 150, 150));
	special.setForegroundScale(itemSpriteSizeMul);

	sellButton = Button();
	sellButton.setTexture(&textures[T_BUTTON]);
	sellButton.setBackgroundColor(sf::Color(200, 100, 100));
	sellButton.setString("SELL");
	sellButton.setTextSize(70);

	confirmSellPanel.setTexture(&textures[T_BUTTON2]);
	confirmSellPanel.setFillColor(sf::Color(220, 220, 220));
	confirmSellPanel.setSize(sf::Vector2f(1400, 900));
	confirmSellPanel.setOrigin(confirmSellPanel.getSize()*0.5f);
	confirmSellPanel.setPosition(0, 0);

	confirmSellText.setPosition(0, -100);
	confirmSellText.setFont(g_candara);
	confirmSellText.setCharacterSize(80);
	confirmSellText.setFillColor(sf::Color::Black);

	sellYes.setString("Yes");
	sellYes.setSize(sf::Vector2f(250, 150));
	sellYes.setBackgroundColor(sf::Color(150, 150, 150));
	sellYes.setPosition(sf::Vector2f(200, 200));

	sellNo.setString("No");
	sellNo.setSize(sf::Vector2f(250, 150));
	sellNo.setBackgroundColor(sf::Color(150, 150, 150));
	sellNo.setPosition(sf::Vector2f(-200, 200));

	sellingIndex = -1;

	if (gameInProgress) {
		special.setBackgroundColor(sf::Color(50, 50, 50));
		special.setForegroundColor(sf::Color(150, 150, 150));
	}

	backButton.setString("Back");
	backButton.setSize(sf::Vector2f(200, 100));
	backButton.setBackgroundColor(sf::Color(150, 150, 150));

	coinsText.setFont(g_candara);
	coinsText.setCharacterSize(100);
	coinsText.setFillColor(sf::Color::Black);
	setCoinText();

	overallStatsTitle.setFont(g_candara);
	overallStatsTitle.setCharacterSize(80);
	overallStatsTitle.setFillColor(sf::Color::Black);
	overallStatsTitle.setString("Overall stats");

	overallStatsText.setFont(g_candara);
	overallStatsText.setCharacterSize(60);
	overallStatsText.setFillColor(sf::Color::Black);

	setOverallStatsText();

	recalc(&window->getView());
}

void InventoryState::setCoinText() {
	coinsText.setString(std::to_string(getCoins()));
	coinsText.setOrigin(coinsText.getLocalBounds().left + coinsText.getLocalBounds().width, 0);
}

// HP
// DEF
// ACC
// AGI
// INT

// DPS
void InventoryState::setOverallStatsText() {
	Stats overall = getOverallPlayerStats();

	std::string t = "HP: " + std::to_string(overall.getHPS()) + "\nDEF: " + std::to_string(overall.getDefS()) +
		"\nACC: " + std::to_string(overall.getAccS()) + "\nAGI: " + std::to_string(overall.getAgiS()) + 
		"\nINT: " + std::to_string(overall.getIntS());

	Weapon *weapon = inventory->getWeapon();

	// DPS = Damage dealt in one second = Num shots per second * bullet damage
	if (weapon != nullptr) {
		t += "\nDPS: " + util::floatToString(weapon->weaponStats.dmg * weapon->weaponStats.shotsPerSecond, 2);
	}
	else {
		t += "\nDPS: 0.00";
	}

	Special *special = getSpecial();
	if (special != nullptr) {
		t += "\nCooldown: " + util::floatToString(overall.getSpecialMultiplier() * special->stats.baseReloadTime, 2);
	}

	overallStatsText.setString(t);
}


InventoryState::~InventoryState()
{
}

void InventoryState::update() {
	State::update();

	const sf::View *v = &window->getView();

	//sf::Vector2i mousePos = getMousePos();
	//sf::Vector2f pos = (sf::Vector2f)mousePos - (sf::Vector2f)(window->getSize()) * 0.5f;

	sf::Vector2f pos = getMousePosWorld();

	hoverWindow.setPosition(pos);

	if (mouseClicked) {
		if (backButton.isClicked(pos)) {
			mouseClicked = false;
			if (gameInProgress) {
				((GameState*)g_savedState)->reloadInventory();
				loadSavedState();
			}
			else {
				sf::RenderWindow *w = window;
				deleteState();
				g_state = new LevelSelectState(w);
			}
			return;
		}

		else if (!gameInProgress && special.isClicked(pos)) {
			sf::RenderWindow *w = window;
			deleteState();
			g_state = new SpecialUpgradeTreeState(w);
			return;
		}
	}

	bool inventoryNeedsSaving = false;

	if (mouseClicked) {
		if (sellingIndex == -1) {
			for (int i = 0; i < 20; i++) {
				if (repr[i] != -1 && inv[i].isClicked(pos)) {
					dragging = true;
					dragInd = i;
					dragTexture = &textures[std::get<1>(itemTypes[inventory->getItems()[repr[i]].first])];
					dragBox.setTexture(dragTexture, true);
					setSellCost(inventory->getItems()[repr[i]].first);
				}
			}

			for (int i = 0; i < 5; i++) {
				if (itemIn[i] != -1 && equip[i].isClicked(pos)) {
					dragging = true;
					dragInd = -i - 1;
					dragTexture = &textures[std::get<1>(itemTypes[inventory->getItems()[itemIn[i]].first])];
					dragBox.setTexture(dragTexture, true);
					setSellCost(inventory->getItems()[itemIn[i]].first);
				}
			}

			setOverallStatsText();
			recalc(v);
		}
		else {
			if (sellYes.isClicked(pos)) {
				inventory->sellItem(sellingIndex);
				setCoinText();
				sellingIndex = -1;
			}
			if (sellNo.isClicked(pos)) {
				sellingIndex = -1;
			}
		}
	}

	if (dragging && mouseReleased) {
		bool w = false;
		for (int i = 0; i < 20; i++) {
			if (inv[i].isClicked(pos)) {
				if (dragInd < 0) {
					inventory->items[itemIn[-dragInd - 1]].second = false;

					if (repr[i] == -1) inventorySwap(itemIn[-dragInd-1], -1);

					// something is in this square
					// so we go to the end
					else inventorySwap(itemIn[-dragInd - 1], -1);
				}
				else {
					if (repr[i] == -1) inventorySwap(repr[dragInd], -1);
					else inventorySwap(repr[dragInd], repr[i]);
				}

				inventoryNeedsSaving = true;
				w = true;
				break;
			}
		}

		if (!w) {
			for (int i = 0; i < 5; i++) {
				if (equip[i].isClicked(pos)) {
					inventoryNeedsSaving = true;
					// We picked up an equip and dropped on another equip
					if (dragInd < 0) break;

					int itemSlotType = std::get<2>(itemTypes[inventory->getItems()[repr[dragInd]].first]);

					if (itemSlotType == i) {
						// Set dragInd to true
						// Set this one to false
						// Swap them

						inventory->items[repr[dragInd]].second = true;

						if (itemIn[i] != -1) {
							inventory->items[itemIn[i]].second = false;
							inventorySwap(repr[dragInd], itemIn[i]);
						}
					}
				}
			}

			if (sellButton.isClicked(pos)) {
				if (dragInd < 0)
					sellingIndex = itemIn[-dragInd - 1];
				else
					sellingIndex = repr[dragInd];

				item it = itemTypes[inventory->getItems()[sellingIndex].first];
				confirmSellText.setString("Sell " + std::get<0>(it) + " for " + std::to_string(std::get<5>(it)) + " gold?");
				const auto &r = confirmSellText.getLocalBounds();
				confirmSellText.setOrigin(r.left+r.width/2,r.top+r.height/2);
			}
		}

		dragging = false;
		dragInd = -1;

		if (inventoryNeedsSaving) inventory->saveInventory();

		setOverallStatsText();
		recalc(v);
	}

	hoverWindow.setVisible(false);
	if (!dragging && !mouseClicked) {
		for (int i = 0; i < 20; i++) {
			if (repr[i] != -1 && inv[i].isClicked(pos)) {
				ITEMS itemType = (ITEMS)inventory->getItems()[repr[i]].first;
				hoverWindow.loadItem(itemType, itemTypes[itemType]);
				hoverWindow.setVisible(true);
			}
		}

		for (int i = 0; i < 5; i++) {
			if (itemIn[i] != -1 && equip[i].isClicked(pos)) {
				ITEMS itemType = (ITEMS)inventory->getItems()[itemIn[i]].first;
				hoverWindow.loadItem(itemType, itemTypes[itemType]);
				hoverWindow.setVisible(true);
			}
		}

	}
}

void InventoryState::setSellCost(int itemIndex) {
	int cost = std::get<5>(itemTypes[itemIndex]);
	sellButton.setString("SELL: " + std::to_string(cost));
}

// a must be valid. b can be invalid
void InventoryState::inventorySwap(int a, int b) {
	if (a == b) return;

	// move a to the end
	if (b >= (int)inventory->items.size() || b == -1) {
		auto x = inventory->items[a];
		inventory->items.erase(inventory->items.begin() + a);
		inventory->items.push_back(x);
	}
	else {
		auto A = inventory->items[a],
			 B = inventory->items[b];
		inventory->items[a] = B;
		inventory->items[b] = A;
	}
}

void InventoryState::draw(const sf::View *v) {
	window->clear(sf::Color::White);
	resize(v);
	for (int i = 0; i < 5; i++) {
		equip[i].draw(window);
	}
	for (int i = 0; i < 20; i++) {
		inv[i].draw(window);
	}
	if (dragging) sellButton.draw(window);
	special.draw(window);

	window->draw(overallStatsTitle);
	window->draw(overallStatsText);

	window->draw(coinsText);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		dragBox.setPosition(getMousePosWorld());
	}
	if (dragging) window->draw(dragBox);

	backButton.draw(window);

	hoverWindow.draw(window);


	if (sellingIndex != -1) {
		window->draw(confirmSellPanel);
		sellYes.draw(window);
		sellNo.draw(window);
		window->draw(confirmSellText);
	}
}

const float a_border_y = 200, a_border_x = 20, a_space = 50;
const float b_border_y = 30, b_border_x = 30, b_space = 10;

// Todo: May have to use a multiplier to make sure height is always 500 regardless of device
void InventoryState::resize(const sf::View *v) {
	State::resize(v);
	recalc(v);
}

const float statsTextTitleGap = 35, statsTextLeftMargin = 30, statsTextTopMargin = 30;

void InventoryState::recalc(const sf::View *v){
	sf::Vector2f screenSize = v->getSize();
	sf::Vector2f topLeft = -0.5f * screenSize;

	coinsText.setPosition(sf::Vector2f(screenSize.x*0.5f, screenSize.y*-0.5f) + sf::Vector2f(-30, 10));

	overallStatsTitle.setPosition(topLeft + sf::Vector2f(statsTextLeftMargin, statsTextTopMargin));
	overallStatsText.setPosition(topLeft + sf::Vector2f(statsTextLeftMargin,
		overallStatsTitle.getLocalBounds().height + statsTextTitleGap + statsTextTopMargin));

	backButton.setPosition(-screenSize * 0.5f + sf::Vector2f(0, screenSize.y) + sf::Vector2f(200, -100));

	float w = screenSize.x, h = screenSize.y;

	float a = (h - 2 * a_space - 2 * a_border_y) / 3;

	float w_a = 3 * a + 2 * a_space + 2 * a_border_x;

	sf::Vector2f a_centre = topLeft + sf::Vector2f(w_a/2, h/2);
	sf::Vector2f a_up = sf::Vector2f(0, -a - a_space);
	sf::Vector2f a_right = sf::Vector2f(a + a_space, 0);

	// 0 = weapon, 1 = head, 2 = torso, 3 = misc, 4 = shoes
	equip[0].setPosition(a_centre - v->getCenter() + a_right);
	equip[0].setSize(sf::Vector2f(a, a));
	equip[1].setPosition(a_centre - v->getCenter() + a_up);
	equip[1].setSize(sf::Vector2f(a, a));
	equip[2].setPosition(a_centre - v->getCenter());
	equip[2].setSize(sf::Vector2f(a, a));
	equip[3].setPosition(a_centre - v->getCenter() - a_right);
	equip[3].setSize(sf::Vector2f(a, a));
	equip[4].setPosition(a_centre - v->getCenter() - a_up);
	equip[4].setSize(sf::Vector2f(a, a));
	
	special.setPosition(a_centre - v->getCenter() - a_up - a_right);
	special.setSize(sf::Vector2f(a, a));

	sellButton.setPosition(a_centre - v->getCenter() - a_up + a_right);
	sellButton.setSize(sf::Vector2f(a, a));

	float w_b = w - w_a;

	float b = (w_b - 4 * b_space - 2 * b_border_x) / 5;

	dragBox.setSize(sf::Vector2f(itemSpriteSizeMul*b, itemSpriteSizeMul*b));
	dragBox.setOrigin(itemSpriteSizeMul * b / 2, itemSpriteSizeMul * b / 2);

	float by = (h - 4 * b - 3 * b_space) / 2;
	if (by < b_border_y) {
		b = (h - 3 * b_space - 2 * b_border_y) / 4;
	}

	float b_x = (w_b - 5 * b - 4 * b_space) / 2,
		b_y = (h - 4 * b - 3 * b_space) / 2;

	// We just need the position for the one in the top left.
	
	sf::Vector2f TL = topLeft + sf::Vector2f(w_a, 0) + sf::Vector2f(b_x + b / 2, b_y + b / 2);
	sf::Vector2f b_right = sf::Vector2f(b + b_space, 0);
	sf::Vector2f b_down = sf::Vector2f(0, b + b_space);

	// itemIn[i] = the index in the inventory of the item equipped in slot i
	for (int i = 0; i < 5; i++) itemIn[i] = -1;

	int ind = 0;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 5; x++) {
			sf::Vector2f pos = TL + b_right * (float)x + b_down * (float)y;
			inv[x + 5 * y].setPosition(pos);
			inv[x + 5 * y].setSize(sf::Vector2f(b, b));

			// Increase ind to the next not equipped thing
			while (ind < (int)inventory->getItems().size() && inventory->getItems()[ind].second) {
				auto p = inventory->getItems()[ind]; // (item type, true)
				int equipIndex = std::get<2>(itemTypes[p.first]);
				if (equipIndex != -1) itemIn[equipIndex] = ind;
				ind++;
			}

			if (ind < (int)inventory->getItems().size()) {
				auto itemInd = inventory->getItems()[ind];
				item item_ = itemTypes[itemInd.first];

				if (dragging && x+5*y == dragInd)
					inv[x + 5 * y].removeForeground();
				else
					inv[x + 5 * y].setForeground(&textures[std::get<1>(item_)]);

				repr[x + 5 * y] = ind;
			}
			else {
				inv[x + 5 * y].removeForeground();
				repr[x + 5 * y] = -1;
			}
			ind++;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (itemIn[i] == -1 || (dragging && -dragInd - 1 == i)) {
//			equip[i].removeForeground();
			equip[i].setForeground(&textures[icons[i]]);
		}
		else {
			int itemTypeIndex = inventory->getItems()[itemIn[i]].first;
			equip[i].setForeground(&textures[std::get<1>(itemTypes[itemTypeIndex])]);
		}
	}

	special.setForeground(&textures[std::get<3>(getSpecialType())]);
}

sf::Vector2f InventoryState::whereToCenter() {
	return sf::Vector2f(0, 0);
}

