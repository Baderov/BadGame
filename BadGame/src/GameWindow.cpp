#include "pch.h"
#include "GameWindow.h"

GameWindow::GameWindow()
{
	sf::Vector2u windowSize(1366, 768);
	bool isFullscreen = false;
	bool isVsync = true;
	unsigned int FPSLimiter = 75;

	createWindow(windowSize, isFullscreen, isVsync, FPSLimiter);

	setMenuViewSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	setMenuViewCenter(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	setGameViewCenter(sf::Vector2f(0.f, 0.f));
}

void GameWindow::resetVariables()
{
	setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	setGameViewCenter(sf::Vector2f(0.f, 0.f));
	setGameView();
}

void GameWindow::createWindow(sf::Vector2u size, bool isFullscreen, bool isVsync, unsigned int fpsLimiter)
{
	settings.antialiasingLevel = 8;

	this->size = std::move(size);
	this->isFullscreen = std::move(isFullscreen);
	this->isVsync = std::move(isVsync);
	this->fpsLimiter = std::move(fpsLimiter);

	if (this->isFullscreen) { window.create(sf::VideoMode(this->size.x, this->size.y), "BadGame", sf::Style::Fullscreen, settings); }
	else { window.create(sf::VideoMode(this->size.x, this->size.y), "BadGame", sf::Style::Close, settings); }

	if (this->isVsync) { window.setVerticalSyncEnabled(true); window.setFramerateLimit(0); }
	else { window.setVerticalSyncEnabled(false); window.setFramerateLimit(this->fpsLimiter); }

	setMenuViewSize(sf::Vector2f(static_cast<float>(this->size.x), static_cast<float>(this->size.y)));
	setMenuViewCenter(sf::Vector2f(static_cast<float>(this->size.x) / 2.f, static_cast<float>(this->size.y) / 2.f));
	setMenuView();
}


sf::Vector2u GameWindow::getSize()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2u size = this->size;
	return size;
}

unsigned int GameWindow::getFPSLimiter()
{
	std::lock_guard<std::mutex> lock(mtx);
	unsigned int fpsLimiter = this->fpsLimiter;
	return fpsLimiter;
}

bool GameWindow::getIsFullscreen()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isFullscreen = this->isFullscreen;
	return isFullscreen;
}
bool GameWindow::getIsVsync()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isVsync = this->isVsync;
	return isVsync;
}

sf::Vector2f GameWindow::getGameViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f viewCenter = gameView.getCenter();
	return viewCenter;
}

sf::Vector2f GameWindow::getGameViewSize()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f viewSize = gameView.getSize();
	return viewSize;
}

sf::Vector2f GameWindow::getMenuViewCenter()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f viewCenter = menuView.getCenter();
	return viewCenter;
}

sf::Vector2f GameWindow::getMenuViewSize()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2f viewSize = menuView.getSize();
	return viewSize;
}





void GameWindow::setMenuView()
{
	std::lock_guard<std::mutex> lock(mtx);
	window.setView(menuView);
}

void GameWindow::setGameView()
{
	std::lock_guard<std::mutex> lock(mtx);
	window.setView(gameView);
}

void GameWindow::setGameViewCenter(sf::Vector2f viewCenter)
{
	std::lock_guard<std::mutex> lock(mtx);
	gameView.setCenter(std::move(viewCenter));
}

void GameWindow::setGameViewSize(sf::Vector2f viewSize)
{
	std::lock_guard<std::mutex> lock(mtx);
	gameView.setSize(std::move(viewSize));
}

void GameWindow::setMenuViewCenter(sf::Vector2f viewCenter)
{
	std::lock_guard<std::mutex> lock(mtx);
	menuView.setCenter(std::move(viewCenter));
}

void GameWindow::setMenuViewSize(sf::Vector2f viewSize)
{
	std::lock_guard<std::mutex> lock(mtx);
	menuView.setSize(std::move(viewSize));
}

void GameWindow::setSize(sf::Vector2u size)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->size = std::move(size);
}

void GameWindow::setFPSLimiter(unsigned int FPSLimiter)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->fpsLimiter = std::move(FPSLimiter);
}

void GameWindow::setIsFullscreen(bool isFullscreen)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isFullscreen = std::move(isFullscreen);
}

void GameWindow::setIsVsync(bool isVsync)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isVsync = std::move(isVsync);
}