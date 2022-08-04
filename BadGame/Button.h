#pragma once // used to provide additional control at compile time.
#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.

class Button
{
public:
	Button(sf::Vector2f buttonSize, sf::Vector2f buttonPos, std::wstring str, unsigned int textSize, std::string name, bool textOrigin); // button constructor.
	sf::RectangleShape& getSprite(); // function to get button sprite.
	sf::Text& getText(); // function to get button text.
	std::string& getName(); // function to get button name.
private:
	sf::Text text;
	sf::RectangleShape sprite;
	sf::Font font;
	std::string name;
};
