#include "Variables.h" // header file for global variables.

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
	gv->wallImage.loadFromFile("Images/wall.png");
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

void setVariables(GameVariable* gv) // function for setting the values of global variables.
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	gv->window.create(sf::VideoMode(1366, 768), "BadGame", sf::Style::Close, settings);
	//gv->window.create(sf::VideoMode(1920, 1080), "BadGame", sf::Style::Fullscreen, settings);
	//gv->window.create(sf::VideoMode::getDesktopMode(), "BadGame", sf::Style::Fullscreen, settings));
	gv->window.setVerticalSyncEnabled(true);

	srand(static_cast<unsigned int>(time(NULL)));

	setColor(gv);
	setFont(gv);
	setText(gv);
	setImage(gv);
	setTexture(gv);
	setSprite(gv);

	gv->setPlayerStartPos(sf::Vector2f(1500.f, 1500.f));

	gv->boxStartPositions[0] = sf::Vector2f(250.f, 1100.f);
	gv->boxStartPositions[1] = sf::Vector2f(750.f, 1100.f);
	gv->boxStartPositions[2] = sf::Vector2f(1250.f, 1100.f);
	gv->boxStartPositions[3] = sf::Vector2f(1750.f, 1100.f);
	gv->boxStartPositions[4] = sf::Vector2f(2250.f, 1100.f);
	gv->boxStartPositions[5] = sf::Vector2f(2750.f, 1100.f);

	gv->boxStartPositions[6] = sf::Vector2f(250.f, 1900.f);
	gv->boxStartPositions[7] = sf::Vector2f(750.f, 1900.f);
	gv->boxStartPositions[8] = sf::Vector2f(1250.f, 1900.f);
	gv->boxStartPositions[9] = sf::Vector2f(1750.f, 1900.f);
	gv->boxStartPositions[10] = sf::Vector2f(2250.f, 1900.f);
	gv->boxStartPositions[11] = sf::Vector2f(2750.f, 1900.f);

	// FLOAT.
	gv->setAimLaserLength(100.f);
	gv->setMenuTimer(0.f);
	gv->setDT(0.f);

	// STRING.
	gv->setSenderNickname(L"");
	gv->setNickname(L"");
	gv->setChatStr(L"");
	gv->setUserStr(L"");
	gv->setChatPrefix(L"");
	gv->setServerIP("");
	gv->setTempPort("");
	gv->setLeftNick(L"");
	gv->setJoinedNick(L"");
	gv->setJoinedMsg(L"");
	gv->setLeftMsg(L"");
	gv->setFuncName("");

	// INT, SIZE_T, sf::INT8,sf::INT16, sf::INT32, sf::INT64.
	gv->setNumberOfEnemies(0);
	gv->setNumberOfPlayers(0);
	gv->setMenuNum(0);
	gv->setNumOfLinesInChat(1);
	gv->setNumOfLinesInUserTextBox(1);
	gv->setPingDelay(100);

	// BOOL.
	gv->setInMenu(false);
	gv->setShowHitbox(false);
	gv->setShowAimLaser(false);
	gv->setShowLogs(false);
	gv->setIsFullscreen(true);
	gv->setAllowButtons(true);
	gv->setFocusEvent(true);
	gv->setMultiPlayerGame(false);
	gv->setSinglePlayerGame(false);
	gv->setRestartGame(false);
	gv->setMainMenu(true);
	gv->setChatEnterText(false);
	gv->setChatContainsMouse(false);
	gv->setRecvMsg(false);
	gv->setSendMsg(false);
	gv->setLeftFromServer(false);
	gv->setJoinToServer(false);
	gv->setNetworkEnd(true);
	//gv->autoScroll = true;

	// CHAR.
	gv->setGameLanguage('e');
	gv->setSymbol(' ');
	gv->setInput(' ');

}

// GETTERS.
sf::Vector2f GameVariable::getViewCenter()
{
	mtx_gv.lock();
	sf::Vector2f tempViewCenter = gVars.view.getCenter();
	mtx_gv.unlock();
	return tempViewCenter;
}

sf::Vector2f GameVariable::getViewSize()
{
	mtx_gv.lock();
	sf::Vector2f tempViewSize = gVars.view.getSize();
	mtx_gv.unlock();
	return tempViewSize;
}

sf::View GameVariable::getView()
{
	mtx_gv.lock();
	sf::View tempView = gVars.view;
	mtx_gv.unlock();
	return tempView;
}

sf::Vector2f GameVariable::getMousePos()
{
	mtx_gv.lock();
	sf::Vector2f tempMousePos = gVars.mousePos;
	mtx_gv.unlock();
	return tempMousePos;
}

sf::Vector2f GameVariable::getPlayerStartPos()
{
	mtx_gv.lock();
	sf::Vector2f tempPlayerStartPos = gVars.playerStartPos;
	mtx_gv.unlock();
	return tempPlayerStartPos;
}

std::wstring GameVariable::getSenderNickname()
{
	mtx_gv.lock();
	std::wstring tempSenderNickname = gVars.senderNickname;
	mtx_gv.unlock();
	return tempSenderNickname;
}

std::wstring GameVariable::getMoveDir()
{
	mtx_gv.lock();
	std::wstring tempMoveDir = gVars.moveDir;
	mtx_gv.unlock();
	return tempMoveDir;
}

std::wstring GameVariable::getNickname()
{
	mtx_gv.lock();
	std::wstring tempNickname = gVars.nickname;
	mtx_gv.unlock();
	return tempNickname;
}

std::wstring GameVariable::getUserStr()
{
	mtx_gv.lock();
	std::wstring tempUserStr = gVars.userStr;
	mtx_gv.unlock();
	return tempUserStr;
}

std::wstring GameVariable::getChatStr()
{
	mtx_gv.lock();
	std::wstring tempChatStr = gVars.chatStr;
	mtx_gv.unlock();
	return tempChatStr;
}

std::wstring GameVariable::getChatPrefix()
{
	mtx_gv.lock();
	std::wstring tempChatPrefix = gVars.chatPrefix;
	mtx_gv.unlock();
	return tempChatPrefix;
}

std::wstring GameVariable::getLeftNick()
{
	mtx_gv.lock();
	std::wstring tempLeftNick = gVars.leftNick;
	mtx_gv.unlock();
	return tempLeftNick;
}

std::wstring GameVariable::getJoinedNick()
{
	mtx_gv.lock();
	std::wstring tempJoinedNick = gVars.joinedNick;
	mtx_gv.unlock();
	return tempJoinedNick;
}

std::wstring GameVariable::getLeftMsg()
{
	mtx_gv.lock();
	std::wstring tempLefMsg = gVars.leftMsg;
	mtx_gv.unlock();
	return tempLefMsg;
}

std::wstring GameVariable::getJoinedMsg()
{
	mtx_gv.lock();
	std::wstring tempJoinedMsg = gVars.joinedMsg;
	mtx_gv.unlock();
	return tempJoinedMsg;
}

std::string GameVariable::getFuncName()
{
	mtx_gv.lock();
	std::string tempFuncName = gVars.funcName;
	mtx_gv.unlock();
	return tempFuncName;
}

std::string GameVariable::getServerIP()
{
	mtx_gv.lock();
	std::string tempServerIP = gVars.serverIP;
	mtx_gv.unlock();
	return tempServerIP;
}

std::string GameVariable::getTempPort()
{
	mtx_gv.lock();
	std::string temporaryPort = gVars.tempPort;
	mtx_gv.unlock();
	return temporaryPort;
}

float GameVariable::getFPS()
{
	mtx_gv.lock();
	float tempFPS = gVars.fps;
	mtx_gv.unlock();
	return tempFPS;
}

float GameVariable::getAimLaserLength()
{
	mtx_gv.lock();
	float tempAimLaserLength = gVars.aimLaserLength;
	mtx_gv.unlock();
	return tempAimLaserLength;
}

float GameVariable::getMenuTimer()
{
	mtx_gv.lock();
	float tempMenuTimer = gVars.menuTimer;
	mtx_gv.unlock();
	return tempMenuTimer;
}

float GameVariable::getDT()
{
	mtx_gv.lock();
	float tempDT = gVars.dt;
	mtx_gv.unlock();
	return tempDT;
}

int GameVariable::getNumberOfEnemies()
{
	mtx_gv.lock();
	int tempNumberOfEnemies = gVars.numberOfEnemies;
	mtx_gv.unlock();
	return tempNumberOfEnemies;
}

int GameVariable::getNumberOfPlayers()
{
	mtx_gv.lock();
	int tempNumberOfPlayers = gVars.numberOfPlayers;
	mtx_gv.unlock();
	return tempNumberOfPlayers;
}

int GameVariable::getMenuNum()
{
	mtx_gv.lock();
	int tempMenuNum = gVars.menuNum;
	mtx_gv.unlock();
	return tempMenuNum;
}

unsigned short GameVariable::getServerPort()
{
	mtx_gv.lock();
	unsigned short tempServerPort = gVars.serverPort;
	mtx_gv.unlock();
	return tempServerPort;
}

int GameVariable::getNumOfLinesInChat()
{
	mtx_gv.lock();
	int tempNumOfLinesInChat = gVars.numOfLinesInChat;
	mtx_gv.unlock();
	return tempNumOfLinesInChat;
}

int GameVariable::getNumOfLinesInUserTextBox()
{
	mtx_gv.lock();
	int tempNumOfLinesInUserTextBox = gVars.numOfLinesInUserTextBox;
	mtx_gv.unlock();
	return tempNumOfLinesInUserTextBox;
}

sf::Int32 GameVariable::getPingDelay()
{
	mtx_gv.lock();
	sf::Int32 tempPingDelay = gVars.pingDelay;
	mtx_gv.unlock();
	return tempPingDelay;
}


bool GameVariable::getInMenu()
{
	mtx_gv.lock();
	bool tempInMenu = gVars.inMenu;
	mtx_gv.unlock();
	return tempInMenu;
}

bool GameVariable::getHideChat()
{
	mtx_gv.lock();
	bool tempHideChat = gVars.hideChat;
	mtx_gv.unlock();
	return tempHideChat;
}

bool GameVariable::getNetworkEnd()
{
	mtx_gv.lock();
	bool tempNetworkEnd = gVars.networkEnd;
	mtx_gv.unlock();
	return tempNetworkEnd;
}

bool GameVariable::getShowHitbox()
{
	mtx_gv.lock();
	bool tempShowHitbox = gVars.showHitbox;
	mtx_gv.unlock();
	return tempShowHitbox;
}

bool GameVariable::getShowAimLaser()
{
	mtx_gv.lock();
	bool tempShowAimLaser = gVars.showAimLaser;
	mtx_gv.unlock();
	return tempShowAimLaser;
}

bool GameVariable::getShowLogs()
{
	mtx_gv.lock();
	bool tempShowLogs = gVars.showLogs;
	mtx_gv.unlock();
	return tempShowLogs;
}

bool GameVariable::getIsFullscreen()
{
	mtx_gv.lock();
	bool tempIsFullscreen = gVars.isFullscreen;
	mtx_gv.unlock();
	return tempIsFullscreen;
}

bool GameVariable::getAllowButtons()
{
	mtx_gv.lock();
	bool tempAllowButtons = gVars.allowButtons;
	mtx_gv.unlock();
	return tempAllowButtons;
}

bool GameVariable::getMultiPlayerGame()
{
	mtx_gv.lock();
	bool tempMultiplayerGame = gVars.multiPlayerGame;
	mtx_gv.unlock();
	return tempMultiplayerGame;
}

bool GameVariable::getSinglePlayerGame()
{
	mtx_gv.lock();
	bool tempSinglePlayerGame = gVars.singlePlayerGame;
	mtx_gv.unlock();
	return tempSinglePlayerGame;
}

bool GameVariable::getFocusEvent()
{
	mtx_gv.lock();
	bool tempFocusEvent = gVars.focusEvent;
	mtx_gv.unlock();
	return tempFocusEvent;
}

bool GameVariable::getMainMenu()
{
	mtx_gv.lock();
	bool tempMainMenu = gVars.mainMenu;
	mtx_gv.unlock();
	return tempMainMenu;
}

bool GameVariable::getRestartGame()
{
	mtx_gv.lock();
	bool tempRestartGame = gVars.restartGame;
	mtx_gv.unlock();
	return tempRestartGame;
}

bool GameVariable::getChatContainsMouse()
{
	mtx_gv.lock();
	bool tempChatContainsMouse = gVars.chatContainsMouse;
	mtx_gv.unlock();
	return tempChatContainsMouse;
}

bool GameVariable::getChatEnterText()
{
	mtx_gv.lock();
	bool tempChatEnterText = gVars.chatEnterText;
	mtx_gv.unlock();
	return tempChatEnterText;
}

bool GameVariable::getRecvMsg()
{
	mtx_gv.lock();
	bool tempRecvMsg = gVars.recvMsg;
	mtx_gv.unlock();
	return tempRecvMsg;
}

bool GameVariable::getSendMsg()
{
	mtx_gv.lock();
	bool tempSendMsg = gVars.sendMsg;
	mtx_gv.unlock();
	return tempSendMsg;
}

bool GameVariable::getLeftFromServer()
{
	mtx_gv.lock();
	bool tempLeftFromServer = gVars.leftFromServer;
	mtx_gv.unlock();
	return tempLeftFromServer;
}

bool GameVariable::getJoinToServer()
{
	mtx_gv.lock();
	bool tempJoinToServer = gVars.joinToServer;
	mtx_gv.unlock();
	return tempJoinToServer;
}

char GameVariable::getGameLanguage()
{
	mtx_gv.lock();
	char tempGameLanguage = gVars.gameLanguage;
	mtx_gv.unlock();
	return tempGameLanguage;
}

char GameVariable::getSymbol()
{
	mtx_gv.lock();
	char tempSymbol = gVars.symbol;
	mtx_gv.unlock();
	return tempSymbol;
}

char GameVariable::getInput()
{
	mtx_gv.lock();
	char tempInput = gVars.input;
	mtx_gv.unlock();
	return tempInput;
}


// SETTERS.
void GameVariable::setViewCenter(sf::Vector2f tempViewCenter)
{
	mtx_gv.lock();
	gVars.view.setCenter(tempViewCenter);
	mtx_gv.unlock();
}

void GameVariable::setViewSize(sf::Vector2f tempViewSize)
{
	mtx_gv.lock();
	gVars.view.setSize(tempViewSize);
	mtx_gv.unlock();
}

void GameVariable::setMousePos(sf::Vector2f tempMousePos)
{
	mtx_gv.lock();
	gVars.mousePos = tempMousePos;
	mtx_gv.unlock();
}

void GameVariable::setPlayerStartPos(sf::Vector2f tempPlayerStartPos)
{
	mtx_gv.lock();
	gVars.playerStartPos = tempPlayerStartPos;
	mtx_gv.unlock();
}

void GameVariable::setSenderNickname(std::wstring tempSenderNickname)
{
	mtx_gv.lock();
	gVars.senderNickname = tempSenderNickname;
	mtx_gv.unlock();
}

void GameVariable::setMoveDir(std::wstring tempMoveDir)
{
	mtx_gv.lock();
	gVars.moveDir = tempMoveDir;
	mtx_gv.unlock();
}

void GameVariable::setNickname(std::wstring tempNickname)
{
	mtx_gv.lock();
	gVars.nickname = tempNickname;
	mtx_gv.unlock();
}

void GameVariable::setUserStr(std::wstring tempUserStr)
{
	mtx_gv.lock();
	gVars.userStr = tempUserStr;
	mtx_gv.unlock();
}

void GameVariable::setChatStr(std::wstring tempChatStr)
{
	mtx_gv.lock();
	gVars.chatStr = tempChatStr;
	mtx_gv.unlock();
}

void GameVariable::setChatPrefix(std::wstring tempChatPrefix)
{
	mtx_gv.lock();
	gVars.chatPrefix = tempChatPrefix;
	mtx_gv.unlock();
}

void GameVariable::setLeftNick(std::wstring tempLeftNick)
{
	mtx_gv.lock();
	gVars.leftNick = tempLeftNick;
	mtx_gv.unlock();
}

void GameVariable::setJoinedNick(std::wstring tempJoinedNick)
{
	mtx_gv.lock();
	gVars.joinedNick = tempJoinedNick;
	mtx_gv.unlock();
}

void GameVariable::setLeftMsg(std::wstring tempLefMsg)
{
	mtx_gv.lock();
	gVars.leftMsg = tempLefMsg;
	mtx_gv.unlock();
}

void GameVariable::setJoinedMsg(std::wstring tempJoinedMsg)
{
	mtx_gv.lock();
	gVars.joinedMsg = tempJoinedMsg;
	mtx_gv.unlock();
}

void GameVariable::setFuncName(std::string tempFuncName)
{
	mtx_gv.lock();
	gVars.funcName = tempFuncName;
	mtx_gv.unlock();
}

void GameVariable::setServerIP(std::string tempServerIP)
{
	mtx_gv.lock();
	gVars.serverIP = tempServerIP;
	mtx_gv.unlock();
}

void GameVariable::setTempPort(std::string temporaryPort)
{
	mtx_gv.lock();
	gVars.tempPort = temporaryPort;
	mtx_gv.unlock();
}

void GameVariable::setFPS(float tempFPS)
{
	mtx_gv.lock();
	gVars.fps = tempFPS;
	mtx_gv.unlock();
}
void GameVariable::setAimLaserLength(float tempAimLaserLength)
{
	mtx_gv.lock();
	gVars.aimLaserLength = tempAimLaserLength;
	mtx_gv.unlock();
}

void GameVariable::setMenuTimer(float tempMenuTimer)
{
	mtx_gv.lock();
	gVars.menuTimer = tempMenuTimer;
	mtx_gv.unlock();
}

void GameVariable::setDT(float tempDT)
{
	mtx_gv.lock();
	gVars.dt = tempDT;
	mtx_gv.unlock();
}

void GameVariable::setNumberOfEnemies(int tempNumberOfEnemies)
{
	mtx_gv.lock();
	gVars.numberOfEnemies = tempNumberOfEnemies;
	mtx_gv.unlock();
}

void GameVariable::setNumberOfPlayers(int tempNumberOfPlayers)
{
	mtx_gv.lock();
	gVars.numberOfPlayers = tempNumberOfPlayers;
	mtx_gv.unlock();
}

void GameVariable::setMenuNum(int tempMenuNum)
{
	mtx_gv.lock();
	gVars.menuNum = tempMenuNum;
	mtx_gv.unlock();
}

void GameVariable::setServerPort(unsigned short tempServerPort)
{
	mtx_gv.lock();
	gVars.serverPort = tempServerPort;
	mtx_gv.unlock();
}

void GameVariable::setNumOfLinesInChat(int tempNumOfLinesInChat)
{
	mtx_gv.lock();
	gVars.numOfLinesInChat = tempNumOfLinesInChat;
	mtx_gv.unlock();
}

void GameVariable::setNumOfLinesInUserTextBox(int tempNumOfLinesInUserTextBox)
{
	mtx_gv.lock();
	gVars.numOfLinesInUserTextBox = tempNumOfLinesInUserTextBox;
	mtx_gv.unlock();
}

void GameVariable::setPingDelay(sf::Int32 tempPingDelay)
{
	mtx_gv.lock();
	gVars.pingDelay = tempPingDelay;
	mtx_gv.unlock();
}

void GameVariable::setInMenu(bool tempInMenu)
{
	mtx_gv.lock();
	gVars.inMenu = tempInMenu;
	mtx_gv.unlock();
}

void GameVariable::setHideChat(bool tempHideChat)
{
	mtx_gv.lock();
	gVars.hideChat = tempHideChat;
	mtx_gv.unlock();
}

void GameVariable::setNetworkEnd(bool tempNetworkEnd)
{
	mtx_gv.lock();
	gVars.networkEnd = tempNetworkEnd;
	mtx_gv.unlock();
}

void GameVariable::setShowHitbox(bool tempShowHitbox)
{
	mtx_gv.lock();
	gVars.showHitbox = tempShowHitbox;
	mtx_gv.unlock();
}

void GameVariable::setShowAimLaser(bool tempShowAimLaser)
{
	mtx_gv.lock();
	gVars.showAimLaser = tempShowAimLaser;
	mtx_gv.unlock();
}

void GameVariable::setShowLogs(bool tempShowLogs)
{
	mtx_gv.lock();
	gVars.showLogs = tempShowLogs;
	mtx_gv.unlock();
}

void GameVariable::setIsFullscreen(bool tempIsFullscreen)
{
	mtx_gv.lock();
	gVars.isFullscreen = tempIsFullscreen;
	mtx_gv.unlock();
}

void GameVariable::setAllowButtons(bool tempAllowButtons)
{
	mtx_gv.lock();
	gVars.allowButtons = tempAllowButtons;
	mtx_gv.unlock();
}

void GameVariable::setMultiPlayerGame(bool tempMultiplayerGame)
{
	mtx_gv.lock();
	gVars.multiPlayerGame = tempMultiplayerGame;
	mtx_gv.unlock();
}

void GameVariable::setSinglePlayerGame(bool tempSinglePlayerGame)
{
	mtx_gv.lock();
	gVars.singlePlayerGame = tempSinglePlayerGame;
	mtx_gv.unlock();
}

void GameVariable::setFocusEvent(bool tempFocusEvent)
{
	mtx_gv.lock();
	gVars.focusEvent = tempFocusEvent;
	mtx_gv.unlock();
}

void GameVariable::setMainMenu(bool tempMainMenu)
{
	mtx_gv.lock();
	gVars.mainMenu = tempMainMenu;
	mtx_gv.unlock();
}

void GameVariable::setRestartGame(bool tempRestartGame)
{
	mtx_gv.lock();
	gVars.restartGame = tempRestartGame;
	mtx_gv.unlock();
}

void GameVariable::setChatContainsMouse(bool tempChatContainsMouse)
{
	mtx_gv.lock();
	gVars.chatContainsMouse = tempChatContainsMouse;
	mtx_gv.unlock();
}

void GameVariable::setChatEnterText(bool tempChatEnterText)
{
	mtx_gv.lock();
	gVars.chatEnterText = tempChatEnterText;
	mtx_gv.unlock();
}

void GameVariable::setRecvMsg(bool tempRecvMsg)
{
	mtx_gv.lock();
	gVars.recvMsg = tempRecvMsg;
	mtx_gv.unlock();
}

void GameVariable::setSendMsg(bool tempSendMsg)
{
	mtx_gv.lock();
	gVars.sendMsg = tempSendMsg;
	mtx_gv.unlock();
}

void GameVariable::setLeftFromServer(bool tempLeftFromServer)
{
	mtx_gv.lock();
	gVars.leftFromServer = tempLeftFromServer;
	mtx_gv.unlock();
}

void GameVariable::setJoinToServer(bool tempJoinToServer)
{
	mtx_gv.lock();
	gVars.joinToServer = tempJoinToServer;
	mtx_gv.unlock();
}

void GameVariable::setGameLanguage(char tempGameLanguage)
{
	mtx_gv.lock();
	gVars.gameLanguage = tempGameLanguage;
	mtx_gv.unlock();
}

void GameVariable::setSymbol(char tempSymbol)
{
	mtx_gv.lock();
	gVars.symbol = tempSymbol;
	mtx_gv.unlock();
}

void GameVariable::setInput(char tempInput)
{
	mtx_gv.lock();
	gVars.input = tempInput;
	mtx_gv.unlock();
}