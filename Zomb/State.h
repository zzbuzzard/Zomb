#pragma once
#include <SFML/Graphics.hpp>

extern float deltaTime, timeScale;
extern bool mouseClicked, mouseReleased, mouseDown;
extern float mouseHoldDuration;

class State
{
public:
	State(sf::RenderWindow *window);
	~State();

	virtual void update();
	virtual void draw(const sf::View *v) = 0;
	virtual sf::Vector2f whereToCenter() = 0;
	virtual void resize(const sf::View *v);

	sf::Vector2i getMousePos() const {
		return sf::Mouse::getPosition(*window);
	}
	sf::Vector2f getScreenCenter() const {
		return ((sf::Vector2f)window->getSize()) * 0.5f;
	}
	sf::Vector2f getMousePosWorld() const {
		const sf::View &v = window->getView();
		return v.getCenter() - v.getSize() / 2.0f + (sf::Vector2f)getMousePos() * (v.getSize().x / window->getSize().x);
	}

private:

public:

protected:
	sf::RenderWindow *window;
};

