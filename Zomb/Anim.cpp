#include "pch.h"
#include "Anim.h"

Anim::Anim(sf::Texture &texture, sf::Vector2i imageCount, float switchTime)
{

	textureRect = sf::IntRect(0, 0, texture.getSize().x/imageCount.x, 
		texture.getSize().y/imageCount.y);
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	elapsedTime = 0;

	pos = sf::Vector2i(0, 0);
	SetRect();
}


Anim::~Anim()
{
}

void Anim::Update(float deltaTime) {
	elapsedTime += deltaTime;
	if (elapsedTime >= switchTime) {
		elapsedTime -= switchTime;
		pos.x++;
		pos.x %= imageCount.x;
		SetRect();
	}
}

void Anim::SetRow(int y) {
	if (y == pos.y) return;
	pos.x = 0;
	pos.y = y;
	SetRect();
}


void Anim::SetRect() {
	textureRect.left = pos.x * textureRect.width;
	textureRect.top = pos.y * textureRect.height;
	
}
