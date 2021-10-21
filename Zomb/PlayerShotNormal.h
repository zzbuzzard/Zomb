#pragma once
#include "PlayerProjectile.h"
#include <SFML/Graphics.hpp>

class GameState;

class PlayerShotNormal : public PlayerProjectile
{
public:
	PlayerShotNormal(sf::Vector2f pos, float angle, const WeaponStats &stat);
	~PlayerShotNormal();
};

