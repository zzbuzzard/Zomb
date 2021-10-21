#pragma once
class Stats
{
public:
	Stats();
	Stats(int hp_, int def_, int agi_, int acc_, int int_);
	~Stats();

	void addStats(const Stats &other) {
		hp += other.hp; def += other.def; agi += other.agi; acc += other.acc; intt += other.intt;
		//return Stats(hp + other.hp, def + other.def, agi + other.agi, acc + other.acc, dex + other.dex, intt + other.intt);
	}

	// Get stats
	int getHPS() const;
	int getDefS() const;
	int getAgiS() const;
	int getAccS() const;
	int getIntS() const;

	// Get in game effect of stats
	float getHP() const;
	float getDef() const;
	float getSpeed() const;
	float getAcc() const;
	// float getSpecialCooldown() const;
	float getSpecialMultiplier() const;

private:
public:
private:
	int hp, def, agi, acc, intt;
};

