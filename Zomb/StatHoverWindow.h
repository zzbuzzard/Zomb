#pragma once

#include <SFML/Graphics.hpp>
#include "Inventory.h"

class StatHoverWindow
{
public:
	StatHoverWindow();
	~StatHoverWindow();

	void setPosition(sf::Vector2f pos);
	void loadItem(ITEMS itemType, const item &item_);
	void setVisible(bool vis) { visible = vis; }

	void draw(sf::RenderWindow *window);
private:
	void setText(std::string string);
	void setTitle(std::string string);
	void setPanelSize();

public:

private:
	bool visible = true;
	sf::RectangleShape panel;
	sf::Text title, text;
};

// Appearance:
// Box
//  Title text
//  Stats text

// Needs a set position thing
// Needs a set item thing