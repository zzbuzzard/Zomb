#include "pch.h"
#include "State.h"

float deltaTime, mouseHoldDuration, timeScale;
bool mouseClicked, mouseReleased, mouseDown = false;

State::State(sf::RenderWindow *window)
{
	this->window = window;
}

State::~State()
{
}

void State::resize(const sf::View *v) {
}

void State::update() {
	// mousedown currently represents last frame
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDown) {
		mouseHoldDuration = 0;
		mouseClicked = true;
	}
	else
		mouseClicked = false;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseDown)
		mouseReleased = true;
	else
		mouseReleased = false;

	mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (mouseDown) mouseHoldDuration += deltaTime;
}

// mouse released: currently mouse down = false, previously mouse down = up