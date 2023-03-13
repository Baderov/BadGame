#include "Menu.h" // header file for working with the menu.
#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::wcout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

void errorChecking(GameVariable* gv, int& countOfDotsInIP) // error checking function.
{
	auto errorLabel = gv->gui.get<tgui::Label>("errorLabel");
	countOfDotsInIP = 0;

	for (int i = 0; i < gv->getServerIP().size(); i++)
	{
		if (gv->getServerIP()[i] == '.') { countOfDotsInIP++; }
	}

	if ((gv->getNickname().size() >= 3 && gv->multiplayerError == MultiplayerErrors::NickMustContainMoreChars) ||
		(countOfDotsInIP == 3 && gv->multiplayerError == MultiplayerErrors::WrongIP) || (gv->getTempPort().size() >= 1 && gv->multiplayerError == MultiplayerErrors::WrongPort))
	{
		gv->multiplayerError = MultiplayerErrors::NoErrors;
	}

	switch (gv->multiplayerError)
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

void updateFields(GameVariable* gv) // function for update fields in multiplayer menu.
{
	gv->setNickname(L"Baderov");
	gv->setServerIP(sf::IpAddress::getLocalAddress().toString());
	gv->setTempPort("2000");
	gv->setServerPort(2000);
}

void multiplayerMenu(GameVariable* gv) // multiplayer menu function.
{
	updateFields(gv);
	multiplayerMenuUpdate(gv);
	gv->setMenuNum(0);
	gv->multiplayerError = MultiplayerErrors::NoErrors;
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
		if (gv->getMultiPlayerGame() == true && gv->getConnectsToServer() == false)
		{
			gv->setMenuNum(9);
			return;
		}

		if (gv->getConnectsToServer() == true)
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
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape && connectButton->isEnabled() == true)
			{
				gv->setMenuNum(5);
				return;
			}
			if (gv->event.type == sf::Event::Closed) { gv->window.close(); return; }

			if (connectButton->isEnabled() == true && gv->getConnectsToServer() == false && gv->getConnectButtonPressed() == true)
			{
				gv->setConnectButtonPressed(false);
				gv->multiplayerError = MultiplayerErrors::NoErrors;
				if (gv->getNickname().size() < 3) { gv->multiplayerError = MultiplayerErrors::NickMustContainMoreChars; break; }
				if (countOfDotsInIP != 3) { gv->multiplayerError = MultiplayerErrors::WrongIP; break; }
				if (gv->getTempPort().size() < 1) { gv->multiplayerError = MultiplayerErrors::WrongPort; break; }
				gv->setMultiPlayerGame(true);
				m_resetVariables(gv);
				gv->restartServerClock();
				std::thread recvThread([&]() { receiveData(gv); });
				std::thread sendThread([&]() { sendData(gv); });
				recvThread.detach();
				sendThread.detach();
				std::thread connectionThread([&]() { startNetwork(gv); });
				connectionThread.detach();
			}
		}
		gv->window.clear(sf::Color::Black);
		gv->gui.draw();
		gv->window.display();
	}
}

void graphicsSettingsMenu(GameVariable* gv, Minimap& minimap) // graphics settings menu function.
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

void settingsMenu(GameVariable* gv) // settings menu function.
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

void mainMenu(GameVariable* gv) // main menu function.
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
			if (gv->event.type == sf::Event::KeyReleased && gv->event.key.code == sf::Keyboard::Escape && (gv->getSinglePlayerGame() == true || gv->getMultiPlayerGame() == true))
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

void menuEventHandler(GameVariable* gv, Minimap& minimap) // function to handle menu events.
{
	gv->setWindowView(gv->getMenuView());
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
			gv->setSinglePlayerGame(true);
			return;
		case 2:
			gv->setMenuNum(0);
			settingsMenu(gv);
			break;
		case 3:
			gv->setMenuNum(0);
			gv->setSinglePlayerGame(false);
			gv->setMultiPlayerGame(false);
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
			if (gv->getSinglePlayerGame() == true) { gv->setSinglePlayerGame(false); }
			if (gv->getMultiPlayerGame() == true) { gv->setMultiPlayerGame(false); }
			return;
		case 8:
			gv->setMenuNum(0);
			multiplayerMenu(gv);
			break;
		case 9:
			gv->setMenuNum(0);
			return;
		}
	}
}