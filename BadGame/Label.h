#pragma once // used to provide additional control at compile time.
#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.

class Label // create a Label class.
{
public:
	Label(std::wstring str, sf::Vector2f labelPos, unsigned int textSize, std::string name); // label constructor.
	std::string& getName(); // function to get label name.
	sf::Text& getText(); // function to get label text.
private:
	sf::Text text;
	sf::Font font;
	std::string name;
};
