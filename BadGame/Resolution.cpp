#include "Resolution.h"

void graphicsSettingsMenuUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	gv->labelsVec.clear();
	if (gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(800.f, 200.f), L"1366x768", 50, "HDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(1120.f, 200.f), L"1920x1080", 50, "fullHDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 450.f), L"WINDOWED", 50, "windowedModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 450.f), L"FULLSCREEN", 50, "fullscreenModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 700.f), L"English", 50, "engLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 700.f), L"�������", 50, "rusLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 915.f), L"BACK", 43, "backButton"));

			gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(960.f, 100.f), 70, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(960.f, 350.f), 70, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(960.f, 600.f), 70, "selectLanguageLabel"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(800.f, 200.f), L"1366x768", 50, "HDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 100.f), sf::Vector2f(1120.f, 200.f), L"1920x1080", 50, "fullHDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 450.f), L"�������", 50, "windowedModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 450.f), L"�������������", 50, "fullscreenModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(750.f, 700.f), L"English", 50, "engLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(1170.f, 700.f), L"�������", 50, "rusLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 915.f), L"�����", 43, "backButton"));

			gv->labelsVec.emplace_back(new Label(L"�������� ���������� ������", sf::Vector2f(960.f, 100.f), 70, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"�������� ����� ����", sf::Vector2f(960.f, 350.f), 70, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"�������� ����", sf::Vector2f(960.f, 600.f), 70, "selectLanguageLabel"));
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(553.f, 150.f), L"1366x768", 35, "HDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(813.f, 150.f), L"1920x1080", 35, "fullHDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 350.f), L"WINDOWED", 35, "windowedModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 350.f), L"FULLSCREEN", 35, "fullscreenModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 550.f), L"English", 35, "engLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 550.f), L"�������", 35, "rusLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 700.f), L"BACK", 43, "backButton"));

			gv->labelsVec.emplace_back(new Label(L"SELECT RESOLUTION", sf::Vector2f(683.f, 80.f), 51, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT WINDOW STYLE", sf::Vector2f(683.f, 280.f), 51, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"SELECT LANGUAGE", sf::Vector2f(683.f, 480.f), 51, "selectLanguageLabel"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(553.f, 150.f), L"1366x768", 35, "HDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 70.f), sf::Vector2f(813.f, 150.f), L"1920x1080", 35, "fullHDResolutionButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 350.f), L"�������", 35, "windowedModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 350.f), L"�������������", 35, "fullscreenModeButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(503.f, 550.f), L"English", 35, "engLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 70.f), sf::Vector2f(863.f, 550.f), L"�������", 35, "rusLangButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 700.f), L"�����", 43, "backButton"));

			gv->labelsVec.emplace_back(new Label(L"�������� ���������� ������", sf::Vector2f(683.f, 80.f), 51, "selectResolutionLabel"));
			gv->labelsVec.emplace_back(new Label(L"�������� ����� ����", sf::Vector2f(683.f, 280.f), 51, "selectWindowStyleLabel"));
			gv->labelsVec.emplace_back(new Label(L"�������� ����", sf::Vector2f(683.f, 480.f), 51, "selectLanguageLabel"));
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
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(960.f, 450.f), L"GRAPHICS\nSETTINGS", 43, "graphicsSettingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 590.f), L"BACK", 43, "backButton"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(960.f, 450.f), L"���������\n �������", 43, "graphicsSettingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(960.f, 590.f), L"�����", 43, "backButton"));
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(683.f, 350.f), L"GRAPHICS\nSETTINGS", 43, "graphicsSettingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 490.f), L"BACK", 43, "backButton"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(300.f, 150.f), sf::Vector2f(683.f, 350.f), L"���������\n �������", 43, "graphicsSettingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(200.f, 100.f), sf::Vector2f(683.f, 490.f), L"�����", 43, "backButton"));
		}
	}
}

void mainMenuUpdate(GameVariables* gv)
{
	gv->buttonsVec.clear();
	if (gv->window.getSize().x == 1920 && gv->window.getSize().y == 1080)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"START", 43, "startButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"SETTINGS", 43, "settingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"EXIT", 43, "exitButton"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 420.f), L"������", 43, "startButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 525.f), L"���������", 43, "settingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(960.f, 630.f), L"�����", 43, "exitButton"));
		}
	}
	else if (gv->window.getSize().x == 1366 && gv->window.getSize().y == 768)
	{
		if (gv->gameLanguage == 'e')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"START", 43, "startButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"SETTINGS", 43, "settingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"EXIT", 43, "exitButton"));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 270.f), L"������", 43, "startButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 375.f), L"���������", 43, "settingsButton"));
			gv->buttonsVec.emplace_back(new Button(sf::Vector2f(400.f, 100.f), sf::Vector2f(683.f, 480.f), L"�����", 43, "exitButton"));
		}
	}
}