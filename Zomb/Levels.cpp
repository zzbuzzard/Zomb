#include "pch.h"
#include "Levels.h"
#include "Media.h"
#include <fstream>

levelType levelTypes[NUM_LEVELS] = {
	levelType("The hills", T_HILLS_BG, T_HILLS_FG, LevelAppearance(2000, T_HILLS_GG, sf::Color::Black, 15),
		{}),
	levelType("The cave", T_CAVE_BG, T_CAVE_FG, LevelAppearance(1600, T_CAVE_GG, sf::Color::Black, 16, T_FADE_CIRCLE),
		{pli(L_HILLS, 10)}),
	levelType("Test level", T_HILLS_BG, T_HILLS_FG, LevelAppearance(2000, T_CAVE_GG, sf::Color::White, 20),
		{ pli(L_HILLS, 10), pli(L_CAVE, 5) }),
};

LEVEL levelOrder[NUM_LEVELS] = {
	L_HILLS, L_CAVE, L_HILLSTEST
};

int levelMaxWaveBeaten[NUM_LEVELS];

void saveWaves() {
	std::ofstream fout("levels");
	for (int i = 0; i < NUM_LEVELS; i++) {
		fout << levelMaxWaveBeaten[i] << " ";
	}
	fout << "-1";
	fout.close();
}


void saveMaxWave(LEVEL level, int wave) {
	if (level >= 0 && level < NUM_LEVELS) {
		if (wave > levelMaxWaveBeaten[level]) {
			levelMaxWaveBeaten[level] = wave;
			saveWaves();
		}
	}
}

void loadMaxWaves() {
	std::ifstream fin("levels");

	for (int i = 0; i < NUM_LEVELS; i++) {
		levelMaxWaveBeaten[i] = 0;
	}

	if (fin.good()) {
		int i, n;
		for (i = 0; i < NUM_LEVELS; i++) {
			fin >> n;
			if (n == -1) break; // meaning we've added a new level since
			levelMaxWaveBeaten[i] = n;
		}
	}
	//for (int i = 0; i < NUM_LEVELS; i++) {
	//	std::cout << "Level: " << std::get<0>(levelTypes[i]) << ", Wave: " << levelMaxWaveBeaten[i] << std::endl;
	//}
}

bool isUnlocked(LEVEL level) {
	const levelType &l = levelTypes[level];
	const std::vector<pli> &levs = std::get<4>(l);
	for (const pli &i : levs) {
		if (getMaxWave(i.first) < i.second) return false;
	}
	return true;
}

int getMaxWave(LEVEL level) {
	if (level < 0 || level >= NUM_LEVELS) return -1;
	return levelMaxWaveBeaten[level];
}

