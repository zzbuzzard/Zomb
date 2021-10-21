#include "pch.h"
#include "SpecialUpgradeTreeState.h"
#include "Media.h"
#include "Levels.h"
#include "Controller.h"
#include "InventoryState.h"
#include "Util.h"
#include "Special.h"

// Button clicked
// setWindow(SPECIAL)
//  window contains a purchase button, if the SPECIAL is not purchased
//  which 

// Button clicked :
// setWindow(SPECIAL)

// window :
//  Panel, takes up a fixed space at the bottom of the screen
//  ROUNDED image, set to the image of the special
//  Button below the image. 
//    If not unlockable, greyed out purchase (or button invisible)
//    If unlockable, yellow purchase button     -> purchaseSpecial()
//    If unlocked, 
//       If equipped, green 'equipped' button
//       If not equipped, yellow equip button   -> equipSpecial()

const float nodeSpacing = 450;
const float nodeSize = 400;
const float nodeYSpacing = 500;

sf::Color bg = sf::Color::White;

SpecialUpgradeTreeState::SpecialUpgradeTreeState(sf::RenderWindow *window) : State(window), specialWindow()
{
	backButton.setSize(sf::Vector2f(200, 100));
	backButton.setString("Back");
	backButton.setBackgroundColor(sf::Color(150, 150, 150));

	screenCenter = sf::Vector2f(0, 200);

	for (int i = 0; i < NUM_SPECIALS; i++) {
		specialButtons[i] = Button();
		specialButtons[i].setSize(sf::Vector2f(nodeSize, nodeSize));
		specialButtons[i].setTexture(&textures[T_BUTTON]); specialButtons[i].setBackgroundColor(sf::Color(150, 150, 150));
		specialButtons[i].setForeground(&textures[std::get<3>(specialTypes[i])]);
		specialButtons[i].setForegroundScale(0.8f);
		children[i] = std::vector<int>();
	}

	setChildren();
	specialXOffsets[0] = 0;
	totWidth = createTree(0);
	makeJoins(0, 0, 0);

	coinsText.setFont(g_candara);
	coinsText.setCharacterSize(100);
	coinsText.setFillColor(sf::Color::Black);
	setCoinText();
}

void SpecialUpgradeTreeState::setCoinText() {
	coinsText.setString(std::to_string(getCoins()));
	coinsText.setOrigin(coinsText.getLocalBounds().left + coinsText.getLocalBounds().width, 0);
}

SpecialUpgradeTreeState::~SpecialUpgradeTreeState()
{
}

void SpecialUpgradeTreeState::setChildren() {
	for (int i = 0; i < NUM_SPECIALS; i++) {
		const auto &vec = std::get<2>(specialTypes[i]);
		if (vec.size() > 0) {
			int parent = vec[0];
			children[parent].push_back(i);
		}
	}
}

float SpecialUpgradeTreeState::createTree(int node) {
	float t = 0;
	std::vector<float> ts; ts.reserve(children[node].size());
	for (int child : children[node]) {
		float x = createTree(child);
		ts.push_back(x);
		t += x;
	}
	if (children[node].size() > 0)
		t += (children[node].size() - 1) * nodeSpacing;

	float left = -t / 2;
	for (int i = 0; i < children[node].size(); i++) {
		int n = children[node][i];

		specialXOffsets[n] = left + ts[i] / 2;
		left += ts[i] + nodeSpacing;
	}

	return t;
}

void SpecialUpgradeTreeState::drawFrom(int i, float xpos, float ypos) {
	specialButtons[i].setPosition(sf::Vector2f(xpos, ypos));
	sf::Color col = getTint((SPECIAL)i);
	specialButtons[i].setBackgroundColor(util::colorLerp(col, sf::Color::White, 0.5f));
	specialButtons[i].setForegroundColor(util::colorLerp(col, sf::Color::White, 0.8f));
	specialButtons[i].draw(window);

	for (int child : children[i]) {
		drawFrom(child, xpos + specialXOffsets[child], ypos + nodeYSpacing);
	}
}

void SpecialUpgradeTreeState::makeJoins(int i, float xpos, float ypos) {
	totHeight = std::max(ypos, totHeight);
	if (specialEquipped((SPECIAL)i)) screenCenter = sf::Vector2f(xpos, ypos);

	sf::Vector2f myPos = sf::Vector2f(xpos, ypos);
	for (int child : children[i]) {
		sf::Vector2f theirPos = sf::Vector2f(xpos+ specialXOffsets[child], ypos+nodeYSpacing);
		createJoint(myPos, theirPos);
		makeJoins(child, xpos + specialXOffsets[child], ypos + nodeYSpacing);
	}
}

const float lineThickness = 10;
// TODO: Creates lines between a and b, moving only down or along
// a is always above b, meaning b.y > a.y
void SpecialUpgradeTreeState::createJoint(sf::Vector2f A, sf::Vector2f B) {
	float d = (B.y - A.y) / 2;

	sf::RectangleShape a = sf::RectangleShape(sf::Vector2f(lineThickness, d));
	a.setOrigin(lineThickness / 2, 0);
	sf::RectangleShape c = sf::RectangleShape(sf::Vector2f(lineThickness, d));
	c.setOrigin(lineThickness / 2, d);

	a.setPosition(A); c.setPosition(B);

	sf::RectangleShape b = sf::RectangleShape(sf::Vector2f(abs(A.x - B.x) + lineThickness, lineThickness));
	b.setOrigin(b.getSize()*0.5f);
	b.setPosition((A + B) * 0.5f);

	a.setFillColor(sf::Color::Black);
	b.setFillColor(sf::Color::Black);
	c.setFillColor(sf::Color::Black);

	rectangleLines.push_back(a);
	rectangleLines.push_back(b);
	rectangleLines.push_back(c);
}

void SpecialUpgradeTreeState::update() {
	State::update();
	
	setCoinText();

	if (mouseClicked) {
		bool buttonClicked = false;
		openClick = false;

		sf::Vector2f pos = getMousePosWorld();

		for (int i = 0; i < NUM_SPECIALS; i++) {
			if (specialButtons[i].isClicked(pos)) {
				specialWindow.setSpecialWindow((SPECIAL)i);
				openClick = true;
				break;
			}
		}

		if (specialWindow.handleClick(pos)) buttonClicked = true;

		if (!(specialWindow.visible && specialWindow.contains(pos))) {
			if (backButton.isClicked(pos)) {
				sf::RenderWindow *w = window;
				deleteState();
				g_state = new InventoryState(w, false);
				return;
			}
		}

		if (!buttonClicked) {
			isDragging = true;
			dragStartPosition = (sf::Vector2f)getMousePos();
			dragStartWorld = screenCenter;
		}
	}

	// Very elaborate conditions for whether we clicked or dragged
	if (mouseReleased && !openClick && mouseHoldDuration < 0.2f && util::dist(dragStartWorld, screenCenter) < 10 &&
		!specialWindow.contains(getMousePosWorld())) {
		specialWindow.visible = false;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) isDragging = false;

	if (isDragging) {
		sf::Vector2f cpos = (sf::Vector2f)getMousePos();
		sf::Vector2f disp = cpos - dragStartPosition;
		screenCenter = dragStartWorld - disp * window->getView().getSize().x / (float)window->getSize().x;
		snapCenter();
	}
}

void SpecialUpgradeTreeState::snapCenter() {
	// totWidth is total width and its centered, so we can go to right and left
	float xBorder = totWidth * 0.5f * 1.2f;

	float minY = -400;
	float maxY = totHeight + 400;

	if (screenCenter.x > xBorder) {
		if (isDragging)
			dragStartWorld.x += xBorder - screenCenter.x;
		screenCenter.x = xBorder;
	}
	if (screenCenter.x < -xBorder) {
		if (isDragging)
			dragStartWorld.x += -xBorder - screenCenter.x;
		screenCenter.x = -xBorder;
	}

	if (screenCenter.y > maxY) {
		if (isDragging)
			dragStartWorld.y += maxY - screenCenter.y;
		screenCenter.y = maxY;
	}
	if (screenCenter.y < minY) {
		if (isDragging)
			dragStartWorld.y += minY - screenCenter.y;
		screenCenter.y = minY;
	}
}

void SpecialUpgradeTreeState::draw(const sf::View *v) {
	window->clear(bg);
	for (const auto &r : rectangleLines) {
		window->draw(r);
	}
	drawFrom(0, 0, 0);

	sf::Vector2f btmLeft = v->getCenter() +
		sf::Vector2f(-v->getSize().x / 2, v->getSize().y / 2);
	backButton.setPosition(btmLeft + sf::Vector2f(200, -100));
	backButton.draw(window);
	
	specialWindow.update(v);
	specialWindow.draw(window);

	sf::Vector2f screenSize = v->getSize();
	coinsText.setPosition(v->getCenter() + sf::Vector2f(screenSize.x*0.5f, screenSize.y*-0.5f) + sf::Vector2f(-30, 10));
	window->draw(coinsText);
}

sf::Vector2f SpecialUpgradeTreeState::whereToCenter() {
	return screenCenter;
}

void SpecialUpgradeTreeState::resize(const sf::View *v) {

}

#include <iostream>

const float panelSizeX = 2200, panelSizeY = 600, buttonY = 80, buttonB = 15,
imageB = 40, textXBorder = 40, imageSize = panelSizeY - imageB - buttonY - buttonB*2,
textYBorder = 30, titleDescGap = 30, textGapY = 50, textSpacingY = 70;

SpecialUpgradeTreeState::Window::Window() {
	panel.setFillColor(sf::Color(150, 150, 150));
	panel.setSize(sf::Vector2f(panelSizeX, panelSizeY));
	panel.setOrigin(sf::Vector2f(panel.getSize().x/2, panel.getSize().y));

	image.setSize(sf::Vector2f(imageSize, imageSize));
	image.setOrigin(0, 0);

	button.setBackgroundColor(sf::Color::Yellow);
	button.setSize(sf::Vector2f(imageSize, buttonY));

	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(100);
	title.setFont(g_candara);

	desc.setFillColor(sf::Color::Black);
	desc.setCharacterSize(60);
	desc.setFont(g_candara);
}

void SpecialUpgradeTreeState::Window::draw(sf::RenderWindow *window) {
	if (visible) {
		window->draw(panel);
		window->draw(image);
		window->draw(title);
		window->draw(desc);
		for (const auto &i : unlockText) window->draw(i);
		button.draw(window);
	}
}

#include <iostream>
void SpecialUpgradeTreeState::Window::update(const sf::View *v) {
	const auto &cent = v->getCenter();
	const auto &size = v->getSize();
	sf::Vector2f btmLeft(cent.x - size.x / 2, cent.y + size.y / 2);
	sf::Vector2f btmMiddle(cent.x, cent.y + size.y / 2);

	sf::Vector2f panelBtmLeft = sf::Vector2f(btmMiddle.x - panelSizeX / 2, btmMiddle.y);
	sf::Vector2f panelTopLeft = sf::Vector2f(btmMiddle.x - panelSizeX / 2, btmMiddle.y - panelSizeY);

	panel.setPosition(btmMiddle);

	image.setPosition(panelBtmLeft + sf::Vector2f(imageB, -(buttonY + 2*buttonB + imageSize)));

	button.setPosition(panelBtmLeft + sf::Vector2f(imageB + imageSize/2, -(buttonY/2 + buttonB)));

	title.setPosition(panelTopLeft + sf::Vector2f(imageB + imageSize + textXBorder, textYBorder));
	const auto &tS = title.getLocalBounds();
	desc.setPosition(title.getPosition() + sf::Vector2f(0, tS.height + titleDescGap));

	float unlockWidth = panelSizeX - imageSize - imageB - textXBorder - textXBorder;
	float x1 = title.getPosition().x, x2 = panelBtmLeft.x + panelSizeX - textXBorder;

	float x = (x1 + x2) / 2, y = btmLeft.y - textGapY;

	for (int i = unlockText.size() - 1; i >= 0; i--) {
		unlockText[i].setPosition(x, y);
		y -= textSpacingY;
	}
}

void addUnlockText(std::string string, bool goalAccomplished, std::vector<sf::Text> &vec) {
	sf::Text text = sf::Text(string, g_candara, 70);
	const auto &r = text.getLocalBounds();
	text.setOrigin(r.left + r.width / 2, r.top + r.height / 2);

	if (goalAccomplished)
		text.setFillColor(sf::Color::Green);
	else
		text.setFillColor(sf::Color::Red);

	vec.push_back(text);
}

// Unlockable : Yellow
// Equipped : Green
// Equippable : Blue
// Locked : Grey
sf::Color SpecialUpgradeTreeState::getTint(SPECIAL special) {
	if (specialUnlocked(special)) {
		if (specialEquipped(special))
			return sf::Color::Green;
		else
			return sf::Color::Blue;
	}
	if (isUnlockable(special)) return sf::Color::Yellow;
	return sf::Color(100, 100, 100);
}

void SpecialUpgradeTreeState::Window::setSpecialWindow(SPECIAL special_) {
	special = special_;

	float cooldown = getSpecialFrom(special)->stats.baseReloadTime;

	visible = true;
	image.setTexture(&textures[std::get<3>(specialTypes[special])], true);
	title.setString(std::get<0>(specialTypes[special]));
	desc.setString(std::get<1>(specialTypes[special]) + "\nBase cooldown: " + util::floatToString(cooldown, 1));

	unlockText.clear();

	const std::pair<LEVEL, int> &p = std::get<5>(specialTypes[special]);
	if (p.first != L_NONE) {
		std::string name = std::get<0>(levelTypes[p.first]);;
		addUnlockText("Beat wave " + std::to_string(p.second) + " on " + name,
			getMaxWave(p.first) >= p.second, unlockText);
	}

	const std::vector<SPECIAL> reqs = std::get<2>(specialTypes[special]);
	for (const SPECIAL &i : reqs) {
		std::string name = std::get<0>(specialTypes[i]);
		addUnlockText("Unlock " + name, specialUnlocked(i), unlockText);
	}

	if (isUnlockable(special) || (!specialUnlocked(special) && !isUnlockable(special))) {
		int cost = std::get<4>(specialTypes[special]);
		button.setString("Buy: " + std::to_string(cost));
	}

	if (specialUnlocked(special)) {
		if (specialEquipped(special)) {
			button.setString("Equipped");
		}
		else {
			button.setString("Equip");
		}
	}
	button.setBackgroundColor(getTint(special));
}

bool SpecialUpgradeTreeState::Window::handleClick(sf::Vector2f pos) {
	if (visible && button.isClicked(pos)) {

		if (isUnlockable(special)) {
			buySpecial(special);
			setSpecialWindow(special);
		}

		if (specialUnlocked(special)) {
			equipSpecial(special);
			setSpecialWindow(special);
		}

		return true;
	}
	return false;
}

bool SpecialUpgradeTreeState::Window::contains(sf::Vector2f pos) {
	return panel.getGlobalBounds().contains(pos);
}