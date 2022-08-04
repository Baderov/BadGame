#include "Label.h" // header file for working with labels.

Label::Label(std::wstring str, sf::Vector2f labelPos, unsigned int textSize, std::string name) // label constructor.
{
	font.loadFromFile("consolas.ttf");
	this->name = name;

	this->text.setFont(font);
	this->text.setCharacterSize(textSize);
	this->text.setString(str);
	this->text.setOrigin(round(this->text.getLocalBounds().left + (this->text.getLocalBounds().width / 2.f)), round(this->text.getLocalBounds().top + (this->text.getLocalBounds().height / 2.f)));
	this->text.setPosition(labelPos);
	this->text.setFillColor(sf::Color::Cyan);
}

std::string& Label::getName() // function to get label name.
{
	return name;
}

sf::Text& Label::getText() // function to get label text.
{
	return text;
}