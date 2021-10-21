#pragma once

#include <SFML/Graphics.hpp>

namespace util {
	extern double PI;

	float rand(float a, float b);
	int randint(int a, int b); //inclusive

	sf::Color colorLerp(sf::Color a, sf::Color b, float t);

	std::string floatToString(float a, int decimal_places = 2);

	double mag(const sf::Vector2f &a);
	double dist(const sf::Vector2f &a, const sf::Vector2f &b);
	double ang(const sf::Vector2f &a);
	double dot(const sf::Vector2f &a, const sf::Vector2f &b);
	double crossMag(const sf::Vector2f &a, const sf::Vector2f &b);
	std::pair<double, double> solveQuadratic(double a, double b, double c);

	sf::Vector2f predictMovementCircular(sf::Vector2f myPos, sf::Vector2f otherPos, sf::Vector2f otherSpd, float projectileSpeed);
	sf::Vector2f predictMovementLinear(sf::Vector2f myPos, sf::Vector2f otherPos, sf::Vector2f otherSpd, float projectileSpeed);

	sf::Vector2f bounce(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f otherpos);
}

class Util
{
public:
	Util();
	~Util();
};

