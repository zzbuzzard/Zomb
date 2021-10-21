#pragma once
#include "State.h"
#include "SpecialController.h"
#include "Button.h"

class SpecialUpgradeTreeState : public State
{
public:
	SpecialUpgradeTreeState(sf::RenderWindow *window);
	~SpecialUpgradeTreeState();

	void update();
	void draw(const sf::View *v);
	sf::Vector2f whereToCenter();
	void resize(const sf::View *v);
private:
	static sf::Color getTint(SPECIAL special);
	void createJoint(sf::Vector2f a, sf::Vector2f b);

	void setChildren();
	float createTree(int i);
	void drawFrom(int i, float xpos, float ypos);
	void makeJoins(int i, float xpos, float ypos);
	void snapCenter();
	void setCoinText();

	class Window {
	public:
		Window();

		void update(const sf::View *v);
		void setSpecialWindow(SPECIAL special);

		bool handleClick(sf::Vector2f pos);
		bool contains(sf::Vector2f pos);
		void draw(sf::RenderWindow *window);
		bool visible = false;
	private:
		sf::RectangleShape panel, image;
		Button button;
		sf::Text title, desc;
		std::vector<sf::Text> unlockText;
		//sf::Vector2f pos;

		SPECIAL special;
	};
public:
private:
	Button backButton;

	bool openClick = false;
	bool isDragging = false;
	sf::Vector2f dragStartPosition;
	sf::Vector2f dragStartWorld;
	float dragSpd = 3.0f;

	sf::Vector2f screenCenter;

	float totWidth, totHeight;

	Button specialButtons[NUM_SPECIALS];
	float specialXOffsets[NUM_SPECIALS];
	std::vector<int> children[NUM_SPECIALS];

	std::vector<sf::RectangleShape> rectangleLines;

	Window specialWindow;

	sf::Text coinsText;
};

// SpecialUpgradeTreeState

// Each special needs a button. Make a button array of size NUM_SPECIALS.

// First, we go through all the specials and we construct the tree object

// Then we call f(root).

// f(n) : returns the WIDTH X of this subtree
//        we then set the RELATIVE position of all our children : They each get the space they need, and center them at 0


// Draw
//  1) Draw all lines
//  2) Recursive call, where x position is passed down. RecDraw(i) draws i then calls on children, with x offset.





