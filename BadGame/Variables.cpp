#include "pch.h"
#include "Network.h"
#include "Variables.h"

void setImage(std::unique_ptr<GameVariable>& gv) // function for setting values for images.
{
	gv->boxImage.loadFromFile("Images/box.png");
	gv->playerImage.loadFromFile("Images/player.png");
	gv->enemyImage.loadFromFile("Images/enemy.png");
	gv->bulletImage.loadFromFile("Images/bullet.png");
	gv->bulletImage.createMaskFromColor(sf::Color(0, 0, 0));
	gv->goldCoinImage.loadFromFile("Images/goldCoin.png");
	gv->goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png");
	gv->hpBonusImage.loadFromFile("Images/hpBonus.png");
	gv->wallImage.loadFromFile("Images/wall.png");
}

void setColor(std::unique_ptr<GameVariable>& gv) // function for setting values for color.
{
	gv->backgroundColor.r = 204;
	gv->backgroundColor.g = 153;
	gv->backgroundColor.b = 255;

	gv->greyColor.r = 120;
	gv->greyColor.g = 120;
	gv->greyColor.b = 120;
}

void setSprite(std::unique_ptr<GameVariable>& gv) // function to set value for sprites.
{
	gv->playerDestination.setRadius(20.f);
	gv->playerDestination.setOrigin(gv->playerDestination.getRadius(), gv->playerDestination.getRadius());
	gv->playerDestination.setFillColor(sf::Color::Transparent);
	gv->playerDestination.setOutlineThickness(5.f);
	gv->playerDestination.setOutlineColor(gv->backgroundColor);

	gv->aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	gv->aimLaser.setFillColor(sf::Color::Red);
}

void setVariables(std::unique_ptr<GameVariable>& gv) // function for setting the values of global variables.
{
	gv->setWindowSize(sf::Vector2u(1366, 768));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Fullscreen, settings);
	gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "BadGame", sf::Style::Close, settings);
	gv->window.setVerticalSyncEnabled(true);
	gv->gui.setWindow(gv->window);

	gv->sock.setBlocking(false);

	tgui::Font consolasFontTGUI;
	consolasFontTGUI.setGlobalFont("consolas.ttf");
	gv->gui.setFont(consolasFontTGUI);

	gv->consolasFont.loadFromFile("consolas.ttf");

	srand(static_cast<unsigned int>(time(NULL)));

	setColor(gv);
	setImage(gv);
	setTextsAndSprites(gv);
	setSprite(gv);

	gv->setMenuViewSize(sf::Vector2f(static_cast<float>(gv->window.getSize().x), static_cast<float>(gv->window.getSize().y)));
	gv->setMenuViewCenter(sf::Vector2f(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f));

	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(960.f, 540.f));

	gv->setPlayerStartPos(sf::Vector2f(2500.f, 2500.f));

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

	gv->setGameLanguage('e');

	gv->setNickname(L"");
	gv->setServerIP("");
	gv->setTempPort("");
	gv->setFuncName("");

	gv->setFPSLimiter(75);
	gv->setMenuNum(0);

	gv->setDT();

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
	gv->setConnectsToServer(false);
	gv->setIsConnected(false);
	gv->setServerIsNotAvailable(false);
	//gv->setChatAutoScroll(true);
}

void resetVariables(std::unique_ptr<GameVariable>& gv, Chat& chat, PlayersList& playersList) // reset function for variables.
{
	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { gv->setNickname(L""); }
	else if (gv->getIsMultiplayer() && !gv->getIsSingleplayer())
	{
		gv->setIsConnected(false);
		gv->setInMenu(false);
		chat.init();
		playersList.init();
	}

	gv->setMenuNum(0);
	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(0.f, 0.f));
	gv->setGameView();
	gv->setShowMinimap(true);
	gv->setServerIsNotAvailable(false);
	gv->gameClock.restart();
	gv->serverClock.restart();
}

// GETTERS.
sf::Vector2f GameVariable::getGameViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewCenter = gameView.getCenter();
	return tempViewCenter;
}

sf::Vector2f GameVariable::getGameViewSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewSize = gameView.getSize();
	return tempViewSize;
}

sf::Vector2f GameVariable::getMenuViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewCenter = menuView.getCenter();
	return tempViewCenter;
}

sf::Vector2f GameVariable::getMenuViewSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempViewSize = menuView.getSize();
	return tempViewSize;
}

sf::Vector2u GameVariable::getWindowSize()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2u tempWindowSize = windowSize;
	return tempWindowSize;
}

sf::Vector2f GameVariable::getMousePos()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempMousePos = mousePos;
	return tempMousePos;
}

sf::Vector2f GameVariable::getPlayerStartPos()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	sf::Vector2f tempPlayerStartPos = playerStartPos;
	return tempPlayerStartPos;
}

std::wstring GameVariable::getNickname()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::wstring tempNickname = nickname;
	return tempNickname;
}

std::string GameVariable::getFuncName()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string tempFuncName = funcName;
	return tempFuncName;
}

std::string GameVariable::getServerIP()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string tempServerIP = serverIP;
	return tempServerIP;
}

std::string GameVariable::getTempPort()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	std::string temporaryPort = tempPort;
	return temporaryPort;
}

float GameVariable::getDT()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	float tempDT = dt;
	return tempDT;
}

unsigned int GameVariable::getFPSLimiter()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	unsigned int tempFPSLimiter = fpsLimiter;
	return tempFPSLimiter;
}

int GameVariable::getMenuNum()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	int tempMenuNum = menuNum;
	return tempMenuNum;
}

unsigned short GameVariable::getServerPort()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	unsigned short tempServerPort = serverPort;
	return tempServerPort;
}

bool GameVariable::getInMenu()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempInMenu = inMenu;
	return tempInMenu;
}

bool GameVariable::getIsConnected()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsConnected = isConnected;
	return tempIsConnected;
}

bool GameVariable::getConnectButtonPressed()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempConnectButtonPressed = connectButtonPressed;
	return tempConnectButtonPressed;
}

bool GameVariable::getConnectsToServer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempConnectsToServer = connectsToServer;
	return tempConnectsToServer;
}

bool GameVariable::getShowHitbox()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowHitbox = showHitbox;
	return tempShowHitbox;
}

bool GameVariable::getShowAimLaser()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowAimLaser = showAimLaser;
	return tempShowAimLaser;
}

bool GameVariable::getShowLogs()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowLogs = showLogs;
	return tempShowLogs;
}

bool GameVariable::getShowMinimap()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempShowMinimap = showMinimap;
	return tempShowMinimap;
}

bool GameVariable::getIsFullscreen()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsFullscreen = isFullscreen;
	return tempIsFullscreen;
}

bool GameVariable::getIsVsync()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsVsync = isVsync;
	return tempIsVsync;
}

bool GameVariable::getIsMultiplayer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsMultiplayer = isMultiplayer;
	return tempIsMultiplayer;
}

bool GameVariable::getIsSingleplayer()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempIsSinglePlayer = isSingleplayer;
	return tempIsSinglePlayer;
}

bool GameVariable::getFocusEvent()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempFocusEvent = focusEvent;
	return tempFocusEvent;
}

bool GameVariable::getRestartGame()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempRestartGame = restartGame;
	return tempRestartGame;
}

//bool GameVariable::getChatAutoScroll()
//{
// 	std::lock_guard<std::mutex> lock(mtx_gv);
//	bool tempChatAutoScroll = chatAutoScroll;
//	return tempChatAutoScroll;
//}

bool GameVariable::getServerIsNotAvailable()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	bool tempServerIsNotAvailable = serverIsNotAvailable;
	return tempServerIsNotAvailable;
}

char GameVariable::getGameLanguage()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	char tempGameLanguage = gameLanguage;
	return tempGameLanguage;
}

// SETTERS.
void GameVariable::setMenuView()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	window.setView(menuView);
}

void GameVariable::setGameView()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	window.setView(gameView);
}

void GameVariable::setGameViewCenter(sf::Vector2f tempViewCenter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gameView.setCenter(std::move(tempViewCenter));
}

void GameVariable::setGameViewSize(sf::Vector2f tempViewSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gameView.setSize(std::move(tempViewSize));
}

void GameVariable::setMenuViewCenter(sf::Vector2f tempViewCenter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	menuView.setCenter(std::move(tempViewCenter));
}

void GameVariable::setMenuViewSize(sf::Vector2f tempViewSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	menuView.setSize(std::move(tempViewSize));
}

void GameVariable::setMousePos(sf::Vector2f tempMousePos)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	mousePos = std::move(tempMousePos);
}

void GameVariable::setPlayerStartPos(sf::Vector2f tempPlayerStartPos)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	playerStartPos = std::move(tempPlayerStartPos);
}

void GameVariable::setWindowSize(sf::Vector2u tempWindowSize)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	windowSize = std::move(tempWindowSize);
}

void GameVariable::setNickname(std::wstring tempNickname)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	nickname = std::move(tempNickname);
}

void GameVariable::setFuncName(std::string tempFuncName)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	funcName = std::move(tempFuncName);
}

void GameVariable::setServerIP(std::string tempServerIP)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	serverIP = std::move(tempServerIP);
}

void GameVariable::setTempPort(std::string temporaryPort)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	tempPort = std::move(temporaryPort);
}

void GameVariable::setDT()
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	dt = gameClock.restart().asSeconds();
}

void GameVariable::setFPSLimiter(unsigned int tempFPSLimiter)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	fpsLimiter = std::move(tempFPSLimiter);
}

void GameVariable::setMenuNum(int tempMenuNum)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	menuNum = std::move(tempMenuNum);
}

void GameVariable::setServerPort(unsigned short tempServerPort)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	serverPort = std::move(tempServerPort);
}

void GameVariable::setInMenu(bool tempInMenu)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	inMenu = std::move(tempInMenu);
}

void GameVariable::setIsConnected(bool tempIsConnected)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	isConnected = std::move(tempIsConnected);
}

void GameVariable::setConnectButtonPressed(bool tempConnectButtonPressed)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	connectButtonPressed = std::move(tempConnectButtonPressed);
}

void GameVariable::setConnectsToServer(bool tempConnectsToServer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	connectsToServer = std::move(tempConnectsToServer);
}

void GameVariable::setShowHitbox(bool tempShowHitbox)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	showHitbox = std::move(tempShowHitbox);
}

void GameVariable::setShowAimLaser(bool tempShowAimLaser)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	showAimLaser = std::move(tempShowAimLaser);
}

void GameVariable::setShowLogs(bool tempShowLogs)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	showLogs = std::move(tempShowLogs);
}

void GameVariable::setShowMinimap(bool tempShowMinimap)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	showMinimap = std::move(tempShowMinimap);
}

void GameVariable::setIsFullscreen(bool tempIsFullscreen)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	isFullscreen = std::move(tempIsFullscreen);
}

void GameVariable::setIsVsync(bool tempIsVsync)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	isVsync = std::move(tempIsVsync);
}

void GameVariable::setIsMultiplayer(bool tempIsMultiplayer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	isMultiplayer = std::move(tempIsMultiplayer);
}

void GameVariable::setIsSingleplayer(bool tempIsSingleplayer)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	isSingleplayer = std::move(tempIsSingleplayer);
}

void GameVariable::setFocusEvent(bool tempFocusEvent)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	focusEvent = std::move(tempFocusEvent);
}

void GameVariable::setRestartGame(bool tempRestartGame)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	restartGame = std::move(tempRestartGame);
}

//void GameVariable::setChatAutoScroll(bool tempChatAutoScroll)
//{
//  std::lock_guard<std::mutex> lock(mtx_gv);
//	chatAutoScroll = std::move(tempChatAutoScroll);
//}

void GameVariable::setServerIsNotAvailable(bool tempServerIsNotAvailable)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	serverIsNotAvailable = std::move(tempServerIsNotAvailable);
}

void GameVariable::setGameLanguage(char tempGameLanguage)
{
	std::lock_guard<std::mutex> lock(mtx_gv);
	gameLanguage = std::move(tempGameLanguage);
}