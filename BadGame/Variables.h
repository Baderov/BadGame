#pragma once // used to provide additional control at compile time.
#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <list> // header file for working with the list.
#include "Button.h" // header file for working with buttons.
#include "Label.h" // header file for working with labels.
#include <mutex>

enum class MultiplayerErrors // enumeration for menu errors.
{
	NoErrors, ServerIsNotAvailable, NicknameIsAlreadyTaken, NickMustContainMoreChars, WrongIP, WrongPort
};

class GameVariable
{
private:
	struct GameVariables // declare structure for game variables.
	{
		sf::Vector2f mousePos;
		sf::Vector2f playerStartPos;

		sf::View view;

		std::wstring senderNickname;
		std::wstring nickname;
		std::wstring chatStr;
		std::wstring userStr;
		std::wstring chatPrefix;
		std::wstring scrollbarDir;
		std::wstring leftNick;
		std::wstring joinedNick;
		std::wstring joinedMsg;
		std::wstring leftMsg;
		std::wstring moveDir;
		std::string funcName;
		std::string serverIP;
		std::string tempPort;

		float fps;
		float aimLaserLength;
		float scrollbarDivisor;
		float dt;
		float menuTimer;

		int numberOfEnemies;
		int numberOfPlayers;
		int menuNum;
		unsigned short serverPort;
		int numOfLinesInChat;
		int numOfLinesInUserTextBox;
		size_t scrollbarStepNumber;

		bool showHitbox;
		bool showAimLaser;
		bool showLogs;
		bool isFullscreen;
		bool allowButtons;
		bool multiPlayerGame;
		bool singlePlayerGame;
		bool focusEvent;
		bool mainMenu;
		bool restartGame;
		bool chatContainsMouse;
		bool chatEnterText;
		bool recvMsg;
		bool sendMsg;
		bool leftFromServer;
		bool joinToServer;
		bool networkEnd;
		bool hideChat;
		bool inMenu;
		//bool autoScroll;

		char gameLanguage;
		char symbol;
		char input;
	} gVars;
	std::mutex mtx_gv;
public:
	sf::RenderWindow window;
	sf::Vector2f boxStartPositions[12];
	std::vector<std::unique_ptr<Button>> buttonsVec;
	std::vector<std::unique_ptr<Label>> labelsVec;
	sf::Text gameInfoText;
	sf::Text playerInfoText;
	sf::Text playerAmmoText;
	MultiplayerErrors multiplayerError;
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
	sf::Font consolasFont;
	sf::Color backgroundColor;
	sf::Color greyColor;
	sf::Clock fpsClock;
	sf::Clock menuClock;
	sf::Clock gameClock;
	sf::Time fpsPreviousTime;
	sf::Time fpsCurrentTime;

	// GETTERS.
	sf::View getView();

	sf::Vector2f getViewCenter();
	sf::Vector2f getViewSize();
	sf::Vector2f getMousePos();
	sf::Vector2f getPlayerStartPos();

	std::wstring getSenderNickname();
	std::wstring getMoveDir();
	std::wstring getNickname();
	std::wstring getUserStr();
	std::wstring getChatStr();
	std::wstring getChatPrefix();
	std::wstring getScrollbarDir();
	std::wstring getLeftNick();
	std::wstring getJoinedNick();
	std::wstring getLeftMsg();
	std::wstring getJoinedMsg();

	std::string getFuncName();
	std::string getServerIP();
	std::string getTempPort();

	float getFPS();
	float getAimLaserLength();
	float getScrollbarDivisor();
	float getDT();
	float getMenuTimer();

	int getNumberOfEnemies();
	int getNumberOfPlayers();
	int getMenuNum();
	unsigned short getServerPort();
	int getNumOfLinesInChat();
	int getNumOfLinesInUserTextBox();
	size_t getScrollbarStepNumber();

	bool getInMenu();
	bool getHideChat();
	bool getNetworkEnd();
	bool getShowHitbox();
	bool getShowAimLaser();
	bool getShowLogs();
	bool getIsFullscreen();
	bool getAllowButtons();
	bool getMultiPlayerGame();
	bool getSinglePlayerGame();
	bool getFocusEvent();
	bool getMainMenu();
	bool getRestartGame();
	bool getChatContainsMouse();
	bool getChatEnterText();
	bool getRecvMsg();
	bool getSendMsg();
	bool getLeftFromServer();
	bool getJoinToServer();

	char getGameLanguage();
	char getSymbol();
	char getInput();

	// SETTERS.
	void setViewCenter(sf::Vector2f tempViewCenter);
	void setViewSize(sf::Vector2f tempViewSize);
	void setMousePos(sf::Vector2f tempMousePos);
	void setPlayerStartPos(sf::Vector2f tempPlayerStartPos);
	void setSenderNickname(std::wstring tempSenderNickname);
	void setMoveDir(std::wstring tempMoveDir);
	void setNickname(std::wstring tempNickname);
	void setUserStr(std::wstring tempUserStr);
	void setChatStr(std::wstring tempChatStr);
	void setChatPrefix(std::wstring tempChatPrefix);
	void setScrollbarDir(std::wstring tempScrollbarDir);
	void setLeftNick(std::wstring tempLeftNick);
	void setJoinedNick(std::wstring tempJoinedNick);
	void setLeftMsg(std::wstring tempLefMsg);
	void setJoinedMsg(std::wstring tempJoinedMsg);
	void setFuncName(std::string tempFuncName);
	void setServerIP(std::string tempServerIP);
	void setTempPort(std::string temporaryPort);
	void setFPS(float tempFPS);
	void setAimLaserLength(float tempAimLaserLength);
	void setScrollbarDivisor(float tempScrollbarDivisor);
	void setDT(float tempDT);
	void setMenuTimer(float tempMenuTimer);
	void setNumberOfEnemies(int tempNumberOfEnemies);
	void setNumberOfPlayers(int tempNumberOfPlayers);
	void setMenuNum(int tempMenuNum);
	void setServerPort(unsigned short tempServerPort);
	void setNumOfLinesInChat(int tempNumOfLinesInChat);
	void setNumOfLinesInUserTextBox(int tempNumOfLinesInUserTextBox);
	void setScrollbarStepNumber(size_t tempScrollbarStepNumber);
	void setInMenu(bool tempInMenu);
	void setHideChat(bool tempHideChat);
	void setNetworkEnd(bool tempNetworkEnd);
	void setShowHitbox(bool tempShowHitbox);
	void setShowAimLaser(bool tempShowAimLaser);
	void setShowLogs(bool tempShowLogs);
	void setIsFullscreen(bool tempIsFullscreen);
	void setAllowButtons(bool tempAllowButtons);
	void setMultiPlayerGame(bool tempMultiplayerGame);
	void setSinglePlayerGame(bool tempSinglePlayerGame);
	void setFocusEvent(bool tempFocusEvent);
	void setMainMenu(bool tempMainMenu);
	void setRestartGame(bool tempRestartGame);
	void setChatContainsMouse(bool tempChatContainsMouse);
	void setChatEnterText(bool tempChatEnterText);
	void setRecvMsg(bool tempRecvMsg);
	void setSendMsg(bool tempSendMsg);
	void setLeftFromServer(bool tempLeftFromServer);
	void setJoinToServer(bool tempJoinToServer);
	void setGameLanguage(char tempGameLanguage);
	void setSymbol(char tempSymbol);
	void setInput(char tempInput);
};

void setColor(GameVariable* gv); // function for setting values for color.

void setFont(GameVariable* gv); // function for setting values for fonts.

void setText(GameVariable* gv); // function for setting values for text.

void setImage(GameVariable* gv); // function for setting values for images.

void setTexture(GameVariable* gv); // function for setting value for textures.

void setSprite(GameVariable* gv); // function to set value for sprites.

void setVariables(GameVariable* gv); // function for setting the values of global variables.