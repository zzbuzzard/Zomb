#include "pch.h"
#include "ItemCrate.h"
#include "Media.h"
#include "Util.h"
#include "GameState.h"
#include "Player.h"

#include <iostream>

const float gap_x = 20, border_y = 20;
const float button_size = 220;
const float fgMul = 0.8f;
const float hoverGap = 60.0f;

const float playerDisplayRange = 140;

TEXTURE crateTextures[4] = {T_CRATE1, T_CRATE2, T_CRATE3, T_CRATE4};
float crateLife[4] = { 30.0f, 45.0f, 60.0f, 90.0f };

TEXTURE getCrateTexture(const std::vector<ITEMS> &items) {
	int m = 0;
	for (const auto &i : items) {
		m = std::max(m, (int)std::get<4>(itemTypes[i]));
	}
	return crateTextures[m];
}

float getCrateLife(const std::vector<ITEMS> &items) {
	int m = 0;
	for (const auto &i : items) {
		m = std::max(m, (int)std::get<4>(itemTypes[i]));
	}
	return crateLife[m];
}

ItemCrate::ItemCrate(sf::Vector2f pos, const std::vector<ITEMS> &containedItems)
	: CircleObj(ObjectType::NOCOLLISION, pos, getCrateTexture(containedItems), 100.0f),
	crateItems(containedItems)
{
	crateTime = getCrateLife(containedItems);

	crateItemButtons = std::vector<Button>(crateItems.size());

	lifeText.setPosition(pos + sf::Vector2f(0, getRadius() + 30));
	lifeText.setFont(g_candara);
	lifeText.setCharacterSize(50);
	lifeText.setString(util::floatToString(crateTime));
	lifeText.setOutlineColor(sf::Color::Black); lifeText.setOutlineThickness(0.3f);
	lifeText.setFillColor(sf::Color::Black);
	auto g = lifeText.getLocalBounds();
	lifeText.setOrigin(g.left + g.width / 2, g.top + g.height / 2);

	for (Button &b : crateItemButtons) {
		b.setSize(sf::Vector2f(button_size, button_size));
		b.setVisible(true);
		b.setTexture(&textures[T_BUTTON]);
		b.setBackgroundColor(sf::Color(150, 150, 150));
		b.setForegroundScale(fgMul);
	}
	panel.setFillColor(sf::Color(200, 200, 200));
	playerInRange = false;
	updateUI();
}


ItemCrate::~ItemCrate()
{
}

void ItemCrate::update(GameState *state) {
	CircleObj::update(state);
	crateTime -= deltaTime;
	playerInRange = util::dist(state->getPlayer()->getPosition(), pos) < playerDisplayRange;

	auto g = lifeText.getLocalBounds();
	lifeText.setString(util::floatToString(crateTime, 1));
	lifeText.setOrigin(g.left + g.width / 2, lifeText.getOrigin().y);

	if (mouseClicked && playerInRange) {
		// Todo: Check for button clicks
		sf::Vector2f pos = state->getMousePosWorld();
		for (int i = 0; i < crateItemButtons.size(); i++) {
			if (crateItemButtons[i].isClicked(pos)) {
				addItemAt(i);
				updateUI();
				break;
			}
		}
	}
}

bool ItemCrate::isAlive(GameState *state) const {
	return crateTime > 0 && crateItems.size() > 0;
}

void ItemCrate::draw(sf::RenderWindow *window) const {
	CircleObj::draw(window);
	if (playerInRange) {
		drawUI(window);
	}
	window->draw(lifeText);
}

void ItemCrate::updateUI() {
	if (crateItems.size() == 0) return;

	float totWidth = crateItems.size() * button_size + (crateItems.size() - 1) * gap_x + 2 * gap_x;
	float totHeight = button_size + border_y * 2;

	// pos -> pos - totLength / 2 -> pos - totLength / 2 + gap_x + size/2

	float x = pos.x - totWidth / 2 + gap_x + button_size / 2;
	float y = pos.y - radius / 2 - hoverGap - border_y - button_size / 2;

	for (int i = 0; i < crateItemButtons.size(); i++) {
		ITEMS item_ = crateItems[i];

		crateItemButtons[i].setPosition(sf::Vector2f(x, y));
		crateItemButtons[i].setForeground(&textures[std::get<1>(itemTypes[item_])]);

		x += gap_x + button_size;
	}

	panel.setSize(sf::Vector2f(totWidth, totHeight));
	panel.setOrigin(totWidth / 2, totHeight / 2);
	panel.setPosition(pos.x, y);
}

void ItemCrate::addItemAt(int i) {
	if (!inventory->inventoryFull()) {
		inventory->addToInventory(crateItems[i]);

		crateItems.erase(crateItems.begin() + i);
		crateItemButtons.erase(crateItemButtons.begin() + i);
	}
}

void ItemCrate::drawUI(sf::RenderWindow *window) const {
	window->draw(panel);
	for (const Button &b : crateItemButtons) {
		b.draw(window);
	}
}