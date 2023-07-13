#include "pch.h"
#include "GameUpdate.h" // game update header file.

sf::Text gameResultText, goldCoinsText;
int gameResultGoldCoins = 0;

float menuTimer = 0.f;

bool s_enterMenu(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // enter menu for singleplayer.
{
	gv->menuClock.restart();
	menuEventHandler(gv, minimap, playersList, chat);
	menuTimer = gv->menuClock.getElapsedTime().asSeconds();

	for (auto& enemy : enemyVec)
	{
		if (enemy == nullptr) { continue; }
		enemy->setMenuTime(menuTimer + enemy->getMenuTime());
	}
	playerPtr->setMenuTime(menuTimer + playerPtr->getMenuTime());

	gv->gameClock.restart();

	gv->setGameView();

	if (!gv->getIsSingleplayer()) { return true; }
	else { return false; }

}

void s_eventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // event handling function for singleplayer.
{
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->window.close();
		break;
	case sf::Event::MouseButtonPressed:
		switch (gv->event.mouseButton.button) // check by mouse button.
		{
		case sf::Mouse::Left:
			playerPtr->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
			playerPtr->setIsMove(true);
			gv->playerDestination.setPosition(playerPtr->getMoveTargetPos()); // set the label position to the mouse click location.
			gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			break;
		case sf::Mouse::Right:
			playerPtr->setIsShoot(true);
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Z:
			if (!gv->getShowLogs()) { gv->setShowLogs(true); } // if the logs were not shown - show.
			else { gv->setShowLogs(false); } // if the logs were shown - don't show them.
			break;
		case sf::Keyboard::X:
			if (!gv->getShowHitbox()) { gv->setShowHitbox(true); } // if hitboxes weren't shown - show them.
			else { gv->setShowHitbox(false); } // if hitboxes were shown, don't show them.
			break;
		case sf::Keyboard::C:
			if (!gv->getShowAimLaser()) { gv->setShowAimLaser(true); } // if the aiming laser was not shown - show.
			else { gv->setShowAimLaser(false); } // if the aiming laser was shown - don't show it.
			break;
		case sf::Keyboard::M:
			gv->setShowMinimap(!(gv->getShowMinimap()));
			break;
		case sf::Keyboard::R:
			if (playerPtr->getCurrentAmmo() < 30 && playerPtr->getMaxAmmo() >= 1 && !playerPtr->getIsReload())
			{
				playerPtr->setIsReload(true);
				playerPtr->restartReloadClock();
				playerPtr->setReloadTime(0.f);
				playerPtr->setMenuTime(0.f);
				break;
			}
			break;
		case sf::Keyboard::Escape:
			if (s_enterMenu(gv, minimap, playersList, chat)) { return; }
			break;
		}
		break;
	}
}

void respawnEnemies(std::unique_ptr<GameVariable>& gv)
{
	enemyPool.returnEverythingToPool(enemyVec);
	int numOfEnemies = 15 + rand() % 15;
	for (int i = 0; i < numOfEnemies; i++)
	{
		if (enemyPool.getFromPool(enemyVec))
		{
			enemyVec.back()->init(gv, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)), L"Enemy" + std::to_wstring(i));
		}
	}
}

void respawnBoxes(std::unique_ptr<GameVariable>& gv)
{
	boxPool.returnEverythingToPool(boxVec);
	for (size_t i = 0; i < std::size(gv->boxStartPositions); i++)
	{
		if (boxPool.getFromPool(boxVec))
		{
			boxVec.back()->init(gv, gv->boxStartPositions[i], L"Box");
		}
	}
}

void respawnHPBonuses(std::unique_ptr<GameVariable>& gv)
{
	itemPool.returnEverythingToPool(itemVec);
	int numOfItems = 20 + rand() % 20;
	for (int i = 0; i < numOfItems; i++)
	{
		if (itemPool.getFromPool(itemVec))
		{
			itemVec.back()->init(gv, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)), L"HPBonus");
		}
	}
}

void restartGame(std::unique_ptr<GameVariable>& gv) // game restart function.
{
	menuTimer = 0.f;

	bulletPool.returnEverythingToPool(bulletVec);

	if (!playerPtr->getIsAlive()) { playerPtr->init(gv, gv->getPlayerStartPos(), gv->getNickname()); }
	else
	{
		playerPtr->setIsReload(false);
		playerPtr->setHP(100);
		playerPtr->setReloadTime(0.f);
		playerPtr->setMagazineAmmo(30);
		playerPtr->setCurrentAmmo(playerPtr->getMagazineAmmo());
		playerPtr->setMaxAmmo(500);
		playerPtr->setMissingAmmo(0);
	}
	respawnBoxes(gv);
	respawnHPBonuses(gv);
	respawnEnemies(gv);
}

void setGameResult(std::unique_ptr<GameVariable>& gv)
{
	gameResultText.setCharacterSize(110);
	gameResultText.setFillColor(sf::Color::Green);
	gameResultText.setOutlineColor(sf::Color::Black);
	gameResultText.setOutlineThickness(3.f);
	gameResultText.setFont(gv->consolasFont);

	goldCoinsText.setCharacterSize(110);
	goldCoinsText.setFillColor(sf::Color::Cyan);
	goldCoinsText.setOutlineColor(sf::Color::Black);
	goldCoinsText.setOutlineThickness(3.f);
	goldCoinsText.setFont(gv->consolasFont);
}

void updatePlayer(std::unique_ptr<GameVariable>& gv, float& fps)
{
	if (playerPtr->getCurrentAmmo() < 30 && playerPtr->getIsReload() && playerPtr->getReloadTime() >= 2.f)
	{
		playerPtr->setMissingAmmo(playerPtr->getMagazineAmmo() - playerPtr->getCurrentAmmo());
		if (playerPtr->getMaxAmmo() < playerPtr->getMagazineAmmo())
		{
			if (playerPtr->getMaxAmmo() + playerPtr->getCurrentAmmo() <= 30)
			{
				playerPtr->setCurrentAmmo(playerPtr->getCurrentAmmo() + playerPtr->getMaxAmmo());
				playerPtr->setMaxAmmo(0);
			}
			else
			{
				int tempAmmo = playerPtr->getMagazineAmmo() - playerPtr->getCurrentAmmo();
				playerPtr->setCurrentAmmo(playerPtr->getCurrentAmmo() + tempAmmo);
				playerPtr->setMaxAmmo(playerPtr->getMaxAmmo() - tempAmmo);
			}
		}
		else
		{
			playerPtr->setCurrentAmmo(playerPtr->getCurrentAmmo() + playerPtr->getMissingAmmo());
			playerPtr->setMaxAmmo(playerPtr->getMaxAmmo() - playerPtr->getMissingAmmo());
		}

		playerPtr->setIsReload(false);
	}
	if (playerPtr->getIsShoot() && playerPtr->getCurrentAmmo() > 0 && !playerPtr->getIsReload() && bulletPool.getFromPool(bulletVec))
	{
		bulletVec.back()->init(gv, playerPtr->getSpritePos(), gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)), L"Bullet", playerPtr->getName());
		playerPtr->setCurrentAmmo(playerPtr->getCurrentAmmo() - 1);
		playerPtr->setIsShoot(false);
	}

	for (auto& wall : wallVec)
	{
		if (wall == nullptr) { continue; }
		collisionHandler(gv, playerPtr.get(), wall.get()); // calling the collision handling function.
	}
	for (auto& box : boxVec)
	{
		if (box == nullptr) { continue; }
		collisionHandler(gv, playerPtr.get(), box.get()); // calling the collision handling function.
	}
	for (auto& enemy : enemyVec)
	{
		if (enemy == nullptr) { continue; }
		collisionHandler(gv, playerPtr.get(), enemy.get()); // calling the collision handling function.
	}
	for (auto& item : itemVec)
	{
		if (item == nullptr) { continue; }
		collisionHandler(gv, playerPtr.get(), item.get()); // calling the collision handling function.
	}

	playerPtr->update(gv);

	if (!playerPtr->getIsAlive()) { gameResultGoldCoins = playerPtr->getGoldCoins(); }

	//playerPtr->setIsCollision(false);

	gv->setGameViewCenter(playerPtr->getSpritePos());
	setGameInfo(gv, playerPtr.get(), fps); // call the function for setting game information.
}

void updateGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat, float& fps) // game update function. 
{
	gv->setDT();
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.

	while (gv->window.pollEvent(gv->event)) { s_eventHandler(gv, minimap, playersList, chat); } // call the event handling function.

	if (gv->getRestartGame() || (enemyVec.empty() && playerPtr->getIsAlive()))
	{
		restartGame(gv);
		gv->setRestartGame(false);
		return;
	}

	updatePlayer(gv, fps);

	if (playerPtr->getIsAlive())
	{
		for (auto& enemy : enemyVec)
		{
			if (enemy == nullptr) { continue; }

			enemy->setAimPos(playerPtr->getSpritePos());

			if (enemy->getIsShoot())
			{
				float distance = sqrt(((enemy->getAimPos().x - enemy->getSpritePos().x) * (enemy->getAimPos().x - enemy->getSpritePos().x)) + ((enemy->getAimPos().y - enemy->getSpritePos().y) * (enemy->getAimPos().y - enemy->getSpritePos().y)));
				if (distance < 750.f && bulletPool.getFromPool(bulletVec))
				{
					bulletVec.back()->init(gv, enemy->getSpritePos(), enemy->getAimPos(), L"Bullet", enemy->getName());
				}
				enemy->setIsShoot(false);
			}

			for (auto& wall : wallVec)
			{
				if (wall == nullptr) { continue; }
				collisionHandler(gv, enemy.get(), wall.get()); // calling the collision handling function.
			}

			for (auto& box : boxVec)
			{
				if (box == nullptr) { continue; }
				collisionHandler(gv, enemy.get(), box.get()); // calling the collision handling function.
			}

			for (auto& enemy2 : enemyVec)
			{
				if (enemy2 == nullptr) { continue; }
				collisionHandler(gv, enemy.get(), enemy2.get()); // calling the collision handling function.
			}

			enemy->update(gv);

			if (!enemy->getIsAlive()) // if entity is dead.
			{
				int numOfItems = 0 + rand() % 6;

				for (int i = 0; i < numOfItems; i++)
				{
					if (itemPool.getFromPool(itemVec))
					{
						itemVec.back()->init(gv, sf::Vector2f(enemy->getSpritePos().x + (i * 15), enemy->getSpritePos().y), L"GoldCoin");
					}
				}
				enemyPool.returnToPool(enemyVec, enemy);
			}
		}

		for (auto& wall : wallVec)
		{
			if (wall == nullptr) { continue; }

			for (auto& enemy : enemyVec)
			{
				if (enemy == nullptr) { continue; }
				collisionHandler(gv, wall.get(), enemy.get()); // calling the collision handling function.	
			}

			wall->update(gv);
		}

		for (auto& box : boxVec)
		{
			if (box == nullptr) { continue; }

			for (auto& enemy : enemyVec)
			{
				if (enemy == nullptr) { continue; }
				collisionHandler(gv, box.get(), enemy.get()); // calling the collision handling function.
			}

			box->update(gv);

			if (!box->getIsAlive())
			{
				int itemType = 0 + rand() % 3;
				int numOfItems = 0;

				if (itemType == 1)
				{
					numOfItems = 0 + rand() % 2;
					for (int i = 0; i < numOfItems; i++)
					{
						if (itemPool.getFromPool(itemVec))
						{
							itemVec.back()->init(gv, sf::Vector2f(box->getSpritePos().x + (i * 15), box->getSpritePos().y), L"HPBonus");
						}
					}
				}
				else if (itemType == 2)
				{
					numOfItems = 0 + rand() % 6;
					for (int i = 0; i < numOfItems; i++)
					{
						if (itemPool.getFromPool(itemVec))
						{
							itemVec.back()->init(gv, sf::Vector2f(box->getSpritePos().x + (i * 15), box->getSpritePos().y), L"GoldCoin");
						}
					}
				}
				boxPool.returnToPool(boxVec, box);
			}
		}

		for (auto& item : itemVec)
		{
			if (item == nullptr) { continue; }

			item->update(gv);

			if (!item->getIsAlive()) { itemPool.returnToPool(itemVec, item); }
		}

		for (auto& bullet : bulletVec)
		{
			if (bullet == nullptr) { continue; }

			for (auto& wall : wallVec)
			{
				if (wall == nullptr) { continue; }
				collisionHandler(gv, bullet.get(), wall.get()); // calling the collision handling function.
			}

			for (auto& box : boxVec)
			{
				if (box == nullptr) { continue; }
				collisionHandler(gv, bullet.get(), box.get()); // calling the collision handling function.
			}

			for (auto& enemy : enemyVec)
			{
				if (enemy == nullptr) { continue; }
				collisionHandler(gv, bullet.get(), enemy.get()); // calling the collision handling function.
			}

			collisionHandler(gv, bullet.get(), playerPtr.get()); // calling the collision handling function.

			bullet->update(gv);

			if (!bullet->getIsAlive()) { bulletPool.returnToPool(bulletVec, bullet); }
		}
	}
	else
	{
		for (auto& enemy : enemyVec)
		{
			if (enemy == nullptr) { continue; }
			enemyPool.returnToPool(enemyVec, enemy);
		}
	}

	enemyPool.eraseEmptyVecElements(enemyVec);
	boxPool.eraseEmptyVecElements(boxVec);
	itemPool.eraseEmptyVecElements(itemVec);
	bulletPool.eraseEmptyVecElements(bulletVec);

	gv->setGameViewCenter(playerPtr->getSpritePos());

	if (gv->getShowMinimap())
	{
		minimap.setViewCenter(sf::Vector2f((minimap.getViewSize().x / 2.f) - 300.f, (minimap.getViewSize().y / 2.f) - 250.f));
		minimap.setBorderPos(sf::Vector2f(gv->getGameViewCenter().x + (0.3f * gv->getGameViewSize().x), gv->getGameViewCenter().y - (0.5f * gv->getGameViewSize().y)));
	}
}

void drawGameResult(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getGameLanguage() == 'e')
	{
		gameResultText.setString(L"GAME RESULT");
		goldCoinsText.setString(L"GOLD COINS: " + std::to_wstring(gameResultGoldCoins));
	}
	else if (gv->getGameLanguage() == 'r')
	{
		gameResultText.setString(L"ÐÅÇÓËÜÒÀÒ ÈÃÐÛ");
		goldCoinsText.setString(L"ÊÎËÈ×ÅÑÒÂÎ ÇÎËÎÒÛÕ ÌÎÍÅÒ: " + std::to_wstring(gameResultGoldCoins));
	}
	gameResultText.setOrigin(round(gameResultText.getLocalBounds().left + (gameResultText.getLocalBounds().width / 2.f)), round(gameResultText.getLocalBounds().top + (gameResultText.getLocalBounds().height / 2.f)));
	gameResultText.setPosition(gv->getGameViewCenter().x, gv->getGameViewCenter().y - 400.f);

	goldCoinsText.setOrigin(round(goldCoinsText.getLocalBounds().left + (goldCoinsText.getLocalBounds().width / 2.f)), round(goldCoinsText.getLocalBounds().top + (goldCoinsText.getLocalBounds().height / 2.f)));
	goldCoinsText.setPosition(gv->getGameViewCenter().x, gv->getGameViewCenter().y);

	gv->window.draw(gameResultText);
	gv->window.draw(goldCoinsText);
}

void drawPlayer(std::unique_ptr<GameVariable>& gv)
{
	if (gv->getShowAimLaser() && gv->getFocusEvent()) { gv->window.draw(gv->aimLaser); }
	if (playerPtr->getIsMove()) { gv->window.draw(gv->playerDestination); }
	if (gv->getShowHitbox()) { playerPtr->drawRectHitbox(gv); }
	else { playerPtr->drawSprite(gv); }
	playerPtr->drawHPBarOuter(gv);
	playerPtr->drawHPBarInner(gv);
	if (playerPtr->getIsReload()) // if the entity is reloading.
	{
		playerPtr->drawReloadRectOuter(gv);
		playerPtr->drawReloadRectInner(gv);
		playerPtr->drawReloadText(gv);
	}
	playerPtr->drawHPText(gv);
	playerPtr->drawNameText(gv);
}

void drawMinimap(std::unique_ptr<GameVariable>& gv, Minimap& minimap)
{
	if (gv->getShowMinimap())
	{
		minimap.setView(gv);

		playerPtr->drawIcon(gv);

		for (auto& enemy : enemyVec)
		{
			if (enemy == nullptr) { continue; }
			enemy->drawIcon(gv);
		}

		for (auto& wall : wallVec)
		{
			if (wall == nullptr) { continue; }
			wall->drawSprite(gv);
		}

		for (auto& box : boxVec)
		{
			if (box == nullptr) { continue; }
			box->drawSprite(gv);
		}

		gv->setGameView();
	}
}

void drawEntities(std::unique_ptr<GameVariable>& gv, Minimap& minimap)
{
	gv->setGameView();

	for (auto& wall : wallVec)
	{
		if (wall == nullptr) { continue; }
		if (gv->getShowHitbox()) { wall->drawRectHitbox(gv); }
		else { wall->drawSprite(gv); }
	}

	for (auto& box : boxVec)
	{
		if (box == nullptr) { continue; }
		if (gv->getShowHitbox()) { box->drawRectHitbox(gv); }
		else { box->drawSprite(gv); }
	}

	for (auto& item : itemVec)
	{
		if (item == nullptr) { continue; }
		if (gv->getShowHitbox()) { item->drawRectHitbox(gv); }
		else { item->drawSprite(gv); }
	}

	for (auto& bullet : bulletVec)
	{
		if (bullet == nullptr) { continue; }
		if (gv->getShowHitbox()) { bullet->drawRectHitbox(gv); }
		else { bullet->drawSprite(gv); }
	}

	for (auto& enemy : enemyVec)
	{
		if (enemy == nullptr) { continue; }
		if (gv->getShowHitbox()) { enemy->drawRectHitbox(gv); }
		else { enemy->drawSprite(gv); }
		enemy->drawHPBarOuter(gv);
		enemy->drawHPBarInner(gv);
		if (enemy->getIsReload())
		{
			enemy->drawReloadRectOuter(gv);
			enemy->drawReloadRectInner(gv);
			enemy->drawReloadText(gv);
		}
		enemy->drawHPText(gv);
		enemy->drawNameText(gv);
	}

	drawPlayer(gv);

	minimap.draw(gv);
}

void drawGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap) // game drawing function.
{
	if (!gv->getIsSingleplayer()) { return; }

	gv->window.clear(gv->backgroundColor);

	if (!playerPtr->getIsAlive()) { drawGameResult(gv); gv->window.display(); return; }

	drawEntities(gv, minimap);
	drawMinimap(gv, minimap);
	drawGameInfo(gv->window, gv->getShowLogs()); // calling the function for drawing game information.

	gv->window.display();
}