#pragma once
#include <SFML/Graphics.hpp>
#include "Media.h"

class GameState;

enum class ObjectType {
	PLAYER,
	ENEMY,
	PROJECTILE,
	NOCOLLISION,
};

class CircleObj
{
public:
	CircleObj(ObjectType myType, sf::Vector2f pos, TEXTURE texture, float rad, float imageRadius = -1);
	virtual ~CircleObj();

	virtual void collide(CircleObj *other) = 0;
	virtual void update(GameState *state);
	virtual bool isAlive(GameState *state) const = 0;
	virtual void draw(sf::RenderWindow *window) const;

	float getRadius() const {
		return radius;
	}
	sf::Vector2f getPosition() const {
		return pos;
	}
	virtual void moveBy(const sf::Vector2f &displacement) {
		pos += displacement;
	}

private:

public:
	const ObjectType type;
	sf::Vector2f pos;

protected:
	float radius, rot, imageRadius;

private:
	sf::Texture *texture;
	sf::RectangleShape rect;
};

