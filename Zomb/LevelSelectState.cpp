#include "pch.h"
#include "LevelSelectState.h"
#include "Button.h"
#include "Util.h"
#include "Controller.h"
#include "GameState.h"
#include "InventoryState.h"

#include <iostream>

int LevelSelectState::levelViewingIndex = 0;
bool LevelSelectState::levelViewingUnlocked = true;

// Text centered in middle of the screen
// When you hover near it, it changes colour and expands. You click, and it loads the game.
// There's a bottom and background graphic. When you click, the screen fades to black

// When you click left / right you go left / right
// A given screen, with index i, needs the following:
//   - Background texture. Should be really long.
//   - Foreground texture. Doesn't have to be that long.
//   - A name.

// When we press L / R, the screen fades to black then fades in with the new textures.

// The screen always has
//  1) Text centered in the middle.
//  2) Foreground texture at bottom of the screen. Width is the screen's length, and a little more. Height is aspect.
//  3) Background texture. Height is view_height. Width is aspect.

LevelSelectState::LevelSelectState(sf::RenderWindow *window) : State(window)
{
	centerText = sf::Text("", g_candara, 150);
	maxLevelText = sf::Text("", g_candara, 75);
	L1 = Button();  L1 .setSize(sf::Vector2f(300, 150)); L1 .setBackgroundColor(sf::Color(150, 150, 150));
	L11 = Button(); L11.setSize(sf::Vector2f(300, 150)); L11.setBackgroundColor(sf::Color(150, 150, 150));
	L21 = Button(); L21.setSize(sf::Vector2f(300, 150)); L21.setBackgroundColor(sf::Color(150, 150, 150));

	L1.setString("Level 1");
	L11.setString("Level 11");
	L21.setString("Level 21");

	L1.setPosition(sf::Vector2f(-460, 400));
	L11.setPosition(sf::Vector2f(0, 400));
	L21.setPosition(sf::Vector2f(460, 400));

	inventoryButton = Button();
	inventoryButton.setString("Inventory");
	inventoryButton.setSize(sf::Vector2f(300, 100));
	inventoryButton.setBackgroundColor(sf::Color(150, 150, 150));

	setTextures();
}

LevelSelectState::~LevelSelectState()
{
}

void disable(Button &b) {
	b.setBackgroundColor(sf::Color(80, 80, 80));
	b.setTextColor(sf::Color(40, 40, 40));
}

void turnOff(Button &b) {
	b.setBackgroundColor(sf::Color(150, 150, 150));
	b.setTextColor(sf::Color(0, 0, 0));
}

void turnOn(Button &b) {
	b.setBackgroundColor(sf::Color(220, 220, 30));
	b.setTextColor(sf::Color(0, 0, 0));
}


void LevelSelectState::setLButtons(LEVEL lev) {
	if (isUnlocked(lev)) {
		L1.setVisible(true);
		L11.setVisible(true);
		L21.setVisible(true);

		turnOff(L1);
		turnOff(L11);
		turnOff(L21);

		if (Lmode == 0) turnOn(L1);
		if (Lmode == 1) turnOn(L11);
		if (Lmode == 2) turnOn(L21);

		int wave = getMaxWave(lev);
		if (wave < 10) disable(L11);
		if (wave < 20) disable(L21);
	}
	else {
		L1.setVisible(false);
		L11.setVisible(false);
		L21.setVisible(false);
	}
}


void LevelSelectState::update() {
	State::update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (!leftDown) moveScreen(-1);
		leftDown = true;
	}
	else leftDown = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!rightDown) moveScreen(1);
		rightDown = true;
	}
	else rightDown = false;

}

void LevelSelectState::moveScreen(int n) {
	if (levelViewingIndex + n >= 0 && levelViewingIndex + n < NUM_LEVELS) {
		levelViewingIndex += n;
		setTextures();
	}
}

void LevelSelectState::resize(const sf::View *v) {
	State::resize(v);
	setTextures();
}

void LevelSelectState::draw(const sf::View *v) {
	window->clear(sf::Color::Black);
	sf::Vector2f mPos = getMousePosWorld();

	//setTextures();
	window->draw(background);
	window->draw(foreground);
	window->draw(centerText);

	if (levelViewingUnlocked)
		window->draw(maxLevelText);
	else {
		for (const auto &text : unlockTexts)
			window->draw(text);
	}

	inventoryButton.draw(window);

	L1.draw(window);
	L11.draw(window);
	L21.draw(window);

	if (mouseClicked && levelViewingUnlocked) {
		int w = getMaxWave(levelOrder[levelViewingIndex]);
		if (L1.isClicked(mPos)) Lmode = 0;
		if (L11.isClicked(mPos) && w >= 10) Lmode = 1;
		if (L21.isClicked(mPos) && w >= 20) Lmode = 2;
		setLButtons(levelOrder[levelViewingIndex]);
	}

	// Centered at 0, 0
	float hoverRadius = 1.2f * (float)util::mag(sf::Vector2f(centerText.getGlobalBounds().width / 2.0f,
		centerText.getGlobalBounds().height / 2.0f));

	if (mouseClicked && inventoryButton.isClicked(mPos)) {
		sf::RenderWindow *w = window;
		deleteState(); // ALL REFERENCES TO CLASS FIELDS ARE NOW UNDEFINED
		g_state = new InventoryState(w, false);
		return;
	}

	float mPosR = util::mag(mPos);

	if (mPosR <= hoverRadius && levelViewingUnlocked) {
		textFocus();
		if (mouseClicked) {
			// Make a new GameState
			currentLevel = levelOrder[levelViewingIndex];
			sf::RenderWindow *w = window;
			int startWave = Lmode * 10 + 1;

			deleteState(); // ALL REFERENCES TO CLASS FIELDS ARE NOW UNDEFINED

			g_state = new GameState(w, startWave);
			return;
		}
	}
	else textNoFocus();

	//if (mPos.x > -textBox.x && mPos.x < textBox.x &&
	//	mPos.y > -textBox.y && mPos.y < textBox.y) {
	//	textFocus();
	//}
	//else textNoFocus();
}

void LevelSelectState::textFocus() {
	centerText.setScale(1.1, 1.1);
	centerText.setOutlineColor(sf::Color::Yellow);
	centerText.setOutlineThickness(3.0f);

	maxLevelText.setScale(1.1, 1.1);
	maxLevelText.setOutlineColor(sf::Color::Yellow);
	maxLevelText.setOutlineThickness(3.0f);
}

void LevelSelectState::textNoFocus() {
	centerText.setScale(1, 1);
	centerText.setOutlineThickness(0.0f);

	maxLevelText.setScale(1, 1);
	maxLevelText.setOutlineThickness(0.0f);
}

sf::Vector2f LevelSelectState::whereToCenter() {
	return sf::Vector2f(0, 0);
}

const float unlockTextSpacing = 80;
void LevelSelectState::setTextures() {
	sf::Vector2f viewSize = window->getView().getSize();

	inventoryButton.setPosition(viewSize*0.5f + sf::Vector2f(-300, -100));
	
	const levelType &lev = levelTypes[levelOrder[levelViewingIndex]];
	centerText.setString(std::get<0>(lev));

	centerText.setOrigin(centerText.getLocalBounds().left + centerText.getLocalBounds().width * 0.5f,
		centerText.getLocalBounds().top + centerText.getLocalBounds().height * 0.5f);
	centerText.setPosition(0, 0);

	Lmode = 0;
	setLButtons(levelOrder[levelViewingIndex]);

	if (isUnlocked(levelOrder[levelViewingIndex])) {
		levelViewingUnlocked = true;
		maxLevelText.setString("Highest wave: " + std::to_string(getMaxWave(levelOrder[levelViewingIndex])));
		auto r = maxLevelText.getLocalBounds();
		maxLevelText.setOrigin(r.left + r.width / 2, r.top + r.height / 2);
		maxLevelText.setPosition(centerText.getPosition() + sf::Vector2f(0, centerText.getLocalBounds().height + 30));

	}
	else {
		levelViewingUnlocked = false;
		unlockTexts.clear();

		float x = centerText.getPosition().x,
			y = centerText.getPosition().y + centerText.getLocalBounds().height + 30;

		for (const std::pair<LEVEL, int> &p : std::get<4>(levelTypes[levelOrder[levelViewingIndex]])) {
			std::string name = std::get<0>(levelTypes[p.first]);
			sf::Text t = sf::Text("Beat wave " + std::to_string(p.second) + " on " + name, g_candara, 75);
			if (getMaxWave(p.first) >= p.second)
				t.setFillColor(sf::Color::Green);
			else
				t.setFillColor(sf::Color::Red);
			const auto &r = t.getLocalBounds();
			t.setOrigin(r.left + r.width / 2, r.top + r.height / 2);

			t.setPosition(x, y);
			unlockTexts.push_back(t);

			y += unlockTextSpacing;
		}
	}
	
	// Foreground width is screen length * 1.2
	// Height is aspect

	// Foreground is centered at bottom middle. Placed at bottom middle.
	
	// textureWidth -> viewSize.width * 1.2
	// X -> viewSize.width * 1.2 / textureWidth	
	sf::Vector2f fgTextureSize = (sf::Vector2f)(textures[std::get<2>(lev)].getSize());

	foreground.setTexture(&textures[std::get<2>(lev)], true);

	float mul = viewSize.x * 1.1f / fgTextureSize.x;
	foreground.setSize(mul * fgTextureSize);

	foreground.setOrigin(mul * fgTextureSize.x / 2, mul * fgTextureSize.y);
	foreground.setPosition(0, viewSize.y / 2);


	// Background
	sf::Vector2f bgTextureSize = (sf::Vector2f)(textures[std::get<1>(lev)].getSize());

	// textureHeight -> viewSize.height
	background.setTexture(&textures[std::get<1>(lev)], true);

	mul = viewSize.y / bgTextureSize.y;
	background.setSize(mul * bgTextureSize);
	background.setOrigin(mul * bgTextureSize * 0.5f);
	background.setPosition(0, 0);
}
