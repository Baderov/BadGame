#include "pch.h"
#include "Menu.h" // header file for working with the menu.

void errorChecking(std::unique_ptr<GameVariable>& gv, int& countOfDotsInIP) // error checking function.
{
	auto errorLabel = gv->gui.get<tgui::Label>("errorLabel");
	countOfDotsInIP = 0;

	for (int i = 0; i < gv->getServerIP().size(); ++i)
	{
		if (gv->getServerIP()[i] == '.') { countOfDotsInIP++; }
	}

	if ((gv->getNickname().size() >= 3 && multiplayerError == MultiplayerErrors::NickMustContainMoreChars) ||
		(countOfDotsInIP == 3 && multiplayerError == MultiplayerErrors::WrongIP) ||
		(gv->getTempPort().size() >= 1 && multiplayerError == MultiplayerErrors::WrongPort))
	{
		multiplayerError = MultiplayerErrors::NoErrors;
	}

	switch (multiplayerError)
	{
	case MultiplayerErrors::NickMustContainMoreChars:
		if (gv->getGameLanguage() == 'e') { errorLabel->setText(L"Nickname must contain more than 2 characters!"); }
		else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L"Никнейм должен содержать более 2 символов!"); }
		break;
	case MultiplayerErrors::ServerIsNotAvailable:
		if (gv->getGameLanguage() == 'e') { errorLabel->setText(L"Server is not available!"); }
		else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L"Сервер недоступен!"); }
		break;
	case MultiplayerErrors::NicknameIsAlreadyTaken:
		if (gv->getGameLanguage() == 'e') { errorLabel->setText(L"Nickname is already taken!"); }
		else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L"Никнейм уже занят!"); }
		break;
	case MultiplayerErrors::WrongIP:
		if (gv->getGameLanguage() == 'e') { errorLabel->setText(L"The number of dots in the IP address must be 3!"); }
		else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L"В IP адресе должно быть 3 точки!"); }
		break;
	case MultiplayerErrors::WrongPort:
		if (gv->getGameLanguage() == 'e') { errorLabel->setText(L"Enter port!"); }
		else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L"Введите порт"); }
		break;
	case MultiplayerErrors::NoErrors:
		errorLabel->setText(L"");
		break;
	}
}

void updateFields(std::unique_ptr<GameVariable>& gv) // function for update fields in multiplayer menu.
{
	gv->setNickname(L"Baderov");
	gv->setServerIP(sf::IpAddress::getLocalAddress().toString());
	gv->setTempPort("2000");
	gv->setServerPort(2000);
}

void multiplayerMenu(std::unique_ptr<GameVariable>& gv, PlayersList& playersList, Chat& chat) // multiplayer menu function.
{
	updateFields(gv);
	multiplayerMenuUpdate(gv);
	gv->setMenuNum(0);
	multiplayerError = MultiplayerErrors::NoErrors;
	int countOfDotsInIP = 0;

	auto nicknameEditBox = gv->gui.get<tgui::EditBox>("nicknameEditBox");
	auto IPEditBox = gv->gui.get<tgui::EditBox>("IPEditBox");
	auto portEditBox = gv->gui.get<tgui::EditBox>("portEditBox");
	auto connectButton = gv->gui.get<tgui::Button>("connectButton");
	auto backButton = gv->gui.get<tgui::Button>("backButton");

	while (gv->window.isOpen())
	{
		if (gv->getMenuNum() > 0) { return; }

		DEBUG_SET_FUNC_NAME;

		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.

		if (gv->getIsMultiplayer() && !gv->getConnectsToServer())
		{
			gv->setMenuNum(9);
			return;
		}

		if (gv->getConnectsToServer())
		{
			connectButton->setEnabled(false);
			backButton->setEnabled(false);
			nicknameEditBox->setEnabled(false);
			IPEditBox->setEnabled(false);
			portEditBox->setEnabled(false);
		}
		else
		{
			connectButton->setEnabled(true);
			backButton->setEnabled(true);
			nicknameEditBox->setEnabled(true);
			IPEditBox->setEnabled(true);
			portEditBox->setEnabled(true);
		}

		errorChecking(gv, countOfDotsInIP);
		while (gv->window.pollEvent(gv->event))
		{
			gv->gui.handleEvent(gv->event);
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape && connectButton->isEnabled())
			{
				gv->setMenuNum(5);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; }

			if (connectButton->isEnabled() && !gv->getConnectsToServer() && gv->getConnectButtonPressed())
			{
				gv->setConnectButtonPressed(false);
				multiplayerError = MultiplayerErrors::NoErrors;
				if (gv->getNickname().size() < 3) { multiplayerError = MultiplayerErrors::NickMustContainMoreChars; break; }
				if (countOfDotsInIP != 3) { multiplayerError = MultiplayerErrors::WrongIP; break; }
				if (gv->getTempPort().size() < 1) { multiplayerError = MultiplayerErrors::WrongPort; break; }

				clientPool.returnEverythingToPool(clientVec);
				bulletPool.returnEverythingToPool(bulletVec);
				gv->serverClock.restart();
				gv->setIsMultiplayer(true);
				resetVariables(gv, chat, playersList);
				gv->setConnectsToServer(true);
			}
		}
		gv->window.clear(sf::Color::Black);
		gv->gui.draw();
		gv->window.display();
	}
}

void graphicsSettingsMenu(std::unique_ptr<GameVariable>& gv, Minimap& minimap) // graphics settings menu function.
{
	graphicsSettingsMenuUpdate(gv, minimap);
	gv->setMenuNum(0);
	while (gv->window.isOpen())
	{
		if (gv->getMenuNum() > 0) { return; }
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.

		while (gv->window.pollEvent(gv->event))
		{
			gv->gui.handleEvent(gv->event);
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape) // если отпустили кнопку Escape.
			{
				gv->setMenuNum(6);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; }
		}
		gv->window.clear(sf::Color::Black);
		gv->gui.draw();
		gv->window.display();
	}
}

void settingsMenu(std::unique_ptr<GameVariable>& gv) // settings menu function.
{
	settingsMenuUpdate(gv);
	gv->setMenuNum(0);
	while (gv->window.isOpen())
	{
		if (gv->getMenuNum() > 0) { return; }
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		while (gv->window.pollEvent(gv->event))
		{
			gv->gui.handleEvent(gv->event);
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape)
			{
				gv->setMenuNum(5);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; }
		}
		gv->window.clear(sf::Color::Black);
		gv->gui.draw();
		gv->window.display();
	}
}

void mainMenu(std::unique_ptr<GameVariable>& gv) // main menu function.
{
	mainMenuUpdate(gv);
	gv->setMenuNum(0);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.
		if (gv->getMenuNum() > 0) { return; }
		while (gv->window.pollEvent(gv->event))
		{
			gv->gui.handleEvent(gv->event);
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape && (gv->getIsSingleplayer() || gv->getIsMultiplayer()))
			{
				gv->setMenuNum(9);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; }
		}
		gv->window.clear(sf::Color::Black);
		gv->gui.draw();
		gv->window.display();
	}
}

void menuEventHandler(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // function to handle menu events.
{
	gv->setMenuView();
	mainMenu(gv);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;

		while (gv->window.pollEvent(gv->event)) { if (gv->event.type == sf::Event::Closed) { gv->window.close(); } }
		gv->gui.removeAllWidgets();
		switch (gv->getMenuNum())
		{
		case 1:
			gv->setMenuNum(0);
			gv->setRestartGame(true);
			gv->setIsSingleplayer(true);
			return;
		case 2:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 3:
			gv->setMenuNum(0);
			gv->setIsSingleplayer(false);
			gv->setIsMultiplayer(false);
			gv->window.close();
			return;
		case 4:
			gv->setMenuNum(0);
			graphicsSettingsMenu(gv, minimap);
			break;
		case 5:
			gv->setMenuNum(0);
			mainMenu(gv);
			break;
		case 6:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 7:
			gv->setMenuNum(0);
			if (gv->getIsSingleplayer()) { gv->setIsSingleplayer(false); }
			if (gv->getIsMultiplayer()) { gv->setIsMultiplayer(false); }
			return;
		case 8:
			gv->setMenuNum(0);
			multiplayerMenu(gv, playersList, chat);
			break;
		case 9:
			gv->setMenuNum(0);
			return;
		}
	}
}