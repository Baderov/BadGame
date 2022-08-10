#pragma once // used to provide additional control at compile time.
#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <list> // header file for working with the list.
#include "Button.h" // header file for working with buttons.
#include "Label.h" // header file for working with labels.

enum class MenuErrors // enumeration for menu errors.
{
	NoErrors, ServerIsNotAvailable, NicknameIsAlreadyTaken, NickMustContainMoreChars
}; 

struct GameVariables // declare structure for game variables.
{
	MenuErrors menuError;

	sf::RenderWindow window;

	sf::Event event;

	sf::Image playerImage;
	sf::Image enemyImage;
	sf::Image wallImage;
	sf::Image bulletImage;
	sf::Image boxImage;
	sf::Image goldCoinImage;
	sf::Image goldCoinHUDImage;
	sf::Image hpBonusImage;

	sf::Texture goldCoinHUDTexture;

	sf::Sprite goldCoinHUDSprite;

	sf::RectangleShape aimLaser;

	sf::CircleShape playerDestination;

	sf::View view;

	sf::Font consolasFont;
	
	sf::Text gameInfoText;
	sf::Text playerInfoText;
	sf::Text playerAmmoText;

	sf::Vector2f mousePos;
	sf::Vector2f playerStartPos;
	sf::Vector2f boxStartPositions[12];

	sf::Color backgroundColor;
	sf::Color greyColor;

	sf::Clock clock;
	sf::Clock fpsClock;
	sf::Clock menuClock;

	sf::Time fpsPreviousTime;
	sf::Time fpsCurrentTime;

	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;

	std::wstring nickname;
	std::wstring chatStr;
	std::wstring userStr;
	std::wstring chatPrefix;
	std::wstring scrollbarDir;
	std::wstring leftNick;
	std::wstring joinedNick;
	std::wstring joinedMsg;
	std::wstring leftMsg;
#ifdef _DEBUG
	std::string funcName;
#endif
	std::string serverIP;
	std::string tempPort;

	float fps;
	float aimLaserLength;
	float scrollbarDivisor;

	sf::Int32 menuTimer;
	sf::Int64 dt;
	sf::Int64 divisor;
	int numberOfEnemies;
	int numberOfPlayers;
	int menuNum;
	int serverPort;
	int numOfLinesInChat;
	int numOfLinesInUserTextBox;
	size_t scrollbarStepNumber;

	bool showHitbox;
	bool showAimLaser;
	bool showLogs;
	bool isGameOver;
	bool isFullscreen; 
	bool allowButtons;
	bool multiPlayerGame;
	bool singlePlayerGame;
	bool focusEvent;
	bool exitFromMenu;
	bool mainMenu;
	bool restartGame;
	bool chatContainsMouse;
	bool chatEnterText;
	bool recvMsg;
	bool sendMsg;
	bool leftFromServer;
	bool joinToServer;
	//bool autoScroll;

	char gameLanguage;
	char symbol;
	char input;
};

void setColor(GameVariables* gv); // function for setting values for color.

void setFont(GameVariables* gv); // function for setting values for fonts.

void setText(GameVariables* gv); // function for setting values for text.

void setImage(GameVariables* gv); // function for setting values for images.

void setTexture(GameVariables* gv); // function for setting value for textures.

void setSprite(GameVariables* gv); // function to set value for sprites.

void setVariables(GameVariables* gv); // function for setting the values of global variables.