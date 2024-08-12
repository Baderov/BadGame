#ifndef SINGLEPLAYER_MANAGER_H
#define SINGLEPLAYER_MANAGER_H

class SingleplayerManager
{
private:
	sf::Vector2f playerStartPos;
	sf::Clock menuClock;
	int gameResultGoldCoins;
	float menuTimer;
	float menuTime;
public:
	sf::Vector2f boxStartPositions[24];
	sf::Text gameInfoText;
	sf::Text playerInfoText;
	sf::Text playerAmmoText;
	sf::Text gameResultText;
	sf::Text goldCoinsText;

	SingleplayerManager(sf::Font& consolasFont);
	void resetVariables();

	// GETTERS.
	sf::Vector2f getPlayerStartPos();
	int getGameResultGoldCoins();
	float getMenuTimer();
	float getMenuTime();
	float getMenuClockElapsedTime();

	// SETTERS.
	void setPlayerStartPos(sf::Vector2f playerStartPos);
	void setGameResultGoldCoins(int gameResultGoldCoins);
	void setMenuTimer(float menuTimer);
	void setMenuTime(float menuTime);
	void restartMenuClock();

};

#endif