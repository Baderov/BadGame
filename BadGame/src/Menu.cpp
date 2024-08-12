#include "pch.h"
#include "Menu.h"

void errorChecking(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	nm->setCountOfDotsInIP(0);

	for (size_t i = 0; i < nm->getServerIP().size(); ++i)
	{
		if (nm->getServerIP()[i] == '.') { nm->setCountOfDotsInIP(nm->getCountOfDotsInIP() + 1); }
	}

	if ((nm->getNickname().size() >= 3 && multiplayerMenuError == MultiplayerMenuErrors::NickMustContainMoreChars) ||
		(nm->getCountOfDotsInIP() == 3 && multiplayerMenuError == MultiplayerMenuErrors::WrongIP) ||
		(nm->getTempPort().size() >= 1 && multiplayerMenuError == MultiplayerMenuErrors::WrongPort))
	{
		multiplayerMenuError = MultiplayerMenuErrors::NoErrors;
	}

	switch (multiplayerMenuError)
	{
	case MultiplayerMenuErrors::NickMustContainMoreChars:
		if (gv->getGameLanguage() == GameLanguage::English) { cw->setErrorLabelText(L"Nickname must contain more than 2 characters!"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { cw->setErrorLabelText(L"Никнейм должен содержать более 2 символов!"); }
		break;
	case MultiplayerMenuErrors::ServerIsNotAvailable:
		if (gv->getGameLanguage() == GameLanguage::English) { cw->setErrorLabelText(L"Server is not available!"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { cw->setErrorLabelText(L"Сервер недоступен!"); }
		break;
	case MultiplayerMenuErrors::NicknameIsAlreadyTaken:
		if (gv->getGameLanguage() == GameLanguage::English) { cw->setErrorLabelText(L"Nickname is already taken!"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { cw->setErrorLabelText(L"Никнейм уже занят!"); }
		break;
	case MultiplayerMenuErrors::WrongIP:
		if (gv->getGameLanguage() == GameLanguage::English) { cw->setErrorLabelText(L"The number of dots in the IP address must be 3!"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { cw->setErrorLabelText(L"В IP адресе должно быть 3 точки!"); }
		break;
	case MultiplayerMenuErrors::WrongPort:
		if (gv->getGameLanguage() == GameLanguage::English) { cw->setErrorLabelText(L"Enter port!"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { cw->setErrorLabelText(L"Введите порт"); }
		break;
	case MultiplayerMenuErrors::NoErrors:
		cw->setErrorLabelText(L"");
		break;
	}
}

void updateFields(std::unique_ptr<NetworkManager>& nm)
{
	nm->setNickname(L"Baderov");
	nm->setServerIP(sf::IpAddress::getLocalAddress().toString());
	nm->setTempPort("2000");
	nm->setServerPort(2000);
}

void updateMenu(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	switch (menuType)
	{
	case MenuType::MainMenu:
		menuUpdate(gv, gw, sm, cw);
		break;
	case MenuType::GameMenu:
		menuUpdate(gv, gw, sm, cw);
		break;
	case MenuType::MultiplayerMenu:
		multiplayerMenuUpdate(gv, gw, nm, cw);
		break;
	case MenuType::SettingsMenu:
		settingsMenuUpdate(gv, gw, cw);
		break;
	case MenuType::GraphicsSettingsMenu:
		graphicsSettingsMenuUpdate(gv, gw, nm, cw, minimap);
		break;
	}
	menuAction = MenuAction::Nothing;
}

void openMenu(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	//std::cout << "START" << std::endl;
	updateFields(nm);
	updateMenu(gv, gw, sm, nm, cw, minimap);

	while (gw->window.isOpen())
	{
		if (menuAction != MenuAction::Nothing) { return; }

		sf::Event event;
		gv->setMousePos(gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)));

		if (menuType == MenuType::MultiplayerMenu)
		{
			if (gv->getIsMultiplayer() && !nm->getConnectsToServer()) { menuAction = MenuAction::StartGame; }
			if (nm->getConnectsToServer()) { cw->disableMultiplayerMenuWidgets(); }
			else { cw->enableMultiplayerMenuWidgets(); }
			errorChecking(gv, gw, sm, nm, cw);
		}

		while (gw->window.pollEvent(event))
		{
			cw->menuGUI.handleEvent(event);
			if (event.type == sf::Event::Closed) { gv->setIsSingleplayer(false); gv->setIsMultiplayer(false); gw->window.close(); /*std::cout << "END 1" << std::endl;*/ return; }
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape && menuType != MenuType::MainMenu)
			{
				switch (menuType)
				{
				case MenuType::GameMenu:
					if (gv->getIsSingleplayer() || gv->getIsMultiplayer()) { menuAction = MenuAction::ContinueGame; }
					break;

				case MenuType::MultiplayerMenu:
					if (cw->connectButtonIsEnabled()) { menuAction = MenuAction::OpenMainMenu; }
					break;

				case MenuType::SettingsMenu:
					if (gv->getGameState() == GameState::GameMenu) { menuAction = MenuAction::OpenGameMenu; }
					else if (gv->getGameState() == GameState::MainMenu) { menuAction = MenuAction::OpenMainMenu; }
					else if (gv->getGameState() == GameState::GameResult) { menuAction = MenuAction::OpenGameMenu; }
					break;

				case MenuType::GraphicsSettingsMenu:
					menuAction = MenuAction::OpenSettingsMenu;
					break;
				}
			}

			if (menuType == MenuType::MultiplayerMenu && cw->connectButtonIsEnabled() && !nm->getConnectsToServer() && nm->getConnectButtonPressed())
			{
				nm->setConnectButtonPressed(false);
				multiplayerMenuError = MultiplayerMenuErrors::NoErrors;
				if (nm->getNickname().size() < 3) { multiplayerMenuError = MultiplayerMenuErrors::NickMustContainMoreChars; break; }
				if (nm->getCountOfDotsInIP() != 3) { multiplayerMenuError = MultiplayerMenuErrors::WrongIP; break; }
				if (nm->getTempPort().size() < 1) { multiplayerMenuError = MultiplayerMenuErrors::WrongPort; break; }

				clientsPool.returnEverythingToPool(clientsVec);
				bulletsPool.returnEverythingToPool(bulletsVec);
				gv->setIsSingleplayer(false);
				nm->resetVariables();
				nm->setConnectsToServer(true);
			}
		}

		gw->window.clear(sf::Color::Black);
		cw->menuGUI.draw();
		gw->window.display();
	}

	//std::cout << "END 3" << std::endl;
}

void menuEventHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap, MenuType _menuType)
{
	gw->setMenuView();
	menuType = std::move(_menuType);
	openMenu(gv, gw, sm, nm, cw, minimap);

	while (gw->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;

		sf::Event event;
		while (gw->window.pollEvent(event)) { if (event.type == sf::Event::Closed) { gv->setIsSingleplayer(false); gv->setIsMultiplayer(false); gw->window.close(); return; } }

		cw->menuGUI.removeAllWidgets();

		switch (menuAction)
		{
		case MenuAction::StartGame:
			gv->setGameState(GameState::StartGame);
			if (!gv->getIsMultiplayer()) { gv->setIsSingleplayer(true); }
			return;

		case MenuAction::RestartGame:
			gv->setGameState(GameState::RestartGame);
			return;

		case MenuAction::ContinueGame:
			gv->setGameState(GameState::ContinueGame);
			return;

		case MenuAction::ExitGame:
			gv->setGameState(GameState::GameOver);
			return;

		case MenuAction::OpenSettingsMenu:
			menuType = MenuType::SettingsMenu;
			openMenu(gv, gw, sm, nm, cw, minimap);
			break;

		case MenuAction::OpenGraphicsSettingsMenu:
			menuType = MenuType::GraphicsSettingsMenu;
			openMenu(gv, gw, sm, nm, cw, minimap);
			break;

		case MenuAction::OpenMainMenu:
			if (gv->getIsSingleplayer()) { gv->setIsSingleplayer(false); }
			else if (gv->getIsMultiplayer()) { gv->setIsMultiplayer(false); }
			gv->setGameState(GameState::MainMenu);
			menuType = MenuType::MainMenu;
			openMenu(gv, gw, sm, nm, cw, minimap);
			break;

		case MenuAction::OpenGameMenu:
			menuType = MenuType::GameMenu;
			openMenu(gv, gw, sm, nm, cw, minimap);
			break;

		case MenuAction::OpenMultiplayerMenu:
			menuType = MenuType::MultiplayerMenu;
			openMenu(gv, gw, sm, nm, cw, minimap);
			break;
		}
	}
}