#include "Button.h" // header file for working with buttons.

Button::Button(sf::Vector2f buttonSize, sf::Vector2f buttonPos, std::wstring str, unsigned int textSize, std::string name, bool textOrigin) // button constructor.
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

sf::RectangleShape& Button::getSprite() // function to get button sprite.
{
	return sprite;
}

sf::Text& Button::getText() // function to get button text.
{
	return text;
}

std::string& Button::getName() // function to get button name.
{
	return name;
}