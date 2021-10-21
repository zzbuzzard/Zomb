#pragma once
#include <SFML/Graphics.hpp>

// Has a size
// Needs a position input when its drawn to a window

class Button
{
public:
	// Always centered in middle. Disp is the offset from the screen center.
	Button();
	Button(sf::Vector2f size, sf::Vector2f offset, sf::Texture *texture = nullptr);
	~Button();
	
	void draw(sf::RenderWindow *window) const;
	void setVisible(bool v) { visible = v; }
	bool isClicked(sf::Vector2f pos) const;

	void setString(const std::string &st);
	void setTextSize(float size);
	void setTextColor(sf::Color col);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos_);
	void setTexture(sf::Texture *texture);
	void setBackgroundColor(sf::Color col);
	void setForegroundColor(sf::Color col);
	void setForeground(sf::Texture *fg);
	void setForegroundScale(float mul);

	void removeForeground() { usesFg = false; }

	const sf::Vector2f &getPosition() const { return pos; }
	const sf::Vector2f &getSize() const { return buttonBox.getSize(); }
private:
public:
private:
	bool visible = true;
	sf::Vector2f pos, size;
	sf::RectangleShape buttonBox;
	sf::Text text;

	float fgScale = 1;
	bool usesFg = false;
	sf::RectangleShape foreground;
};

