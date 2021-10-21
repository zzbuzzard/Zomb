#include "pch.h"
#include "FootWalk.h"
#include "State.h"
#include "Media.h"
#include "Util.h"

const sf::Vector2f defaultFootSize(1.35, 1.35*0.7);
const float defaultGap = 0.6, defaultMoveMag = 0.6;

FootWalk::FootWalk()
{
	L = sf::RectangleShape();
	//L.setSize(defaultFootSize);
	L.setTexture(&textures[T_ENEMY_FOOT]);

	R = sf::RectangleShape();
	//R.setSize(defaultFootSize);
	R.setTexture(&textures[T_ENEMY_FOOT]);

	//L.setOrigin(L.getSize()*0.5f);
	//R.setOrigin(R.getSize()*0.5f);

	t = util::rand(0, 2*util::PI);
}


FootWalk::~FootWalk()
{
}

void FootWalk::setScale(float scale_) {
	scale = scale_;
	L.setSize(defaultFootSize*scale); L.setOrigin(L.getSize()*0.5f);
	R.setSize(defaultFootSize*scale); R.setOrigin(R.getSize()*0.5f);
	gap = defaultGap * scale;
	moveMag = defaultMoveMag * scale;
}
void FootWalk::setPosition(sf::Vector2f pos_) {
	pos = pos_;
	update(0);
}

//#include <iostream>
void FootWalk::update(float speed) {
	t += deltaTime * speed * 0.02f;
	float angR = ang - util::PI/2;

	//std::cout << "ang = " << ang << std::endl;

	R.setPosition(pos + gap * sf::Vector2f(cos(angR), sin(angR)) + moveMag * sin(t)*sf::Vector2f(cos(ang), sin(ang)));
	L.setPosition(pos - gap * sf::Vector2f(cos(angR), sin(angR)) - moveMag * sin(t)*sf::Vector2f(cos(ang), sin(ang)));
}

void FootWalk::setAngle(float ang_) {
	ang = ang_;
}

void FootWalk::draw(sf::RenderWindow *window) const {
	//window->draw(L); window->draw(R);

	sf::Transform transform;
	transform.rotate(ang * 180 / util::PI, R.getPosition());
	window->draw(R, transform);

	sf::Transform transform2;
	transform2.rotate(ang * 180 / util::PI , L.getPosition());
	window->draw(L, transform2);
}
