#include "pch.h"
#include "CircleObj.h"

class GameState;

// CircleObj is the base class for enemies and the player.
// A circle object has a radius, and a texture
// It can also have collision events registered.

CircleObj::CircleObj(ObjectType myType, sf::Vector2f pos, TEXTURE _texture, float rad, float imageRadius) : type(myType)
{
	if (imageRadius == -1) imageRadius = rad;
	this->pos = pos;
	this->texture = &textures[_texture];
	radius = rad;
	this->imageRadius = imageRadius;
	rect = sf::RectangleShape(sf::Vector2f(imageRadius*2, imageRadius*2));
	rect.setOrigin(imageRadius, imageRadius);
	rect.setTexture(texture);
	rot = 0;
}

void CircleObj::update(GameState *state) {
	rect.setPosition(pos);
}

void CircleObj::draw(sf::RenderWindow *window) const {
	sf::Transform transform;
	transform.rotate(rot, pos);

	window->draw(rect, transform);
}

CircleObj::~CircleObj()
{
}
