#pragma once // used to provide additional control at compile time.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include "RichText.hpp" // improved sf::Text.
#include "Variables.h" // header file for global variables.
#include <windows.h> // windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API.

class Chat // declare a class for creating a chat.
{
public:
	struct chatStrings // chatStrings structure.
	{
		chatStrings(std::wstring prefix, std::wstring msg, int countOfLines, bool joinedTheServer, bool leftTheServer) // chatStrings constructor.
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
	Chat(); // chat constructor.
	sf::RectangleShape& getOuterScrollBar(); // function to get outer scrollbar.
	sf::RectangleShape& getInnerScrollBar(); // function to get inner scrollbar.
	sf::RectangleShape& getChatTextBox(); // function to get chat textbox.
	sf::RectangleShape& getUserTextBox(); // function to get user textbox.
	std::vector<std::unique_ptr<chatStrings>>& getStrVector(); // function to get string vector.
	sf::Font& getFont(); // function to get font.
	sfe::RichText& getChatText(); // function to get chat text.
	sfe::RichText& getUserText(); // function to get user text.

	void setOuterScrollBarPos(float posX, float posY);
	void setInnerScrollBarPos(float posX, float posY);
	void setChatTextBoxPos(float posX, float posY);
	void setUserTextBoxPos(float posX, float posY);
	void setChatTextPos(float posX, float posY);
	void setUserTextPos(float posX, float posY);


	void addString(GameVariable* gv, Chat& chat); // function to add a string to a vector.
	void addEndLine(GameVariable* gv, Chat& chat); // function to add the end of the line.
	void scrollUp(GameVariable* gv, Chat& chat); // function to scroll up the chat.
	void scrollDown(GameVariable* gv, Chat& chat); // function to scroll down the chat.
	bool trimString(std::wstring& str, GameVariable* gv); // string trim function.

	float scrollbarDivisor;
	size_t scrollbarStepNumber;
	std::wstring scrollbarDir;
private:
	sf::RectangleShape outerScrollBar, innerScrollBar, chatTextBox, userTextBox;
	sf::Color greyColor;
	std::vector<std::unique_ptr<chatStrings>> strVector;
	sf::Font font;
	sfe::RichText chatText, userText;
};

void chatUpdate(GameVariable* gv, Chat& chat);

void updateUserTextBox(GameVariable* gv, Chat& chat);

void updateScrollbarDir(GameVariable* gv, Chat& chat);