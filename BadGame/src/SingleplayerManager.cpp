#include "pch.h"
#include "SingleplayerManager.h"
#include "Network.h"

SingleplayerManager::SingleplayerManager(sf::Font& consolasFont)
{
	consoleSettings();

	srand(static_cast<unsigned int>(time(NULL)));

	size_t tempVar = 0;
	for (size_t i = 0; i < 24; ++i)
	{
		if (tempVar == 6 || tempVar == 12 || tempVar == 18 || tempVar == 24) { tempVar = 0; }

		if (i < 6)
		{
			boxStartPositions[i] = sf::Vector2f(1250.f + (500.f * tempVar), 1000.f);
			tempVar++;
		}
		else if (i >= 6 && i < 12)
		{
			boxStartPositions[i] = sf::Vector2f(1250.f + (500.f * tempVar), 2000.f);
			tempVar++;
		}
		else if (i >= 12 && i < 18)
		{
			boxStartPositions[i] = sf::Vector2f(1250.f + (500.f * tempVar), 3000.f);
			tempVar++;
		}
		else if (i >= 18 && i < 24)
		{
			boxStartPositions[i] = sf::Vector2f(1250.f + (500.f * tempVar), 4000.f);
			tempVar++;
		}
	}

	playerStartPos = sf::Vector2f(2500.f, 2500.f);
	gameResultGoldCoins = 0;

	gameInfoText.setString("");
	playerInfoText.setString("");
	playerAmmoText.setString("");
	gameResultText.setString("");
	goldCoinsText.setString("");

	gameResultText.setCharacterSize(110);
	gameResultText.setFillColor(sf::Color::Green);
	gameResultText.setOutlineColor(sf::Color::Black);
	gameResultText.setOutlineThickness(3.f);
	gameResultText.setFont(consolasFont);

	goldCoinsText.setCharacterSize(110);
	goldCoinsText.setFillColor(sf::Color::Cyan);
	goldCoinsText.setOutlineColor(sf::Color::Black);
	goldCoinsText.setOutlineThickness(3.f);
	goldCoinsText.setFont(consolasFont);

	gameInfoText.setFont(consolasFont);
	gameInfoText.setFillColor(sf::Color::Black);

	playerInfoText.setFont(consolasFont);
	playerInfoText.setCharacterSize(60);
	playerInfoText.setFillColor(sf::Color::Cyan);
	playerInfoText.setOutlineThickness(2.f);

	playerAmmoText.setFont(consolasFont);
	playerAmmoText.setCharacterSize(50);
	playerAmmoText.setFillColor(sf::Color::Green);
	playerAmmoText.setOutlineThickness(2.f);
}

void SingleplayerManager::resetVariables()
{
	playerStartPos = sf::Vector2f(2500.f, 2500.f);
	gameResultGoldCoins = 0;
	gameInfoText.setString("");
	playerInfoText.setString("");
	playerAmmoText.setString("");
	gameResultText.setString("");
	goldCoinsText.setString("");
}

// GETTERS.
sf::Vector2f SingleplayerManager::getPlayerStartPos()
{
	sf::Vector2f playerStartPos = this->playerStartPos;
	return playerStartPos;
}

int SingleplayerManager::getGameResultGoldCoins()
{
	int gameResultGoldCoins = this->gameResultGoldCoins;
	return gameResultGoldCoins;
}


// SETTERS.
void SingleplayerManager::setPlayerStartPos(sf::Vector2f playerStartPos) { this->playerStartPos = std::move(playerStartPos); }
void SingleplayerManager::setGameResultGoldCoins(int gameResultGoldCoins) { this->gameResultGoldCoins = std::move(gameResultGoldCoins); }