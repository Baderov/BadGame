#include "pch.h"
#include "Singleplayer.h"

void respawnEnemies(std::unique_ptr<GameVariable>& gv)
{
	enemiesPool.returnEverythingToPool(enemiesVec);
	int numOfEnemies = 15 + rand() % 15;
	for (int i = 0; i < numOfEnemies; ++i)
	{
		if (enemiesPool.getFromPool(enemiesVec))
		{
			enemiesVec.back()->init(gv, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)));
		}
	}
}

void respawnBoxes(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm)
{
	boxesPool.returnEverythingToPool(boxesVec);
	for (size_t i = 0; i < std::size(sm->boxStartPositions); ++i)
	{
		if (boxesPool.getFromPool(boxesVec))
		{
			boxesVec.back()->init(gv, sm->boxStartPositions[i]);
		}
	}
}

void respawnHPBonuses(std::unique_ptr<GameVariable>& gv)
{
	itemsPool.returnEverythingToPool(itemsVec);
	int numOfItems = 20 + rand() % 20;
	for (int i = 0; i < numOfItems; ++i)
	{
		if (itemsPool.getFromPool(itemsVec))
		{
			itemsVec.back()->init(gv, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)), ItemType::Health);
		}
	}
}

void restartGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm)
{
	bulletsPool.returnEverythingToPool(bulletsVec);

	if (!playerPtr->getIsAlive()) { playerPtr->init(gv, sm->getPlayerStartPos()); }
	else
	{
		playerPtr->setCurrentAmmo(playerPtr->getMagazineAmmo());
		playerPtr->setHP(100);
		playerPtr->setMagazineAmmo(30);
		playerPtr->setMaxAmmo(500);
		playerPtr->setMissingAmmo(0);
		playerPtr->setSpritePos(sm->getPlayerStartPos());
		playerPtr->setMoveTargetPos(sm->getPlayerStartPos());
		playerPtr->setStepPos(sf::Vector2f(0.f, 0.f));
		playerPtr->setMenuTime(0.f);
		playerPtr->setReloadTime(0.f);
		playerPtr->setIsMove(false);
		playerPtr->setIsReload(false);
		playerPtr->setIsShoot(false);
		playerPtr->restartMenuClock();
	}

	respawnBoxes(gv, sm);
	respawnHPBonuses(gv);
	respawnEnemies(gv);
}

void drawGameResult(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm)
{
	if (gv->getGameLanguage() == GameLanguage::English)
	{
		sm->gameResultText.setString(L"GAME RESULT");
		sm->goldCoinsText.setString(L"GOLD COINS: " + std::to_wstring(sm->getGameResultGoldCoins()));
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		sm->gameResultText.setString(L"ÐÅÇÓËÜÒÀÒ ÈÃÐÛ");
		sm->goldCoinsText.setString(L"ÊÎËÈ×ÅÑÒÂÎ ÇÎËÎÒÛÕ ÌÎÍÅÒ: " + std::to_wstring(sm->getGameResultGoldCoins()));
	}
	sm->gameResultText.setOrigin(round(sm->gameResultText.getLocalBounds().left + (sm->gameResultText.getLocalBounds().width / 2.f)), round(sm->gameResultText.getLocalBounds().top + (sm->gameResultText.getLocalBounds().height / 2.f)));
	sm->gameResultText.setPosition(gw->getGameViewCenter().x, gw->getGameViewCenter().y - 400.f);

	sm->goldCoinsText.setOrigin(round(sm->goldCoinsText.getLocalBounds().left + (sm->goldCoinsText.getLocalBounds().width / 2.f)), round(sm->goldCoinsText.getLocalBounds().top + (sm->goldCoinsText.getLocalBounds().height / 2.f)));
	sm->goldCoinsText.setPosition(gw->getGameViewCenter().x, gw->getGameViewCenter().y);

	gw->window.draw(sm->gameResultText);
	gw->window.draw(sm->goldCoinsText);
}

void singleplayerGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	gw->resetVariables();
	gv->resetVariables();

	while (gv->getIsSingleplayer())
	{
		DEBUG_SET_FUNC_NAME;
		updateGame(gv, gw, sm, nm, cw, minimap);
		drawGame(gv, gw, sm, nm, cw, minimap);
		updateFPS(gv);
	}
}