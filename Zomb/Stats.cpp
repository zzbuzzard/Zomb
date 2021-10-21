#include "pch.h"
#include "Stats.h"


Stats::Stats() : hp(0), def(0), agi(0), acc(0), intt(0)
{
}


Stats::Stats(int hp_, int def_, int agi_, int acc_, int int_) :
	hp(hp_), def(def_), agi(agi_), acc(acc_), intt(int_)
{
}

Stats::~Stats()
{
}

int Stats::getHPS() const { return hp; }
int Stats::getDefS() const { return def; }
int Stats::getAgiS() const { return agi; }
int Stats::getAccS() const { return acc; }
int Stats::getIntS() const { return intt; }


float Stats::getHP() const {
	return hp;
}

// Damage multiplier
const float mulAt100 = 0.4f;
float Stats::getDef() const {
	return 1 - def * (1 - mulAt100) / 100;
}

const float baseSpd = 425.0f, spdAt75 = 850.0f;
float Stats::getSpeed() const {
	return baseSpd + agi * (spdAt75 - baseSpd)/75;
}

const float baseAcc = 0.4f, accAt100 = 0.0035f;
float Stats::getAcc() const {
	return baseAcc - acc * (baseAcc - accAt100) / 100;
}

// first we work out shots per second
// dexterity = 0 : 1
// dexterity = 50 : 10
//const float baseShots = 3.0f, shotsAt100 = 500.0f; //Max is 50 though
//float Stats::getShootCooldown() const {
//	return 0.65f / baseShots + dex * (1 / shotsAt100 - 1 / baseShots) / 100;
//	//return 1 / (baseShots + dex * (shotsAt60 - baseShots) / 60);
//}

const float baseSp = 1.0f, spAt100 = 0.55f;
float Stats::getSpecialMultiplier() const {
	return baseSp + (spAt100 - baseSp) / 100 * intt;
}

//const float baseSp = 0.05f, spAt50 = 0.2f;
//float Stats::getSpecialCooldown() const {
//	return 1 / (baseSp + intt * (spAt50 - baseSp) / 50);
//}