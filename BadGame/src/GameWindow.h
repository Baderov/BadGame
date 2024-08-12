#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

class GameWindow
{
private:
	std::mutex mtx;
	sf::ContextSettings settings;
	sf::Vector2u size;
	sf::View gameView;
	sf::View menuView;
	unsigned int fpsLimiter;
	bool isFullscreen;
	bool isVsync;
public:
	sf::RenderWindow window;

	GameWindow();

	void resetVariables();
	void createWindow(sf::Vector2u size, bool isFullscreen, bool isVsync, unsigned int fpsLimiter);

	sf::Vector2u getSize();
	unsigned int getFPSLimiter();
	bool getIsFullscreen();
	bool getIsVsync();
	sf::Vector2f getGameViewCenter();
	sf::Vector2f getGameViewSize();
	sf::Vector2f getMenuViewCenter();
	sf::Vector2f getMenuViewSize();

	void setMenuView();
	void setGameView();
	void setGameViewCenter(sf::Vector2f viewCenter);
	void setGameViewSize(sf::Vector2f viewSize);
	void setMenuViewCenter(sf::Vector2f viewCenter);
	void setMenuViewSize(sf::Vector2f viewSize);
	void setSize(sf::Vector2u size);
	void setFPSLimiter(unsigned int fpsLimiter);
	void setIsFullscreen(bool isFullscreen);
	void setIsVsync(bool isVsync);

};

#endif