#pragma once
#include <SFML/Graphics.hpp>


class Anim
{
public:
	Anim(sf::Texture &texture, sf::Vector2i imageCount, float switchTime);
	~Anim();
	void Update(float deltaTime);
	void SetRow(int y);
private:
	void SetRect();
public:
	sf::IntRect textureRect;
private:
	// y is fixed
	// x changes
	sf::Vector2i pos;
	sf::Vector2i imageCount;

	float elapsedTime;
	float switchTime;
};

