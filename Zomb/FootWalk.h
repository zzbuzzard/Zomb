#pragma once
#include <SFML/Graphics.hpp>
class FootWalk
{
public:
	FootWalk();
	~FootWalk();

	void setScale(float scale);
	void setPosition(sf::Vector2f pos);
	void setAngle(float ang);

	void update(float speed);
	void draw(sf::RenderWindow *window) const;
private:
	sf::Vector2f pos;
	float t = 0;
	float scale = 1;
	float ang;

	float gap = 10;
	float moveMag = 8;

	sf::RectangleShape L, R;
};

