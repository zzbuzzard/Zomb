#include "pch.h"
#include "Button.h"
#include "Media.h"
#include "GameState.h"

Button::Button() {
	usesFg = false;
	setTexture(nullptr);
	visible = true;

	text = sf::Text("", g_candara, 60);
	text.setFillColor(sf::Color::Black);
}

Button::Button(sf::Vector2f size_, sf::Vector2f pos_, sf::Texture *texture)
{
	usesFg = false;

	setPosition(pos_);
	setSize(size_);
	setTexture(texture);

	text = sf::Text("", g_candara, 60);
	text.setFillColor(sf::Color::Black);

	visible = true;
}

void Button::setForeground(sf::Texture *fg) {
	usesFg = true;
	foreground.setTexture(fg, true);
	setSize(buttonBox.getSize());
}

void Button::setTextSize(float size) {
	text.setCharacterSize(size);
}

void Button::setTextColor(sf::Color col) {
	text.setFillColor(col);
}


void Button::setForegroundScale(float scale) {
//	foreground.setScale(scale, scale);
	fgScale = scale;

	foreground.setSize(fgScale * size);
	foreground.setOrigin(size * 0.5f * fgScale);
}

void Button::setSize(sf::Vector2f size_) {
	size = size_;

	buttonBox.setSize(size);
	buttonBox.setOrigin(size*0.5f);

	foreground.setSize(fgScale * size);
	foreground.setOrigin(size * 0.5f * fgScale);
}

void Button::setTexture(sf::Texture *texture) {
	if (texture != nullptr) {
		buttonBox.setTexture(texture, true);
		buttonBox.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)texture->getSize()));
	}
}

void Button::setBackgroundColor(sf::Color col) {
	buttonBox.setFillColor(col);
}

void Button::setForegroundColor(sf::Color col) {
	foreground.setFillColor(col);
}

void Button::setString(const std::string &st) {
	text.setString(st);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void Button::setPosition(sf::Vector2f pos_) {
	buttonBox.setPosition(pos_);
	text.setPosition(pos_);
	foreground.setPosition(pos_);
	pos = pos_;
}

void Button::draw(sf::RenderWindow *window) const {
	if (visible) {
		//buttonBox.setPosition(pos);
		//text.setPosition(pos);
		window->draw(buttonBox);

		if (usesFg) {
			//foreground.setPosition(pos);
			window->draw(foreground);
		}

		window->draw(text);
	}
}

Button::~Button()
{
}

// Box is offset.x - width / 2 .. width / 2
bool Button::isClicked(sf::Vector2f click) const {
	sf::Vector2f s = buttonBox.getSize();
	return click.x > pos.x - s.x / 2 && click.x < pos.x + s.x / 2 && click.y > pos.y - s.y / 2 && click.y < pos.y + s.y / 2;

	//float m = window->getSize().y / VIEW_HEIGHT;
	//return pos.x > (offset.x - s.x/2)*m && pos.x < (offset.x + s.x/2)*m && pos.y > (offset.y - s.y/2)*m && pos.y < (offset.y + s.y/2)*m;
}



