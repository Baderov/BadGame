#include "pch.h"
#include "Text.h" 

sf::Text gameInfoText;
sf::Text playerInfoText;
sf::Text playerAmmoText;

sf::Texture goldCoinHUDTexture;
sf::Sprite goldCoinHUDSprite;

void setTextsAndSprites(std::unique_ptr<GameVariable>& gv) // function for setting values for texts and sprites.
{
	gameInfoText.setFont(gv->consolasFont);
	gameInfoText.setFillColor(sf::Color::Black);

	playerInfoText.setFont(gv->consolasFont);
	playerInfoText.setCharacterSize(60);
	playerInfoText.setFillColor(sf::Color::Cyan);
	playerInfoText.setOutlineThickness(2.f);

	playerAmmoText.setFont(gv->consolasFont);
	playerAmmoText.setCharacterSize(50);
	playerAmmoText.setFillColor(sf::Color::Cyan);
	playerAmmoText.setOutlineThickness(2.f);


	gv->goldCoinHUDImage.loadFromFile("Images/goldCoinHUD.png");
	goldCoinHUDTexture.loadFromImage(gv->goldCoinHUDImage);
	goldCoinHUDSprite.setTexture(goldCoinHUDTexture);
}

void setGameInfo(std::unique_ptr<GameVariable>& gv, Entity* player, float& fps) // function for setting game information.
{
	if (player != nullptr) { playerInfoText.setString(std::to_string(player->getGoldCoins())); }
	if (gv->getGameLanguage() == 'e')
	{
		gameInfoText.setString(
			"GAME INFO\nMouse X pos: " + std::to_string(gv->getMousePos().x) + "\nMouse Y pos: " + std::to_string(gv->getMousePos().y) +
			"\nNumber of enemies: " + std::to_string(enemyVec.size()) +
			"\nNumber of boxes: " + std::to_string(boxVec.size()) + "\nNumber of bullets: " + std::to_string(bulletVec.size()) +
			"\nNumber of walls: " + std::to_string(wallVec.size()) + "\nNumber of items: " + std::to_string(itemVec.size()) +
			"\nFPS: " + std::to_string(static_cast<int>(fps)));

		if (player != nullptr) // if the player is alive.
		{
			playerAmmoText.setString("Ammo: " + std::to_string(player->getCurrentAmmo()) + "/" + std::to_string(player->getMaxAmmo()));
		}
	}
	else if (gv->getGameLanguage() == 'r')
	{
		gameInfoText.setString(
			L"ИГРОВАЯ ИНФОРМАЦИЯ\nПозиция мыши X: " + std::to_wstring(gv->getMousePos().x) + L"\nПозиция мыши Y: " + std::to_wstring(gv->getMousePos().y) +
			L"\nКоличество врагов: " + std::to_wstring(enemyVec.size()) +
			L"\nКоличество коробок: " + std::to_wstring(boxVec.size()) + L"\nКоличество пуль: " + std::to_wstring(bulletVec.size()) +
			L"\nКоличество стен: " + std::to_wstring(wallVec.size()) + L"\nКоличество предметов: " + std::to_wstring(itemVec.size()) +
			L"\nФПС: " + std::to_wstring(static_cast<int>(fps)));

		if (player != nullptr) // if the player is alive.
		{
			playerAmmoText.setString(L"Патроны: " + std::to_wstring(player->getCurrentAmmo()) + L"/" + std::to_wstring(player->getMaxAmmo()));
		}
	}

	gameInfoText.setPosition(gv->getGameViewCenter().x - 600.f, gv->getGameViewCenter().y - 350.f);
	playerInfoText.setPosition(gv->getGameViewCenter().x + 600.f, gv->getGameViewCenter().y + 150.f);
	goldCoinHUDSprite.setPosition(gv->getGameViewCenter().x + 500.f, gv->getGameViewCenter().y + 150.f);
	playerAmmoText.setPosition(gv->getGameViewCenter().x + 500.f, gv->getGameViewCenter().y + 300.f);
}

void drawGameInfo(sf::RenderWindow& window, bool showLogs) // function for drawing game information.
{
	if (showLogs) { window.draw(gameInfoText); }
	window.draw(goldCoinHUDSprite);
	window.draw(playerInfoText);
	window.draw(playerAmmoText);
}