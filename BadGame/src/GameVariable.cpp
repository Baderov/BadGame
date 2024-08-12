#include "pch.h"
#include "GameVariable.h"

GameVariable::GameVariable()
{
	consolasFont.loadFromFile("Fonts\\consolas.ttf");

	gameLanguage = GameLanguage::English;
	gameState = GameState::MainMenu;
	mousePos = sf::Vector2f(0.f, 0.f);
	targetPos = sf::Vector2f(0.f, 0.f);
	funcName = "";
	fpsPreviousTime = 0.f;
	fpsCurrentTime = 0.f;
	fps = 0.f;
	dt = 0.f;

	backgroundColor.r = 204;
	backgroundColor.g = 153;
	backgroundColor.b = 255;

	greyColor.r = 120;
	greyColor.g = 120;
	greyColor.b = 120;

	showAimLaser = false;
	showLogs = false;
	showMinimap = true;
	showCollisionRect = false;
	isSingleplayer = false;
	isMultiplayer = false;
	focusEvent = true;

	bulletImage.loadFromFile("Images/bullet.png");
	bulletImage.createMaskFromColor(sf::Color(0, 0, 0));
	wallImage.loadFromFile("Images/wall.png");

	goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png");
	goldCoinHUDTexture.loadFromImage(goldCoinHUDImage);
	goldCoinHUDSprite.setTexture(goldCoinHUDTexture);

	playerImage.loadFromFile("Images/player.png");
	enemyImage.loadFromFile("Images/enemy.png");
	boxImage.loadFromFile("Images/box.png");
	goldCoinImage.loadFromFile("Images/goldCoin.png");
	hpBonusImage.loadFromFile("Images/hpBonus.png");

	playerDestination.setRadius(20.f);
	playerDestination.setOrigin(playerDestination.getRadius(), playerDestination.getRadius());
	playerDestination.setFillColor(sf::Color::Transparent);
	playerDestination.setOutlineThickness(5.f);
	playerDestination.setOutlineColor(backgroundColor);

	aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	aimLaser.setFillColor(sf::Color::Red);

	connectionErrorText.setString("");
	OKButtonText.setString("");
	fpsClock.restart();
	gameClock.restart();
}

void GameVariable::resetVariables()
{
	mousePos = sf::Vector2f(0.f, 0.f);
	targetPos = sf::Vector2f(0.f, 0.f);
	funcName = "";
	fpsPreviousTime = 0.f;
	fpsCurrentTime = 0.f;
	fps = 0.f;
	dt = 0.f;
	showAimLaser = false;
	showLogs = false;
	showMinimap = true;
	showCollisionRect = false;
	focusEvent = true;
	aimLaser.setSize(sf::Vector2f(2.25f, 100.f));
	connectionErrorText.setString("");
	OKButtonText.setString("");
	fpsClock.restart();
	gameClock.restart();
}




// GETTERS.
GameLanguage GameVariable::getGameLanguage()
{
	std::lock_guard<std::mutex> lock(mtx);
	GameLanguage gameLanguage = this->gameLanguage;
	return gameLanguage;
}

GameState GameVariable::getGameState()
{
	std::lock_guard<std::mutex> lock(mtx);
	GameState gameState = this->gameState;
	return gameState;
}

sf::Vector2f GameVariable::getMousePos()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f mousePos = this->mousePos;
	return mousePos;
}

sf::Vector2f GameVariable::getTargetPos()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f targetPos = this->targetPos;
	return targetPos;
}

std::string GameVariable::getFuncName()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::string funcName = this->funcName;
	return funcName;
}

float GameVariable::getFPS()
{
	std::lock_guard<std::mutex> lock(mtx);
	float fps = this->fps;
	return fps;
}

float GameVariable::getDT()
{
	std::lock_guard<std::mutex> lock(mtx);
	float dt = this->dt;
	return dt;
}

float GameVariable::getGameClockElapsedTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	return gameClock.getElapsedTime().asSeconds();
}

float GameVariable::getFPSClockElapsedTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	return fpsClock.getElapsedTime().asSeconds();
}

float GameVariable::getFPSPreviousTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	float fpsPreviousTime = this->fpsPreviousTime;
	return fpsPreviousTime;
}

float GameVariable::getFPSCurrentTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	float fpsCurrentTime = this->fpsCurrentTime;
	return fpsCurrentTime;
}

bool GameVariable::getShowAimLaser()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool showAimLaser = this->showAimLaser;
	return showAimLaser;
}

bool GameVariable::getShowLogs()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool showLogs = this->showLogs;
	return showLogs;
}

bool GameVariable::getShowMinimap()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool showMinimap = this->showMinimap;
	return showMinimap;
}

bool GameVariable::getShowCollisionRect()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool showCollisionRect = this->showCollisionRect;
	return showCollisionRect;
}

bool GameVariable::getIsSingleplayer()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isSingleplayer = this->isSingleplayer;
	return isSingleplayer;
}

bool GameVariable::getIsMultiplayer()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isMultiplayer = this->isMultiplayer;
	return isMultiplayer;
}

bool GameVariable::getFocusEvent()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool focusEvent = this->focusEvent;
	return focusEvent;
}



// SETTERS.
void GameVariable::setGameLanguage(GameLanguage gameLanguage)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->gameLanguage = std::move(gameLanguage);
}

void GameVariable::setGameState(GameState gameState)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->gameState = std::move(gameState);
}

void GameVariable::setMousePos(sf::Vector2f mousePos)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->mousePos = std::move(mousePos);
}

void GameVariable::setTargetPos(sf::Vector2f targetPos)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->targetPos = std::move(targetPos);
}

void GameVariable::setFuncName(std::string funcName)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->funcName = std::move(funcName);
}

void GameVariable::setFPS(float fps)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->fps = std::move(fps);
}

void  GameVariable::setFPSPreviousTime(float fpsPreviousTime)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->fpsPreviousTime = std::move(fpsPreviousTime);
}
void  GameVariable::setFPSCurrentTime(float fpsCurrentTime)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->fpsCurrentTime = std::move(fpsCurrentTime);
}

void GameVariable::setDT()
{
	std::lock_guard<std::mutex> lock(mtx);
	dt = gameClock.restart().asSeconds();
}

void GameVariable::restartGameClock()
{
	std::lock_guard<std::mutex> lock(mtx);
	gameClock.restart();
}

void GameVariable::setShowAimLaser(bool showAimLaser)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->showAimLaser = std::move(showAimLaser);
}

void GameVariable::setShowLogs(bool showLogs)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->showLogs = std::move(showLogs);
}

void GameVariable::setShowMinimap(bool showMinimap)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->showMinimap = std::move(showMinimap);
}

void GameVariable::setShowCollisionRect(bool showCollisionRect)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->showCollisionRect = std::move(showCollisionRect);
}

void GameVariable::setIsSingleplayer(bool isSingleplayer)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isSingleplayer = std::move(isSingleplayer);
}

void GameVariable::setIsMultiplayer(bool isMultiplayer)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isMultiplayer = std::move(isMultiplayer);
}

void GameVariable::setFocusEvent(bool focusEvent)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->focusEvent = std::move(focusEvent);
}