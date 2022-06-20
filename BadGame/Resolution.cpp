#include "Resolution.h"

void graphicsSettingsMenuUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	if (gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(800.f, 200.f), L"1366x768", 50, "HDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(1120.f, 200.f), L"1920x1080", 50, "fullHDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 450.f), L"WINDOWED", 50, "windowedModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 450.f), L"FULLSCREEN", 50, "fullscreenModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 700.f), L"English", 50, "engLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 700.f), L"–ÛÒÒÍËÈ", 50, "rusLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 915.f), L"BACK", 43, "backButton", true));

			gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(960.f, 100.f), 70, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(960.f, 350.f), 70, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(960.f, 600.f), 70, "selectLanguageLabel"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(800.f, 200.f), L"1366x768", 50, "HDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(1120.f, 200.f), L"1920x1080", 50, "fullHDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 450.f), L"Œ ŒÕÕ€…", 50, "windowedModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 450.f), L"œŒÀÕŒ› –¿ÕÕ€…", 50, "fullscreenModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 700.f), L"English", 50, "engLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 700.f), L"–ÛÒÒÍËÈ", 50, "rusLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 915.f), L"Õ¿«¿ƒ", 43, "backButton", true));

			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ –¿«–≈ÿ≈Õ»≈ › –¿Õ¿", sf::Vector2f(960.f, 100.f), 70, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ —“»À‹ Œ Õ¿", sf::Vector2f(960.f, 350.f), 70, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ ﬂ«€ ", sf::Vector2f(960.f, 600.f), 70, "selectLanguageLabel"));
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(553.f, 150.f), L"1366x768", 35, "HDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(813.f, 150.f), L"1920x1080", 35, "fullHDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 350.f), L"WINDOWED", 35, "windowedModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 350.f), L"FULLSCREEN", 35, "fullscreenModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 550.f), L"English", 35, "engLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 550.f), L"–ÛÒÒÍËÈ", 35, "rusLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 700.f), L"BACK", 43, "backButton", true));

			gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(683.f, 80.f), 51, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(683.f, 280.f), 51, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(683.f, 480.f), 51, "selectLanguageLabel"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(553.f, 150.f), L"1366x768", 35, "HDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(813.f, 150.f), L"1920x1080", 35, "fullHDResolutionButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 350.f), L"Œ ŒÕÕ€…", 35, "windowedModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 350.f), L"œŒÀÕŒ› –¿ÕÕ€…", 35, "fullscreenModeButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 550.f), L"English", 35, "engLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 550.f), L"–ÛÒÒÍËÈ", 35, "rusLangButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 700.f), L"Õ¿«¿ƒ", 43, "backButton", true));

			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ –¿«–≈ÿ≈Õ»≈ › –¿Õ¿", sf::Vector2f(683.f, 80.f), 51, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ —“»À‹ Œ Õ¿", sf::Vector2f(683.f, 280.f), 51, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"¬€¡≈–»“≈ ﬂ«€ ", sf::Vector2f(683.f, 480.f), 51, "selectLanguageLabel"));
		}
	}
}

void settingsMenuUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	if (gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(960.f, 450.f), L"GRAPHICS\nSETTINGS", 43, "graphicsSettingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 590.f), L"BACK", 43, "backButton", true));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(960.f, 450.f), L"Õ¿—“–Œ… »\n √–¿‘» »", 43, "graphicsSettingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 590.f), L"Õ¿«¿ƒ", 43, "backButton", true));
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(683.f, 350.f), L"GRAPHICS\nSETTINGS", 43, "graphicsSettingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 490.f), L"BACK", 43, "backButton", true));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(683.f, 350.f), L"Õ¿—“–Œ… »\n √–¿‘» »", 43, "graphicsSettingsButton", true));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 490.f), L"Õ¿«¿ƒ", 43, "backButton", true));
		}
	}
}

void mainMenuUpdate(GameVariables* gv, Entity*& player)
{
	gv->buttonsVec.clear();
	if (gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080)
	{
		if (gv->gameLanguage == 'e')
		{
			if (gv->isGameStarted == false)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"SINGLEPLAYER", 43, "singlePlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"MULTIPLAYER", 43, "multiPlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"SETTINGS", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 735.f), L"EXIT", 43, "exitButton", true));
			}
			else if (gv->isGameStarted == true)
			{
				if (player == nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"RESTART", 43, "restartGameButton", true));
				}
				else if (player != nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"CONTINUE", 43, "continueButton", true));
				}
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"BACK TO MENU", 43, "backToMenuButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"SETTINGS", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 735.f), L"EXIT", 43, "exitButton", true));

			}
		}
		else if (gv->gameLanguage == 'r')
		{
			if (gv->isGameStarted == false)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"Œƒ»ÕŒ◊Õ¿ﬂ »√–¿", 43, "singlePlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"—≈“≈¬¿ﬂ »√–¿", 43, "multiPlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"Õ¿—“–Œ… »", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 735.f), L"¬€’Œƒ", 43, "exitButton", true));
			}
			else if (gv->isGameStarted == true)
			{
				if (player == nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"œ≈–≈«¿œ”— ", 43, "restartGameButton", true));
				}
				else if (player != nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"œ–ŒƒŒÀ∆»“‹", 43, "continueButton", true));
				}
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"Õ¿«¿ƒ ¬ Ã≈Õﬁ", 43, "backToMenuButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"Õ¿—“–Œ… »", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 735.f), L"¬€’Œƒ", 43, "exitButton", true));
			}
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			if (gv->isGameStarted == false)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"SINGLEPLAYER", 43, "singlePlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"MULTIPLAYER", 43, "multiPlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"SETTINGS", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 585.f), L"EXIT", 43, "exitButton", true));
			}
			else if (gv->isGameStarted == true)
			{
				if (player == nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"RESTART", 43, "restartGameButton", true));
				}
				else if (player != nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"CONTINUE", 43, "continueButton", true));
				}
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"BACK TO MENU", 43, "backToMenuButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"SETTINGS", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 585.f), L"EXIT", 43, "exitButton", true));
			}
		}
		else if (gv->gameLanguage == 'r')
		{
			if (gv->isGameStarted == false)
			{
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"Œƒ»ÕŒ◊Õ¿ﬂ »√–¿", 43, "singlePlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"—≈“≈¬¿ﬂ »√–¿", 43, "multiPlayerButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"Õ¿—“–Œ… »", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 585.f), L"¬€’Œƒ", 43, "exitButton", true));
			}
			else if (gv->isGameStarted == true)
			{
				if (player == nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"œ≈–≈«¿œ”— ", 43, "restartGameButton", true));
				}
				else if (player != nullptr)
				{
					gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"œ–ŒƒŒÀ∆»“‹", 43, "continueButton", true));
				}
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"Õ¿«¿ƒ ¬ Ã≈Õﬁ", 43, "backToMenuButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"Õ¿—“–Œ… »", 43, "settingsButton", true));
				gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 585.f), L"¬€’Œƒ", 43, "exitButton", true));
			}
		}
	}
}

void authorizationUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	float halfWinSizeX = gv->window.getSize().x / 2.f;

	if (gv->gameLanguage == 'e')
	{
		gv->labelsVec.emplace_back(new Label(L"ENTER YOUR NICKNAME", sf::Vector2f(halfWinSizeX, 100.f), 50, "enterYourNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, 250.f), L"", 45, "nicknameFieldButton", false));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX - 100.f, 400.f), L"Enter", 40, "enterButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX + 100.f, 400.f), L"Exit", 40, "exitButton", true));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(100.f, 40.f), sf::Vector2f(500.f, 500.f), L"English", 20, "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(100.f, 40.f), sf::Vector2f(500.f, 550.f), L"–ÛÒÒÍËÈ", 20, "rusLangButton", true));
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ —¬Œ… Õ» Õ≈…Ã", sf::Vector2f(halfWinSizeX, 100.f), 50, "enterYourNicknameLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, 250.f), L"", 45, "nicknameFieldButton", false));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX - 100.f, 400.f), L"¬ÓÈÚË", 40, "enterButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX + 100.f, 400.f), L"¬˚ıÓ‰", 40, "exitButton", true));
		gv->buttonsVec.back()->getText().setPosition(gv->buttonsVec.back()->getText().getPosition().x, gv->buttonsVec.back()->getText().getPosition().y + 3.f);

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(100.f, 40.f), sf::Vector2f(500.f, 500.f), L"English", 20, "engLangButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(100.f, 40.f), sf::Vector2f(500.f, 550.f), L"–ÛÒÒÍËÈ", 20, "rusLangButton", true));
	}
}

void multiplayerMenuUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;

	if (gv->gameLanguage == 'e')
	{
		gv->labelsVec.emplace_back(new Label(L"ENTER IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - 160.f), 50, "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, halfWinSizeY - 100.f), L"", 45, "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"ENTER PORT", sf::Vector2f(halfWinSizeX, halfWinSizeY - 10.f), 50, "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, halfWinSizeY + 50.f), L"", 45, "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX - 100.f, halfWinSizeY + 150.f), L"Connect", 30, "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX + 100.f, halfWinSizeY + 150.f), L"Back", 30, "backButton", true));
	}
	else if (gv->gameLanguage == 'r')
	{
		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ IP", sf::Vector2f(halfWinSizeX, halfWinSizeY - 160.f), 50, "enterIPLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, halfWinSizeY - 100.f), L"", 45, "ipFieldButton", false));

		gv->labelsVec.emplace_back(new Label(L"¬¬≈ƒ»“≈ œŒ–“", sf::Vector2f(halfWinSizeX, halfWinSizeY - 10.f), 50, "enterPortLabel"));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 50.f), sf::Vector2f(halfWinSizeX, halfWinSizeY + 50.f), L"", 45, "portFieldButton", false));

		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX - 100.f, halfWinSizeY + 150.f), L"¬ÓÈÚË", 30, "connectButton", true));
		gv->buttonsVec.emplace_back(new Button(sf::Vector2f(150.f, 50.f), sf::Vector2f(halfWinSizeX + 100.f, halfWinSizeY + 150.f), L"Õ‡Á‡‰", 30, "backButton", true));
	}
}