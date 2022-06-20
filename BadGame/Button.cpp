#include "Button.h"

Button::Button(sf::Vector2f buttonSize, sf::Vector2f buttonPos, std::wstring str, int textSize, std::string name, bool textOrigin)
{
	font.loadFromFile("consolas.ttf");

	this->name = name;

	this->sprite.setSize(buttonSize);
	this->sprite.setOrigin(this->sprite.getSize().x / 2.f, this->sprite.getSize().y / 2.f);
	this->sprite.setPosition(buttonPos);
	this->sprite.setFillColor(sf::Color::White);

	this->text.setFont(font);
	this->text.setCharacterSize(textSize);
	this->text.setString(str);
	if (textOrigin == true)
	{
		this->text.setOrigin(round(this->text.getLocalBounds().left + (this->text.getLocalBounds().width / 2.f)), round(this->text.getLocalBounds().top + (this->text.getLocalBounds().height / 2.f)));
	}
	this->text.setPosition(this->sprite.getPosition());
	this->text.setFillColor(sf::Color::Black);
}

std::string& Button::getName()
{
	return name;
}

sf::RectangleShape& Button::getSprite()
{
	return sprite;
}

sf::Text& Button::getText()
{
	return text;
}