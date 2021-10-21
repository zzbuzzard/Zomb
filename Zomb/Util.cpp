#include "pch.h"
#include "Util.h"
#include <iostream>
#include <random>

#define _USE_MATH_DEFINES
#include <math.h>

#include <iomanip>
#include <sstream>


namespace util {
	double PI = M_PI;

	float rand(float a, float b)
	{
		static std::mt19937 gen;
		static bool set = false;
		static std::uniform_real_distribution<float> dis(0, 1);
		if (!set) {
			set = true;
			gen = std::mt19937((unsigned int)time(NULL));
		}
		return a + (b - a)*dis(gen);
	}

	int randint(int a, int b)
	{
		return (int)rand((float)a, (float)b + 0.999999f);
	}

	sf::Color colorLerp(sf::Color a, sf::Color b, float t) {
		return sf::Color(a.r*(1-t) + b.r*t, a.g*(1-t) + b.g*t, a.b*(1-t) + b.b*t);
	}

	std::string floatToString(float a, int decimal_places) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(decimal_places) << a;
		return stream.str();
	}

	double mag(const sf::Vector2f &a) {
		return sqrt(a.x*a.x + a.y*a.y);
	}

	double dist(const sf::Vector2f &a, const sf::Vector2f &b) {
		return mag(a - b);
	}

	double ang(const sf::Vector2f &a) {
		return atan2(a.y, a.x);
	}

	double dot(const sf::Vector2f &a, const sf::Vector2f &b) {
		return a.x*b.x + a.y*b.y;
	}

	double crossMag(const sf::Vector2f &a, const sf::Vector2f &b) {
		return a.x * b.y - a.y * b.x;
	}

	std::pair<double, double> solveQuadratic(double a, double b, double c) {
		// -b +- sqrt(b^2 - 4ac) / 2a
		if (b*b - 4 * a*c < 0 || a == 0) return std::pair<double, double>(0, 0);
		double pm = sqrt(b*b - 4 * a*c);
		return std::pair<double, double>((-b - pm) / (2*a), (-b + pm) / (2*a));
	}

	// Attempts to predict somethings position for better firing
	sf::Vector2f predictMovementCircular(sf::Vector2f myPos, sf::Vector2f otherPos, sf::Vector2f otherSpd, float projectileSpeed) {
		// we want their number of degrees per second
		// then we need the time taken for us to move that far

		if (mag(otherSpd) < 0.01f) return otherPos;

		// We need the component of otherspd perpendicular to currentDisplacement
		sf::Vector2f currentDisplacement = otherPos - myPos;

		double R = dist(myPos, otherPos);

		double sinAngle = crossMag(otherPos, otherSpd) / (mag(otherPos) * mag(otherSpd));

		// distance travelled per second perpendicular
		double perpendicularComponent = util::mag(otherSpd) * sinAngle;

//		std::cout << "Perpendicular component of velocity = " << perpendicularComponent << std::endl;
//		std::cout << "Radians/s = " << perpendicularComponent / R << std::endl;

		// Distance / 2 PI R   * 2 PI = Distance / R

		float timeNeeded = (float)(R / projectileSpeed);

		double angle = perpendicularComponent * timeNeeded / R + util::ang(currentDisplacement);

		return myPos + (float)R * sf::Vector2f((float)cos(angle), (float)sin(angle));
	}

	sf::Vector2f predictMovementLinear(sf::Vector2f myPos, sf::Vector2f otherPos, sf::Vector2f otherSpd, float projectileSpeed) {
		if (mag(otherSpd) < 0.01f) return otherPos;
		float X1 = otherPos.x - myPos.x, X2 = otherSpd.x;
		float Y1 = otherPos.y - myPos.y, Y2 = otherSpd.y;
		float Vsq = projectileSpeed * projectileSpeed;

		float A = X2 * X2 + Y2 * Y2 - Vsq, B = 2 * (X1*X2 + Y1 * Y2), C = X1 * X1 + Y1 * Y1;
		auto p = solveQuadratic(A, B, C);
		float t = (float)((p.first > 0) ? p.first : p.second);
		if (t == 0) return otherPos;

		sf::Vector2f displacement = sf::Vector2f(X1 + X2*t, Y1 + Y2*t);
		return myPos + displacement;
	}

	sf::Vector2f bounce(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f otherpos) {
		sf::Vector2f inwards = otherpos - pos;
		inwards = inwards / (float)mag(inwards);
		float magIn = dot(inwards, vel);

		return vel - 2 * magIn * inwards;
	}
}


Util::Util()
{
}


Util::~Util()
{
}
