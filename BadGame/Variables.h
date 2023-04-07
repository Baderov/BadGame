#pragma once // used to provide additional control at compile time.
#include "Entity.h"
#include "Chat.h"

const sf::Vector2f wallSize(5000.f, 64.f);

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
		sf::Vector2u windowSize;

		sf::View gameView;
		sf::View menuView;

		std::wstring nickname;
		std::wstring moveDir;
		std::string funcName;
		std::string serverIP;
		std::string tempPort;

		float fps;
		float dt;
		float menuTimer;
		float serverTime;

		int menuNum;
		unsigned short serverPort;

		sf::Int32 ping;
		sf::Int32 pingDelay;
		unsigned int fpsLimiter;

		bool showPlayersList;
		bool showHitbox;
		bool showAimLaser;
		bool showLogs;
		bool showMinimap;
		bool isConnected;
		bool isFullscreen;
		bool isVsync;
		bool isMultiplayer;
		bool isSingleplayer;
		bool focusEvent;
		bool mainMenu;
		bool restartGame;
		bool connectsToServer;
		bool inMenu;
		bool serverIsNotAvailable;
		bool connectButtonPressed;
		//	bool chatAutoScroll;

		char gameLanguage;
		char symbol;
		char input;
	} gVars;
	std::mutex mtx_gv;
public:
	std::vector<std::unique_ptr<Entity>> entitiesVec;
	std::mutex entities_mtx;
	sf::UdpSocket sock;
	sf::RenderWindow window;
	tgui::Gui gui;
	sf::Vector2f boxStartPositions[24];
	sf::Text gameInfoText;
	sf::Text playerInfoText;
	sf::Text playerAmmoText;
	sf::Text connectionErrorText;
	sf::Text OKButtonText;
	MultiplayerErrors multiplayerError;
	sf::Event event;
	sf::Image playerImage;
	sf::Image enemyImage;
	sf::Image bulletImage;
	sf::Image boxImage;
	sf::Image goldCoinImage;
	sf::Image goldCoinHUDImage;
	sf::Image hpBonusImage;
	sf::Texture goldCoinHUDTexture;
	sf::Sprite goldCoinHUDSprite;
	sf::RectangleShape aimLaser;
	sf::RectangleShape connectionErrorRS;
	sf::RectangleShape OKButtonRS;
	sf::CircleShape playerDestination;
	sf::Font consolasFont;
	sf::Color backgroundColor;
	sf::Color greyColor;
	sf::Clock fpsClock;
	sf::Clock menuClock;
	sf::Clock gameClock;
	sf::Clock serverClock;
	sf::Time fpsPreviousTime;
	sf::Time fpsCurrentTime;

	// GETTERS.
	sf::View getGameView();
	sf::View getMenuView();
	sf::Vector2f getGameViewCenter();
	sf::Vector2f getGameViewSize();
	sf::Vector2f getMenuViewCenter();
	sf::Vector2f getMenuViewSize();
	sf::Vector2f getMousePos();
	sf::Vector2f getPlayerStartPos();
	sf::Vector2u getWindowSize();

	std::wstring getMoveDir();
	std::wstring getNickname();

	std::string getFuncName();
	std::string getServerIP();
	std::string getTempPort();
	float getFPS();
	float getDT();
	float getMenuTimer();
	float getServerTime();
	float getServerClockElapsedTime();
	unsigned short getServerPort();
	unsigned int getFPSLimiter();
	int getMenuNum();

	sf::Int32 getPingDelay();
	bool getIsConnected();
	bool getConnectButtonPressed();
	bool getShowPlayersList();
	bool getInMenu();
	bool getConnectsToServer();
	bool getShowHitbox();
	bool getShowAimLaser();
	bool getShowLogs();
	bool getShowMinimap();
	bool getIsVsync();
	bool getIsFullscreen();
	bool getIsMultiplayer();
	bool getIsSingleplayer();
	bool getFocusEvent();
	bool getMainMenu();
	bool getRestartGame();

	bool getServerIsNotAvailable();
	//bool getChatAutoScroll();
	char getGameLanguage();
	char getSymbol();
	char getInput();

	// SETTERS.
	void setWindowView(sf::View view);
	void setGameViewCenter(sf::Vector2f tempViewCenter);
	void setGameViewSize(sf::Vector2f tempViewSize);
	void setMenuViewCenter(sf::Vector2f tempViewCenter);
	void setMenuViewSize(sf::Vector2f tempViewSize);
	void setMousePos(sf::Vector2f tempMousePos);
	void setPlayerStartPos(sf::Vector2f tempPlayerStartPos);
	void setWindowSize(sf::Vector2u tempWindowSize);
	void setMoveDir(std::wstring tempMoveDir);
	void setNickname(std::wstring tempNickname);
	void setFuncName(std::string tempFuncName);
	void setServerIP(std::string tempServerIP);
	void setTempPort(std::string temporaryPort);
	void setFPS(float tempFPS);
	void setDT(float tempDT);
	void setMenuTimer(float tempMenuTimer);
	void setServerTime(float tempServerTime);
	void setFPSLimiter(unsigned int tempFPSLimiter);
	void setMenuNum(int tempMenuNum);
	void setServerPort(unsigned short tempServerPort);
	void setPingDelay(sf::Int32 tempPingDelay);
	void setIsConnected(bool tempIsConnected);
	void setConnectButtonPressed(bool tempConnectButtonPressed);
	void setShowPlayersList(bool tempShowPlayersList);

	void setInMenu(bool tempInMenu);
	void setConnectsToServer(bool tempConnectsToServer);
	void setShowHitbox(bool tempShowHitbox);
	void setShowAimLaser(bool tempShowAimLaser);
	void setShowLogs(bool tempShowLogs);
	void setShowMinimap(bool tempShowMinimap);
	void setIsFullscreen(bool tempIsFullscreen);
	void setIsVsync(bool tempIsVsync);
	void setIsMultiplayer(bool tempIsMultiplayer);
	void setIsSingleplayer(bool tempIsSingleplayer);
	void setFocusEvent(bool tempFocusEvent);
	void setMainMenu(bool tempMainMenu);
	void setRestartGame(bool tempRestartGame);

	void setServerIsNotAvailable(bool tempServerIsNotAvailable);
	//void setChatAutoScroll(bool tempChatAutoScroll);
	void setGameLanguage(char tempGameLanguage);
	void setSymbol(char tempSymbol);
	void setInput(char tempInput);
	void restartServerClock();
};

void setColor(GameVariable* gv); // function for setting values for color.

void setFont(GameVariable* gv); // function for setting values for fonts.

void setText(GameVariable* gv); // function for setting values for text.

void setImage(GameVariable* gv); // function for setting values for images.

void setTexture(GameVariable* gv); // function for setting value for textures.

void setSprite(GameVariable* gv); // function to set value for sprites.

void setVariables(GameVariable* gv, Chat& chat); // function for setting the values of global variables.

void resetVariables(GameVariable* gv, Chat& chat); // global variable reset function.

void clearEntitiesVec(GameVariable* gv);