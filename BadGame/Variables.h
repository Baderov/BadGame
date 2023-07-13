#ifndef VARIABLES_H
#define VARIABLES_H

class Chat;
class PlayersList;

class GameVariable
{
private:
	sf::Vector2f mousePos;
	sf::Vector2f playerStartPos;
	sf::Vector2u windowSize;
	sf::View gameView;
	sf::View menuView;
	std::wstring nickname;
	std::string funcName;
	std::string serverIP;
	std::string tempPort;
	float dt;
	int menuNum;
	unsigned short serverPort;
	unsigned int fpsLimiter;
	bool showHitbox;
	bool showAimLaser;
	bool showLogs;
	bool showMinimap;
	bool isConnected;
	bool isFullscreen;
	bool isVsync;
	bool isMultiplayer;
	bool isSingleplayer;
	bool inMenu;
	bool focusEvent;
	bool restartGame;
	bool connectsToServer;
	bool serverIsNotAvailable;
	bool connectButtonPressed;
	//	bool chatAutoScroll;
	char gameLanguage;
	std::mutex mtx_gv;
public:
	sf::UdpSocket sock;
	sf::RenderWindow window;
	sf::Image wallImage;
	sf::Image boxImage;
	sf::Image goldCoinImage;
	sf::Image goldCoinHUDImage;
	sf::Image enemyImage;
	sf::Image playerImage;
	sf::Image hpBonusImage;
	sf::Image bulletImage;
	tgui::Gui gui;
	sf::Vector2f boxStartPositions[24];
	sf::Text connectionErrorText;
	sf::Text OKButtonText;
	sf::Event event;
	sf::RectangleShape aimLaser;
	sf::RectangleShape connectionErrorRS;
	sf::RectangleShape OKButtonRS;
	sf::CircleShape playerDestination;
	sf::Font consolasFont;
	sf::Color backgroundColor;
	sf::Color greyColor;
	sf::Clock menuClock;
	sf::Clock gameClock;
	sf::Clock serverClock;
	// GETTERS.
	sf::Vector2f getGameViewCenter();
	sf::Vector2f getGameViewSize();
	sf::Vector2f getMenuViewCenter();
	sf::Vector2f getMenuViewSize();
	sf::Vector2f getMousePos();
	sf::Vector2f getPlayerStartPos();
	sf::Vector2u getWindowSize();
	std::wstring getNickname();
	std::string getFuncName();
	std::string getServerIP();
	std::string getTempPort();
	float getDT();
	unsigned short getServerPort();
	unsigned int getFPSLimiter();
	int getMenuNum();
	bool getInMenu();
	bool getConnectButtonPressed();
	bool getConnectsToServer();
	bool getShowHitbox();
	bool getShowAimLaser();
	bool getShowLogs();
	bool getShowMinimap();
	bool getIsConnected();
	bool getIsVsync();
	bool getIsFullscreen();
	bool getIsMultiplayer();
	bool getIsSingleplayer();
	bool getFocusEvent();
	bool getRestartGame();
	bool getServerIsNotAvailable();
	//bool getChatAutoScroll();
	char getGameLanguage();

	// SETTERS.
	void setMenuView();
	void setGameView();
	void setGameViewCenter(sf::Vector2f tempViewCenter);
	void setGameViewSize(sf::Vector2f tempViewSize);
	void setMenuViewCenter(sf::Vector2f tempViewCenter);
	void setMenuViewSize(sf::Vector2f tempViewSize);
	void setMousePos(sf::Vector2f tempMousePos);
	void setPlayerStartPos(sf::Vector2f tempPlayerStartPos);
	void setWindowSize(sf::Vector2u tempWindowSize);
	void setNickname(std::wstring tempNickname);
	void setFuncName(std::string tempFuncName);
	void setServerIP(std::string tempServerIP);
	void setTempPort(std::string temporaryPort);
	void setDT();
	void setFPSLimiter(unsigned int tempFPSLimiter);
	void setMenuNum(int tempMenuNum);
	void setServerPort(unsigned short tempServerPort);
	void setInMenu(bool tempInMenu);
	void setConnectButtonPressed(bool tempConnectButtonPressed);
	void setConnectsToServer(bool tempConnectsToServer);
	void setShowHitbox(bool tempShowHitbox);
	void setShowAimLaser(bool tempShowAimLaser);
	void setShowLogs(bool tempShowLogs);
	void setShowMinimap(bool tempShowMinimap);
	void setIsConnected(bool tempIsConnected);
	void setIsFullscreen(bool tempIsFullscreen);
	void setIsVsync(bool tempIsVsync);
	void setIsMultiplayer(bool tempIsMultiplayer);
	void setIsSingleplayer(bool tempIsSingleplayer);
	void setFocusEvent(bool tempFocusEvent);
	void setRestartGame(bool tempRestartGame);
	void setServerIsNotAvailable(bool tempServerIsNotAvailable);
	//void setChatAutoScroll(bool tempChatAutoScroll);
	void setGameLanguage(char tempGameLanguage);
};

void setImage(std::unique_ptr<GameVariable>& gv); // function for setting values for images.

void setColor(std::unique_ptr<GameVariable>& gv); // function for setting values for color.

void setSprite(std::unique_ptr<GameVariable>& gv); // function to set value for sprites.

void setVariables(std::unique_ptr<GameVariable>& gv); // function for setting the values of global variables.

void resetVariables(std::unique_ptr<GameVariable>& gv, Chat& chat, PlayersList& playersList); // reset function for variables.

#endif