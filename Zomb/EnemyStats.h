#pragma once
class EnemyStats
{
public:
	EnemyStats(float hp_, float def_, float spd_, float dmg_, int coins_);
	~EnemyStats();

	float hp, def, spd, dmg;
	int coins;
};

// Enemies have life, defence, speed, damage when u walk into them, coins when killed