#include "pch.h"
#include "PlayerShotNormal.h"
#include "CircleObj.h"
#include "Media.h"
#include "GameState.h"
#include "PlayerProjectile.h"

PlayerShotNormal::PlayerShotNormal(sf::Vector2f pos, float angle, const WeaponStats &stats)
	: PlayerProjectile(pos, angle, stats) {
}


PlayerShotNormal::~PlayerShotNormal()
{
}

