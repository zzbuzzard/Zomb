#include "pch.h"
#include "Projectile.h"
#include "GameState.h"
#include "Util.h"

Projectile::Projectile(sf::Vector2f pos, TEXTURE texture, float life_, float angle, float damage, float radius, float speed, float imageRadius) :
	CircleObj(ObjectType::PROJECTILE, pos, texture, radius, imageRadius),
	spd(speed),
	dmg(damage),
	life(life_)
{
	rot = (float)(angle * 180 / util::PI);
	moveV = sf::Vector2f(spd*cos(angle), spd*sin(angle));
}


Projectile::~Projectile()
{
}

bool Projectile::isAlive(GameState *state) const {
	if (life != -10 && life < 0) return false;
	if (hasHit) return false;
	if (util::mag(pos) + radius > state->getGameRadius()) return false;
	return true;
}

void Projectile::update(GameState *state) {
	pos += deltaTime * moveV;
	CircleObj::update(state);
	
	if (life != -10) life -= deltaTime;
}
