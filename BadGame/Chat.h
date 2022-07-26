#pragma once
#include <SFML/Graphics.hpp>
#include "RichText.hpp"
#include "Variables.h"
#include <windows.h>

class Chat
{
public:
	struct chatStrings
	{
		chatStrings(std::wstring prefix, std::wstring msg, int countOfLines, bool joinedTheServer, bool leftTheServer)
		{
			this->prefix = prefix;
			this->msg = msg;
			this->countOfLines = countOfLines;
			this->joinedTheServer = joinedTheServer;
			this->leftTheServer = leftTheServer;
		}
		std::wstring prefix = L"";
		std::wstring msg = L"";
		int countOfLines = 1;
		bool joinedTheServer = false;
		bool leftTheServer = false;
	};

	Chat(sf::RenderWindow& window);
	sf::RectangleShape& getOuterScrollBar();
	sf::RectangleShape& getInnerScrollBar();
	sf::RectangleShape& getChatTextBox();
	sf::RectangleShape& getUserTextBox();
	std::vector<std::unique_ptr<chatStrings>>& getStrVector();
	sf::Font& getFont();
	sfe::RichText& getChatText();
	sfe::RichText& getUserText();

	void addString(GameVariables* gv, Chat& chat);

	void addNewLine(GameVariables* gv, Chat& chat);

	void moveUp(GameVariables* gv, Chat& chat);

	void moveDown(GameVariables* gv, Chat& chat);

	bool trimString(std::wstring& str, GameVariables* gv);
private:
	sf::RectangleShape outerScrollBar, innerScrollBar, chatTextBox, userTextBox;
	sf::Color greyColor;
	std::vector<std::unique_ptr<chatStrings>> strVector;
	sf::Font font;
	sfe::RichText chatText, userText;
};