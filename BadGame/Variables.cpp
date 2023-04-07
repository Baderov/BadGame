#include "pch.h"

void setColor(GameVariable* gv) // function for setting values for color.
{
	gv->backgroundColor.r = 204;
	gv->backgroundColor.g = 153;
	gv->backgroundColor.b = 255;

	gv->greyColor.r = 120;
	gv->greyColor.g = 120;
	gv->greyColor.b = 120;
}

void setFont(GameVariable* gv) // function for setting values for fonts.
{
	gv->consolasFont.loadFromFile("consolas.ttf");
}

void setText(GameVariable* gv) // function for setting values for text.
{
	gv->gameInfoText.setFont(gv->consolasFont);
	gv->gameInfoText.setFillColor(sf::Color::Black);

	gv->playerInfoText.setFont(gv->consolasFont);
	gv->playerInfoText.setCharacterSize(60);
	gv->playerInfoText.setFillColor(sf::Color::Cyan);
	gv->playerInfoText.setOutlineThickness(2.f);

	gv->playerAmmoText.setFont(gv->consolasFont);
	gv->playerAmmoText.setCharacterSize(50);
	gv->playerAmmoText.setFillColor(sf::Color::Red);
	gv->playerAmmoText.setOutlineThickness(2.f);

}

void setImage(GameVariable* gv) // function for setting values for images.
{
	gv->boxImage.loadFromFile("Images/box.png");
	gv->playerImage.loadFromFile("Images/player.png");
	gv->enemyImage.loadFromFile("Images/enemy.png");
	gv->bulletImage.loadFromFile("Images/bullet.png");
	gv->bulletImage.createMaskFromColor(sf::Color(0, 0, 0));
	gv->goldCoinImage.loadFromFile("Images/goldCoin.png");
	gv->goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png");
	gv->hpBonusImage.loadFromFile("Images/hpBonus.png");
}

void setTexture(GameVariable* gv) // function for setting value for textures.
{
	gv->goldCoinHUDTexture.loadFromImage(gv->goldCoinHUDImage);
}

void setSprite(GameVariable* gv) // function to set value for sprites.
{
	gv->playerDestination.setRadius(20.f);
	gv->playerDestination.setOrigin(gv->playerDestination.getRadius(), gv->playerDestination.getRadius());
	gv->playerDestination.setFillColor(sf::Color::Transparent);
	gv->playerDestination.setOutlineThickness(5.f);
	gv->playerDestination.setOutlineColor(gv->backgroundColor);

	gv->goldCoinHUDSprite.setTexture(gv->goldCoinHUDTexture);

	gv->aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	gv->aimLaser.setFillColor(sf::Color::Red);
}

void setVariables(GameVariable* gv, Chat& chat) // function for setting the values of global variables.
{
	gv->setWindowSize(sf::Vector2u(1366, 768));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Fullscreen, settings);
	gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "BadGame", sf::Style::Close, settings);
	gv->window.setVerticalSyncEnabled(true);
	gv->gui.setWindow(gv->window);

	tgui::Font consolasFontTGUI;
	consolasFontTGUI.setGlobalFont("consolas.ttf");
	gv->gui.setFont(consolasFontTGUI);

	gv->sock.setBlocking(false);

	srand(static_cast<unsigned int>(time(NULL)));

	setColor(gv);
	setFont(gv);
	setText(gv);
	setImage(gv);
	setTexture(gv);
	setSprite(gv);

	gv->setMenuViewSize(sf::Vector2f(static_cast<float>(gv->window.getSize().x), static_cast<float>(gv->window.getSize().y)));
	gv->setMenuViewCenter(sf::Vector2f(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f));

	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(960.f, 540.f));

	gv->setPlayerStartPos(sf::Vector2f(1500.f, 1500.f));

	gv->boxStartPositions[0] = sf::Vector2f(1250.f, 1000.f);
	gv->boxStartPositions[1] = sf::Vector2f(1750.f, 1000.f);
	gv->boxStartPositions[2] = sf::Vector2f(2250.f, 1000.f);
	gv->boxStartPositions[3] = sf::Vector2f(2750.f, 1000.f);
	gv->boxStartPositions[4] = sf::Vector2f(3250.f, 1000.f);
	gv->boxStartPositions[5] = sf::Vector2f(3750.f, 1000.f);

	gv->boxStartPositions[6] = sf::Vector2f(1250.f, 2000.f);
	gv->boxStartPositions[7] = sf::Vector2f(1750.f, 2000.f);
	gv->boxStartPositions[8] = sf::Vector2f(2250.f, 2000.f);
	gv->boxStartPositions[9] = sf::Vector2f(2750.f, 2000.f);
	gv->boxStartPositions[10] = sf::Vector2f(3250.f, 2000.f);
	gv->boxStartPositions[11] = sf::Vector2f(3750.f, 2000.f);

	gv->boxStartPositions[12] = sf::Vector2f(1250.f, 3000.f);
	gv->boxStartPositions[13] = sf::Vector2f(1750.f, 3000.f);
	gv->boxStartPositions[14] = sf::Vector2f(2250.f, 3000.f);
	gv->boxStartPositions[15] = sf::Vector2f(2750.f, 3000.f);
	gv->boxStartPositions[16] = sf::Vector2f(3250.f, 3000.f);
	gv->boxStartPositions[17] = sf::Vector2f(3750.f, 3000.f);

	gv->boxStartPositions[18] = sf::Vector2f(1250.f, 4000.f);
	gv->boxStartPositions[19] = sf::Vector2f(1750.f, 4000.f);
	gv->boxStartPositions[20] = sf::Vector2f(2250.f, 4000.f);
	gv->boxStartPositions[21] = sf::Vector2f(2750.f, 4000.f);
	gv->boxStartPositions[22] = sf::Vector2f(3250.f, 4000.f);
	gv->boxStartPositions[23] = sf::Vector2f(3750.f, 4000.f);

	// FLOAT.
	gv->setMenuTimer(0.f);
	gv->setDT(0.f);

	// STRING.
	chat.setSenderNickname(L"");
	gv->setNickname(L"");
	chat.setChatStr(L"");
	chat.setUserStr(L"");
	chat.setChatPrefix(L"");
	gv->setServerIP("");
	gv->setTempPort("");
	chat.setLeftNick(L"");
	chat.setJoinedNick(L"");
	chat.setJoinedMsg(L"");
	chat.setLeftMsg(L"");
	gv->setFuncName("");

	// INT, SIZE_T, sf::INT8,sf::INT16, sf::INT32, sf::INT64.
	gv->setFPSLimiter(75);
	gv->setMenuNum(0);
	chat.setNumOfLinesInChat(1);
	chat.setNumOfLinesInUserTextBox(1);
	gv->setPingDelay(100);

	// BOOL.
	gv->setInMenu(false);
	gv->setShowHitbox(false);
	gv->setShowAimLaser(false);
	gv->setShowLogs(false);
	gv->setShowMinimap(true);
	gv->setIsFullscreen(false);
	gv->setIsVsync(true);
	gv->setFocusEvent(true);
	gv->setIsMultiplayer(false);
	gv->setIsSingleplayer(false);
	gv->setRestartGame(false);
	gv->setMainMenu(true);
	chat.setChatEnterText(false);
	chat.setChatContainsMouse(false);
	chat.setRecvMsg(false);
	chat.setSendMsg(false);
	chat.setLeftFromServer(false);
	chat.setJoinToServer(false);
	gv->setConnectsToServer(false);
	//gv->setChatAutoScroll(true);

	// CHAR.
	gv->setGameLanguage('e');
	gv->setSymbol(' ');
	gv->setInput(' ');

}

void clearEntitiesVec(GameVariable* gv)
{
	std::lock_guard<std::mutex> lock(gv->entities_mtx);
	gv->entitiesVec.clear();
}

void resetVariables(GameVariable* gv, Chat& chat) // global variable reset function.
{
	if (gv->getIsSingleplayer() == true && gv->getIsMultiplayer() == false) { gv->setNickname(L""); }
	else if (gv->getIsMultiplayer() == true && gv->getIsSingleplayer() == false)
	{
		clearEntitiesVec(gv);
		chat.setUserStr(L"");
		chat.setChatStr(L"");
		chat.setChatPrefix(L"");
		chat.setJoinedMsg(L"");
		chat.setLeftMsg(L"");
		chat.setNumOfLinesInChat(1);
		chat.setNumOfLinesInUserTextBox(1);

		gv->setIsConnected(false);
		chat.setChatEnterText(false);
		chat.setChatContainsMouse(false);
		chat.setRecvMsg(false);
		chat.setSendMsg(false);
		chat.setLeftFromServer(false);
		chat.setJoinToServer(true);
		gv->setServerIsNotAvailable(false);
		gv->setInMenu(false);
		gv->setShowPlayersList(false);
		chat.setShowChat(true);
	}
	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(0.f, 0.f));
	gv->setWindowView(gv->getGameView());
	gv->setShowMinimap(true);
	gv->gameClock.restart();
}

// GETTERS.
sf::Vector2f GameVariable::getGameViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewCenter = gVars.gameView.getCenter();
	return tempViewCenter;
}

sf::Vector2f GameVariable::getGameViewSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewSize = gVars.gameView.getSize();
	return tempViewSize;
}

sf::Vector2f GameVariable::getMenuViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewCenter = gVars.menuView.getCenter();
	return tempViewCenter;
}

sf::Vector2f GameVariable::getMenuViewSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewSize = gVars.menuView.getSize();
	return tempViewSize;
}

sf::Vector2u GameVariable::getWindowSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2u tempWindowSize = gVars.windowSize;
	return tempWindowSize;
}

sf::View GameVariable::getGameView()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::View tempView = gVars.gameView;
	return tempView;
}

sf::View GameVariable::getMenuView()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::View tempView = gVars.menuView;
	return tempView;
}

sf::Vector2f GameVariable::getMousePos()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempMousePos = gVars.mousePos;
	return tempMousePos;
}

sf::Vector2f GameVariable::getPlayerStartPos()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempPlayerStartPos = gVars.playerStartPos;
	return tempPlayerStartPos;
}

std::wstring GameVariable::getMoveDir()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::wstring tempMoveDir = gVars.moveDir;
	return tempMoveDir;
}

std::wstring GameVariable::getNickname()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::wstring tempNickname = gVars.nickname;
	return tempNickname;
}

std::string GameVariable::getFuncName()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string tempFuncName = gVars.funcName;
	return tempFuncName;
}

std::string GameVariable::getServerIP()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string tempServerIP = gVars.serverIP;
	return tempServerIP;
}

std::string GameVariable::getTempPort()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string temporaryPort = gVars.tempPort;
	return temporaryPort;
}

float GameVariable::getFPS()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float tempFPS = gVars.fps;
	return tempFPS;
}

float GameVariable::getMenuTimer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float tempMenuTimer = gVars.menuTimer;
	return tempMenuTimer;
}

float GameVariable::getDT()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float tempDT = gVars.dt;
	return tempDT;
}

float GameVariable::getServerTime()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float tempServerTime = gVars.serverTime;
	return tempServerTime;
}

float GameVariable::getServerClockElapsedTime()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float serverClockElapsedTime = serverClock.getElapsedTime().asSeconds();
	return serverClockElapsedTime;
}

unsigned int GameVariable::getFPSLimiter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	unsigned int tempFPSLimiter = gVars.fpsLimiter;
	return tempFPSLimiter;
}

int GameVariable::getMenuNum()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	int tempMenuNum = gVars.menuNum;
	return tempMenuNum;
}

unsigned short GameVariable::getServerPort()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	unsigned short tempServerPort = gVars.serverPort;
	return tempServerPort;
}

sf::Int32 GameVariable::getPingDelay()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Int32 tempPingDelay = gVars.pingDelay;
	return tempPingDelay;
}

bool GameVariable::getIsConnected()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsConnected = gVars.isConnected;
	return tempIsConnected;
}

bool GameVariable::getConnectButtonPressed()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempConnectButtonPressed = gVars.connectButtonPressed;
	return tempConnectButtonPressed;
}

bool GameVariable::getShowPlayersList()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowPlayersList = gVars.showPlayersList;
	return tempShowPlayersList;
}

bool GameVariable::getInMenu()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempInMenu = gVars.inMenu;
	return tempInMenu;
}

bool GameVariable::getConnectsToServer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempConnectsToServer = gVars.connectsToServer;
	return tempConnectsToServer;
}

bool GameVariable::getShowHitbox()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowHitbox = gVars.showHitbox;
	return tempShowHitbox;
}

bool GameVariable::getShowAimLaser()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowAimLaser = gVars.showAimLaser;
	return tempShowAimLaser;
}

bool GameVariable::getShowLogs()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowLogs = gVars.showLogs;
	return tempShowLogs;
}

bool GameVariable::getShowMinimap()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowMinimap = gVars.showMinimap;
	return tempShowMinimap;
}

bool GameVariable::getIsFullscreen()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsFullscreen = gVars.isFullscreen;
	return tempIsFullscreen;
}

bool GameVariable::getIsVsync()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsVsync = gVars.isVsync;
	return tempIsVsync;
}

bool GameVariable::getIsMultiplayer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsMultiplayer = gVars.isMultiplayer;
	return tempIsMultiplayer;
}

bool GameVariable::getIsSingleplayer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsSinglePlayer = gVars.isSingleplayer;
	return tempIsSinglePlayer;
}

bool GameVariable::getFocusEvent()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempFocusEvent = gVars.focusEvent;
	return tempFocusEvent;
}

bool GameVariable::getMainMenu()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempMainMenu = gVars.mainMenu;
	return tempMainMenu;
}

bool GameVariable::getRestartGame()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempRestartGame = gVars.restartGame;
	return tempRestartGame;
}



//bool GameVariable::getChatAutoScroll()
//{
//	
//	bool tempChatAutoScroll = gVars.chatAutoScroll;
//	
//	return tempChatAutoScroll;
//}

bool GameVariable::getServerIsNotAvailable()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempServerIsNotAvailable = gVars.serverIsNotAvailable;
	return tempServerIsNotAvailable;
}

char GameVariable::getGameLanguage()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	char tempGameLanguage = gVars.gameLanguage;
	return tempGameLanguage;
}

char GameVariable::getSymbol()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	char tempSymbol = gVars.symbol;
	return tempSymbol;
}

char GameVariable::getInput()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	char tempInput = gVars.input;
	return tempInput;
}

// SETTERS.
void GameVariable::setWindowView(sf::View view)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	window.setView(view);
}

void GameVariable::setGameViewCenter(sf::Vector2f tempViewCenter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.gameView.setCenter(tempViewCenter);
}

void GameVariable::setGameViewSize(sf::Vector2f tempViewSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.gameView.setSize(tempViewSize);
}

void GameVariable::setMenuViewCenter(sf::Vector2f tempViewCenter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.menuView.setCenter(tempViewCenter);
}

void GameVariable::setMenuViewSize(sf::Vector2f tempViewSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.menuView.setSize(tempViewSize);
}

void GameVariable::setMousePos(sf::Vector2f tempMousePos)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.mousePos = tempMousePos;
}

void GameVariable::setPlayerStartPos(sf::Vector2f tempPlayerStartPos)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.playerStartPos = tempPlayerStartPos;
}

void GameVariable::setWindowSize(sf::Vector2u tempWindowSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.windowSize = tempWindowSize;
}

void GameVariable::setMoveDir(std::wstring tempMoveDir)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.moveDir = tempMoveDir;
}

void GameVariable::setNickname(std::wstring tempNickname)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.nickname = tempNickname;
}

void GameVariable::setFuncName(std::string tempFuncName)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.funcName = tempFuncName;
}

void GameVariable::setServerIP(std::string tempServerIP)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.serverIP = tempServerIP;
}

void GameVariable::setTempPort(std::string temporaryPort)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.tempPort = temporaryPort;
}

void GameVariable::setFPS(float tempFPS)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.fps = tempFPS;
}

void GameVariable::setMenuTimer(float tempMenuTimer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.menuTimer = tempMenuTimer;
}

void GameVariable::setDT(float tempDT)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.dt = tempDT;
}

void GameVariable::setServerTime(float tempServerTime)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.serverTime = tempServerTime;
}

void GameVariable::setFPSLimiter(unsigned int tempFPSLimiter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.fpsLimiter = tempFPSLimiter;
}

void GameVariable::setMenuNum(int tempMenuNum)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.menuNum = tempMenuNum;
}

void GameVariable::setServerPort(unsigned short tempServerPort)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.serverPort = tempServerPort;
}

void GameVariable::setPingDelay(sf::Int32 tempPingDelay)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.pingDelay = tempPingDelay;
}

void GameVariable::setIsConnected(bool tempIsConnected)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.isConnected = tempIsConnected;
}

void GameVariable::setConnectButtonPressed(bool tempConnectButtonPressed)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.connectButtonPressed = tempConnectButtonPressed;
}

void GameVariable::setShowPlayersList(bool tempShowPlayersList)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.showPlayersList = tempShowPlayersList;
}

void GameVariable::setInMenu(bool tempInMenu)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.inMenu = tempInMenu;
}

void GameVariable::setConnectsToServer(bool tempConnectsToServer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.connectsToServer = tempConnectsToServer;
}

void GameVariable::setShowHitbox(bool tempShowHitbox)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.showHitbox = tempShowHitbox;
}

void GameVariable::setShowAimLaser(bool tempShowAimLaser)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.showAimLaser = tempShowAimLaser;
}

void GameVariable::setShowLogs(bool tempShowLogs)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.showLogs = tempShowLogs;
}

void GameVariable::setShowMinimap(bool tempShowMinimap)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.showMinimap = tempShowMinimap;
}

void GameVariable::setIsFullscreen(bool tempIsFullscreen)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.isFullscreen = tempIsFullscreen;
}

void GameVariable::setIsVsync(bool tempIsVsync)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.isVsync = tempIsVsync;
}

void GameVariable::setIsMultiplayer(bool tempIsMultiplayer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.isMultiplayer = tempIsMultiplayer;
}

void GameVariable::setIsSingleplayer(bool tempIsSingleplayer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.isSingleplayer = tempIsSingleplayer;
}

void GameVariable::setFocusEvent(bool tempFocusEvent)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.focusEvent = tempFocusEvent;
}

void GameVariable::setMainMenu(bool tempMainMenu)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.mainMenu = tempMainMenu;
}

void GameVariable::setRestartGame(bool tempRestartGame)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.restartGame = tempRestartGame;
}



//void GameVariable::setChatAutoScroll(bool tempChatAutoScroll)
//{
//	
//	gVars.chatAutoScroll = tempChatAutoScroll;
//	
//}

void GameVariable::setServerIsNotAvailable(bool tempServerIsNotAvailable)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.serverIsNotAvailable = tempServerIsNotAvailable;
}

void GameVariable::setGameLanguage(char tempGameLanguage)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.gameLanguage = tempGameLanguage;
}

void GameVariable::setSymbol(char tempSymbol)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.symbol = tempSymbol;
}

void GameVariable::setInput(char tempInput)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gVars.input = tempInput;
}

void GameVariable::restartServerClock()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	serverClock.restart();
}