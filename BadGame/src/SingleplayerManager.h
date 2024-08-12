#ifndef SINGLEPLAYER_MANAGER_H
#define SINGLEPLAYER_MANAGER_H

class SingleplayerManager
{
private:
	sf::Vector2f playerStartPos;
	int gameResultGoldCoins;
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

	// SETTERS.
	void setPlayerStartPos(sf::Vector2f playerStartPos);
	void setGameResultGoldCoins(int gameResultGoldCoins);
};

#endif