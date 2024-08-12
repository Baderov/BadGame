#include "pch.h"
#include "GameUpdate.h"

const int ENTER_CODE = 13;

void enterMenu(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap) // enter menu for singleplayer.
{
	playerPtr->restartMenuClock();
	for (size_t i = 0; i < enemiesVec.size(); i++) { enemiesVec[i]->restartMenuClock(); }

	gv->setGameState(GameState::GameMenu);

	menuEventHandler(gv, gw, sm, nm, cw, minimap, MenuType::GameMenu);

	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		playerPtr->setMenuTime(playerPtr->getMenuTime() + playerPtr->getMenuClockElapsedTime());
		for (size_t i = 0; i < enemiesVec.size(); i++)
		{
			enemiesVec[i]->setMenuTime(enemiesVec[i]->getMenuTime() + enemiesVec[i]->getMenuClockElapsedTime());
		}
	}

	gw->setGameView();
	gv->restartGameClock();
}

void eventHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap) // event handling function for singleplayer.
{
	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		sf::Event event;
		while (gw->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				gv->setIsSingleplayer(false);
				gw->window.close();
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					playerPtr->setMoveTargetPos(gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)));
					playerPtr->setIsMove(true);
					playerPtr->setIsCollision(false);
					gv->playerDestination.setPosition(playerPtr->getMoveTargetPos()); // set the label position to the mouse click location.
					gv->playerDestination.setOutlineColor(sf::Color::Yellow);
					break;
				case sf::Mouse::Right:
					if (!playerPtr->getIsReload() && playerPtr->getIsAlive()) { playerPtr->setIsShoot(true); }
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					gv->setShowLogs(!gv->getShowLogs());
					break;

				case sf::Keyboard::X:
					gv->setShowCollisionRect(!gv->getShowCollisionRect());
					break;

				case sf::Keyboard::C:
					gv->setShowAimLaser(!gv->getShowAimLaser());
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
					enterMenu(gv, gw, sm, nm, cw, minimap);
					break;
				}
				break;
			}
		}
	}

	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer())
	{
		sf::Event event;
		while (gw->window.pollEvent(event))
		{
			cw->handleGameGUIEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				gv->setIsMultiplayer(false);
				gw->window.close();
				break;

			case sf::Event::LostFocus:
				gv->setFocusEvent(false);
				break;

			case sf::Event::GainedFocus:
				gv->setFocusEvent(true);
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					setMoveTarget(gv, gw, nm, cw);

					cw->updateEditBox();

					if (networkAction == NetworkAction::ServerIsNotAvailable)
					{
						nm->setServerIsNotAvailable(false);
						gv->setIsMultiplayer(false);
						gv->setGameState(GameState::GameOver);
						networkAction = NetworkAction::Nothing;
					}
				}
				break;

				case sf::Mouse::Right:
					std::lock_guard<std::mutex> lock(clients_mtx);
					for (size_t i = 0; i < clientsVec.size(); ++i)
					{
						if (clientsVec[i]->getName() != nm->getNickname() || clientsVec[i]->getIsShoot() || nm->getServerIsNotAvailable() || clientsVec[i]->getIsGhost()) { continue; }

						clientsVec[i]->setIsShoot(true);
						shootRequest(nm, clientsVec[i]->getName(), gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)), clientsVec[i]->getSpritePos());
						clientsVec[i]->setCurrentAmmo(clientsVec[i]->getCurrentAmmo() - 1);
						clientsVec[i]->setIsShoot(false);

						break;
					}
					break;
				}

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Tab:
					cw->setPlayersListVisible(true);
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Tab:
					cw->setPlayersListVisible(false);
					break;

				case sf::Keyboard::Z:
					gv->setShowLogs(!gv->getShowLogs());
					break;

				case sf::Keyboard::X:
					gv->setShowCollisionRect(!gv->getShowCollisionRect());
					break;

				case sf::Keyboard::C:
					if (cw->editBoxIsReadOnly() && !nm->getServerIsNotAvailable()) { gv->setShowAimLaser(!gv->getShowAimLaser()); }
					break;

				case sf::Keyboard::O:
					if (cw->editBoxIsReadOnly() && !nm->getServerIsNotAvailable())
					{
						cw->setChatBoxVisible(!cw->chatBoxIsVisible());
						cw->setEditBoxVisible(!cw->editBoxIsVisible());
					}
					break;

				case sf::Keyboard::M:
					if (cw->editBoxIsReadOnly() && !nm->getServerIsNotAvailable()) { gv->setShowMinimap(!(gv->getShowMinimap())); }
					break;

				case sf::Keyboard::Escape:
					enterMenu(gv, gw, sm, nm, cw, minimap);
					break;
				}
				break;

			case sf::Event::TextEntered:
				std::lock_guard<std::mutex> lock(clients_mtx);
				for (size_t i = 0; i < clientsVec.size(); ++i)
				{
					if (clientsVec[i]->getName() != nm->getNickname()) { continue; }

					if (event.text.unicode == ENTER_CODE && !cw->editBoxIsReadOnly() && cw->getEditBoxText().trim().toWideString() != L"" && nm->getAllowToSendMsg())
					{
						nm->setAllowToSendMsg(false);
						std::wstring msg = cw->getEditBoxText().trim().toWideString();
						messageRequest(nm, std::move(msg));
						cw->setEditBoxText("");
					}

					break;
				}
				break;
			}
		}
	}
}

void updateGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	gv->setDT();
	gv->setMousePos(gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)));
	eventHandler(gv, gw, sm, nm, cw, minimap);

	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		if (gv->getGameState() == GameState::StartGame || gv->getGameState() == GameState::RestartGame || (enemiesVec.empty() && playerPtr->getIsAlive()))
		{
			restartGame(gv, sm);
			gv->setGameState(GameState::ContinueGame);
			return;
		}

		playerPtr->update(gv, gw, sm, nm);

		if (playerPtr->getIsAlive())
		{
			for (size_t i = 0; i < enemiesVec.size(); ++i) { enemiesVec[i]->update(gv, gw, sm, nm); }
			for (size_t i = 0; i < boxesVec.size(); ++i) { boxesVec[i]->update(gv, gw, sm, nm); }
			for (size_t i = 0; i < itemsVec.size(); ++i) { itemsVec[i]->update(gv, gw, sm, nm); }
			for (size_t i = 0; i < bulletsVec.size(); ++i) { bulletsVec[i]->update(gv, gw, sm, nm); }
		}
		else
		{
			for (size_t i = 0; i < enemiesVec.size(); ++i) { enemiesPool.returnToPool(enemiesVec, enemiesVec[i]); }
		}
	}
	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer() && nm->getIsConnected())
	{
		updateClients(gv, gw, sm, nm, minimap);
		updateBullets(gv, gw, sm, nm);
		updateServerIsNotAvailable(gv, gw, nm, cw);
	}
	else if (!gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { return; }

	updateGameInfo(gv, gw, sm);
	minimap.update(gv, gw);
}

void updateFPS(std::unique_ptr<GameVariable>& gv)
{
	gv->setFPSCurrentTime(gv->getFPSClockElapsedTime()); // assign the variable gv->fpsPreviousTime variable to elapsed time.
	gv->setFPS(floor(1.0f / (gv->getFPSCurrentTime() - gv->getFPSPreviousTime()))); // calculate fps.
	gv->setFPSPreviousTime(gv->getFPSCurrentTime()); // assign the variable gv->fpsPreviousTime to the current time.
}

void updateGameInfo(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm)
{
	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		if (playerPtr != nullptr) { sm->playerInfoText.setString(std::to_string(playerPtr->getGoldCoins())); }
		if (gv->getGameLanguage() == GameLanguage::English)
		{
			sm->gameInfoText.setString(
				"GAME INFO\nMouse X pos: " + std::to_string(gv->getMousePos().x) + "\nMouse Y pos: " + std::to_string(gv->getMousePos().y) +
				"\nNumber of enemies: " + std::to_string(enemiesVec.size()) +
				"\nNumber of boxes: " + std::to_string(boxesVec.size()) + "\nNumber of bullets: " + std::to_string(bulletsVec.size()) +
				"\nNumber of walls: " + std::to_string(wallsVec.size()) + "\nNumber of items: " + std::to_string(itemsVec.size()) +
				"\nFPS: " + std::to_string(static_cast<int>(gv->getFPS())));

			if (playerPtr != nullptr)
			{
				sm->playerAmmoText.setString("Ammo: " + std::to_string(playerPtr->getCurrentAmmo()) + "/" + std::to_string(playerPtr->getMaxAmmo()));
			}
		}
		else if (gv->getGameLanguage() == GameLanguage::Russian)
		{
			sm->gameInfoText.setString(
				L"ИГРОВАЯ ИНФОРМАЦИЯ\nПозиция мыши X: " + std::to_wstring(gv->getMousePos().x) + L"\nПозиция мыши Y: " + std::to_wstring(gv->getMousePos().y) +
				L"\nКоличество врагов: " + std::to_wstring(enemiesVec.size()) +
				L"\nКоличество коробок: " + std::to_wstring(boxesVec.size()) + L"\nКоличество пуль: " + std::to_wstring(bulletsVec.size()) +
				L"\nКоличество стен: " + std::to_wstring(wallsVec.size()) + L"\nКоличество предметов: " + std::to_wstring(itemsVec.size()) +
				L"\nФПС: " + std::to_wstring(static_cast<int>(gv->getFPS())));

			if (playerPtr != nullptr)
			{
				sm->playerAmmoText.setString(L"Патроны: " + std::to_wstring(playerPtr->getCurrentAmmo()) + L"/" + std::to_wstring(playerPtr->getMaxAmmo()));
			}
		}

		sm->playerInfoText.setPosition(gw->getGameViewCenter().x + 600.f, gw->getGameViewCenter().y + 150.f);
		sm->playerAmmoText.setPosition(gw->getGameViewCenter().x + 500.f, gw->getGameViewCenter().y + 300.f);
		gv->goldCoinHUDSprite.setPosition(gw->getGameViewCenter().x + 500.f, gw->getGameViewCenter().y + 150.f);
	}

	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer())
	{
		if (gv->getGameLanguage() == GameLanguage::English)
		{
			sm->gameInfoText.setString(
				"GAME INFO\nMouse X pos: " + std::to_string(gv->getMousePos().x) + "\nMouse Y pos: " + std::to_string(gv->getMousePos().y) +
				"\nNumber of clients: " + std::to_string(clientsVec.size()) +
				"\nNumber of boxes: " + std::to_string(boxesVec.size()) + "\nNumber of bullets: " + std::to_string(bulletsVec.size()) +
				"\nNumber of walls: " + std::to_string(wallsVec.size()) + "\nNumber of items: " + std::to_string(itemsVec.size()) +
				"\nFPS: " + std::to_string(static_cast<int>(gv->getFPS())));
		}
		else if (gv->getGameLanguage() == GameLanguage::Russian)
		{
			sm->gameInfoText.setString(
				L"ИГРОВАЯ ИНФОРМАЦИЯ\nПозиция мыши X: " + std::to_wstring(gv->getMousePos().x) + L"\nПозиция мыши Y: " + std::to_wstring(gv->getMousePos().y) +
				L"\nКоличество клиентов: " + std::to_wstring(clientsVec.size()) +
				L"\nКоличество коробок: " + std::to_wstring(boxesVec.size()) + L"\nКоличество пуль: " + std::to_wstring(bulletsVec.size()) +
				L"\nКоличество стен: " + std::to_wstring(wallsVec.size()) + L"\nКоличество предметов: " + std::to_wstring(itemsVec.size()) +
				L"\nФПС: " + std::to_wstring(static_cast<int>(gv->getFPS())));
		}
	}

	sm->gameInfoText.setPosition(gw->getGameViewCenter().x - 600.f, gw->getGameViewCenter().y - 350.f);
}

void drawGameInfo(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm)
{
	if (gv->getShowLogs()) { gw->window.draw(sm->gameInfoText); }
	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		gw->window.draw(gv->goldCoinHUDSprite);
		gw->window.draw(sm->playerInfoText);
		gw->window.draw(sm->playerAmmoText);
	}
}

void drawMinimapView(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, Minimap& minimap)
{
	if (!gv->getShowMinimap()) { return; }

	nm->setIsMinimapView(true);
	minimap.setView(gw);

	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		for (size_t i = 0; i < boxesVec.size(); ++i) { boxesVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < wallsVec.size(); ++i) { wallsVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < enemiesVec.size(); ++i) { enemiesVec[i]->draw(gv, gw, sm, nm); }
		playerPtr->draw(gv, gw, sm, nm);
	}

	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer())
	{
		drawClients(gv, gw, sm, nm);
		drawWalls(gv, gw, sm, nm);
	}

	nm->setIsMinimapView(false);
	gw->setGameView();
}

void drawGameView(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, Minimap& minimap)
{
	gw->setGameView();

	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer())
	{
		for (size_t i = 0; i < wallsVec.size(); ++i) { wallsVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < boxesVec.size(); ++i) { boxesVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < itemsVec.size(); ++i) { itemsVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < bulletsVec.size(); ++i) { bulletsVec[i]->draw(gv, gw, sm, nm); }
		for (size_t i = 0; i < enemiesVec.size(); ++i) { enemiesVec[i]->draw(gv, gw, sm, nm); }
		playerPtr->draw(gv, gw, sm, nm);
	}

	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer())
	{
		drawClients(gv, gw, sm, nm);
		drawBullets(gv, gw, sm, nm);
		drawWalls(gv, gw, sm, nm);
		drawServerIsNotAvailable(gv, gw, nm);
	}

	minimap.draw(gv, gw);
}

void drawGame(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	gw->window.clear(gv->backgroundColor);

	drawGameView(gv, gw, sm, nm, minimap);
	drawMinimapView(gv, gw, sm, nm, minimap);
	drawGameInfo(gv, gw, sm);

	if (gv->getIsSingleplayer() && !gv->getIsMultiplayer() && !playerPtr->getIsAlive())
	{
		gw->window.clear(gv->backgroundColor);
		drawGameResult(gv, gw, sm);
		gw->window.display();
		return;
	}
	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer() && nm->getIsConnected()) { cw->drawGameGUI(); }
	else if (!gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { return; }

	gw->window.display();
}