#include "pch.h"
#include "StatHoverWindow.h"
#include "Media.h"
#include "Controller.h"
#include "Weapon.h"

#include <sstream>
#include <iomanip>

const float titleTextGap = 40.0f, leftMargin = 20.0f, rightMargin = 30.0f, topMargin = 15.0f, bottomMargin = 32.0f,
titleFontSize = 70, textFontSize = 55, minimumWidth = 400.0f;

StatHoverWindow::StatHoverWindow()
{
	title.setFont(g_candara);
	title.setCharacterSize(titleFontSize);
	title.setFillColor(sf::Color::Black);

	text.setFont(g_candara);
	text.setCharacterSize(textFontSize);
	text.setFillColor(sf::Color::Black);
	text.setLineSpacing(0.8f);

	panel.setFillColor(sf::Color(200, 200, 200));

	setTitle("Test");
	setText("DEX +5\nAGI +2\nSPD -5\nHP +50");
	setPanelSize();
}


StatHoverWindow::~StatHoverWindow()
{
}

void StatHoverWindow::setPosition(sf::Vector2f pos) {
	panel.setPosition(pos);
	title.setPosition(pos + sf::Vector2f(leftMargin, topMargin));
	text.setPosition(pos + sf::Vector2f(leftMargin, title.getGlobalBounds().height + titleTextGap + topMargin));
}

std::string signInt(int n) {
	return ((n > 0) ? "+" : "") + std::to_string(n);
}

void StatHoverWindow::loadItem(ITEMS itemType, const item &item_) {
	// TODO: Weapons have additional stats
	setTitle(std::get<0>(item_));

	Stats s = std::get<3>(item_);
	std::string statsText = std::get<6>(item_) + "\n";

	if (s.getHPS()  != 0) statsText += "HP "  + signInt(s.getHPS())  + "\n";
	if (s.getDefS() != 0) statsText += "DEF " + signInt(s.getDefS()) + "\n";
	if (s.getAgiS() != 0) statsText += "AGI " + signInt(s.getAgiS()) + "\n";
	if (s.getAccS() != 0) statsText += "ACC " + signInt(s.getAccS()) + "\n";
	if (s.getIntS() != 0) statsText += "INT " + signInt(s.getIntS()) + "\n";

	// Weapons have additional text
	if (std::get<2>(item_) == 0) {
		Weapon *weap = inventory->getWeaponFrom(itemType);

		float range = weap->weaponStats.lifetime * weap->weaponStats.spd;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(1);

		stream << "Shots per second: " << weap->weaponStats.shotsPerSecond << "\nBullet damage: " << weap->weaponStats.dmg << "\nRange: " << range * DISTANCE_MUL << "\n";
//		std::string s = stream.str();

		statsText += stream.str();
	}

	setText(statsText);
	setPanelSize();
}


void StatHoverWindow::setText(std::string string) {
	text.setString(string);
	//auto rect = text.getLocalBounds();
	//text.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

void StatHoverWindow::setTitle(std::string string) {
	title.setString(string);
	//auto rect = title.getLocalBounds();
	//title.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
}


void StatHoverWindow::setPanelSize() {
	auto r1 = title.getGlobalBounds(), r2 = text.getGlobalBounds();
	panel.setSize(sf::Vector2f(std::max(minimumWidth, leftMargin + rightMargin + std::max(r1.width, r2.width)),
		r1.height + r2.height + titleTextGap + topMargin + bottomMargin));
}

void StatHoverWindow::draw(sf::RenderWindow *window) {
	if (visible) {
		window->draw(panel);
		window->draw(title);
		window->draw(text);
	}
}
