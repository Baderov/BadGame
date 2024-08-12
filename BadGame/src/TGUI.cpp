#include "pch.h"
#include "TGUI.h"

void widgetStateHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw)
{
	std::string tempResolution = "", width = "", height = "";

	auto resolutionComboBox = cw->menuGUI.get<tgui::ComboBox>("resolutionComboBox");
	auto languageComboBox = cw->menuGUI.get<tgui::ComboBox>("languageComboBox");
	auto fpsComboBox = cw->menuGUI.get<tgui::ComboBox>("fpsComboBox");
	auto fullscreenCheckBox = cw->menuGUI.get<tgui::CheckBox>("fullscreenCheckBox");
	auto vsyncCheckBox = cw->menuGUI.get<tgui::CheckBox>("vsyncCheckBox");

	switch (widgetState)
	{
	case WidgetState::ResolutionComboBoxChanged:
		menuAction = MenuAction::Nothing;
		tempResolution = resolutionComboBox->getSelectedItem().trim().toStdString();
		width = tempResolution.substr(0, tempResolution.find('x'));
		height = tempResolution.substr(tempResolution.find('x') + 1, tempResolution.size());
		cw->setTempWindowSize(sf::Vector2u(std::atoi(width.c_str()), std::atoi(height.c_str())));
		break;

	case WidgetState::LanguageComboBoxChanged:
		if (languageComboBox->getSelectedItemId() == "0") { cw->setTempGameLanguage(GameLanguage::English); }
		else if (languageComboBox->getSelectedItemId() == "1") { cw->setTempGameLanguage(GameLanguage::Russian); }
		break;

	case WidgetState::FPSComboBoxChanged:
		if (fpsComboBox->getSelectedItemId() == "0") { cw->setTempFPSLimiter(60); }
		else if (fpsComboBox->getSelectedItemId() == "1") { cw->setTempFPSLimiter(75); }
		else if (fpsComboBox->getSelectedItemId() == "2") { cw->setTempFPSLimiter(100); }
		else if (fpsComboBox->getSelectedItemId() == "3") { cw->setTempFPSLimiter(144); }
		break;

	case WidgetState::FullscreenCheckBoxChanged:
		if (fullscreenCheckBox->isChecked()) { cw->setTempIsFullscreen(true); }
		else { cw->setTempIsFullscreen(false); }
		break;

	case WidgetState::VsyncCheckBoxChanged:
		if (vsyncCheckBox->isChecked()) { cw->setTempIsVsync(true); }
		else { cw->setTempIsVsync(false); }
		break;

	}
	widgetState = WidgetState::Nothing;
}

void menuApplyButtonPressed(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	gv->setGameLanguage(cw->getTempGameLanguage());
	gw->setSize(cw->getTempWindowSize());
	gw->setFPSLimiter(cw->getTempFPSLimiter());
	gw->setIsFullscreen(cw->getTempIsFullscreen());
	gw->setIsVsync(cw->getTempIsVsync());

	gw->createWindow(gw->getSize(), gw->getIsFullscreen(), gw->getIsVsync(), gw->getFPSLimiter());

	minimap.create();

	cw->updateGUI(gw);
	cw->updatePlayersList(gv->getGameLanguage());

	graphicsSettingsMenuUpdate(gv, gw, nm, cw, minimap);
}


void graphicsSettingsMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw, Minimap& minimap)
{
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float winSizeY = static_cast<float>(gw->window.getSize().y);
	cw->menuGUI.removeAllWidgets();

	cw->setTempGameLanguage(gv->getGameLanguage());
	cw->setTempWindowSize(gw->getSize());
	cw->setTempFPSLimiter(gw->getFPSLimiter());
	cw->setTempIsFullscreen(gw->getIsFullscreen());
	cw->setTempIsVsync(gw->getIsVsync());

	tgui::Button::Ptr applyButton = tgui::Button::create();
	applyButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	applyButton->getRenderer()->setTextColor(tgui::Color::Black);
	applyButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	applyButton->getRenderer()->setTextColorDisabled(tgui::Color::Black);
	applyButton->setSize("14%", "7%");
	applyButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { applyButton->setText(L"Apply"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { applyButton->setText(L"Ïðèìåíèòü"); }
	applyButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	applyButton->setPosition("50%", "80%");
	applyButton->onPress(&menuApplyButtonPressed, std::ref(gv), std::ref(gw), std::ref(nm), std::ref(cw), std::ref(minimap));
	applyButton->setEnabled(false);
	cw->menuGUI.add(applyButton);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize("14%", "7%");
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { backButton->setText(L"Back"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { backButton->setText(L"Íàçàä"); }
	backButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	backButton->setPosition("50%", "90%");
	backButton->onPress([] {
		menuAction = MenuAction::OpenSettingsMenu;
		});
	cw->menuGUI.add(backButton);

	tgui::Label::Ptr graphicsSettingsLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { graphicsSettingsLabel->setText(L"GRAPHICS SETTINGS"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { graphicsSettingsLabel->setText(L"ÍÀÑÒÐÎÉÊÈ ÃÐÀÔÈÊÈ"); }
	graphicsSettingsLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 20.f)));
	graphicsSettingsLabel->setOrigin(0.5f, 0.5f);
	graphicsSettingsLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	graphicsSettingsLabel->setPosition("50%", "15%");
	cw->menuGUI.add(graphicsSettingsLabel, "graphicsSettingsLabel");

	tgui::Label::Ptr resolutionLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { resolutionLabel->setText(L"Resolution"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { resolutionLabel->setText(L"Ðàçðåøåíèå ýêðàíà"); }
	resolutionLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	resolutionLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	resolutionLabel->setPosition("5%", "22%");
	cw->menuGUI.add(resolutionLabel, "resolutionLabel");

	tgui::Label::Ptr fullscreenLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { fullscreenLabel->setText(L"Fullscreen"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { fullscreenLabel->setText(L"Ïîëíûé ýêðàí"); }
	fullscreenLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	fullscreenLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	fullscreenLabel->setPosition("5%", "32%");
	cw->menuGUI.add(fullscreenLabel, "fullscreenLabel");

	tgui::Label::Ptr vsyncLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { vsyncLabel->setText(L"Vsync"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { vsyncLabel->setText(L"Âåðò. ñèíõðîíèçàöèÿ"); }
	vsyncLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	vsyncLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	vsyncLabel->setPosition("5%", "42%");
	cw->menuGUI.add(vsyncLabel, "vsyncLabel");

	tgui::Label::Ptr fpsLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { fpsLabel->setText(L"FPS"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { fpsLabel->setText(L"ÔÏÑ"); }
	fpsLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	fpsLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	fpsLabel->setPosition("5%", "52%");
	cw->menuGUI.add(fpsLabel, "fpsLabel");

	tgui::Label::Ptr languageLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { languageLabel->setText(L"Language"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { languageLabel->setText(L"ßçûê"); }
	languageLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 50.f)));
	languageLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	languageLabel->setPosition("5%", "62%");
	cw->menuGUI.add(languageLabel, "languageLabel");

	tgui::ComboBox::Ptr resolutionComboBox = tgui::ComboBox::create();
	resolutionComboBox->setSize("10.4%", "3.7%");
	resolutionComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	resolutionComboBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 70.f)));
	int i = 0;
	for (auto& el : sf::VideoMode::getFullscreenModes())
	{
		resolutionComboBox->addItem(std::to_string(el.width) + "x" + std::to_string(el.height), std::to_string(i));
		++i;
	}
	resolutionComboBox->setPosition(resolutionLabel->getPosition().x + 500.f, resolutionLabel->getPosition().y);
	resolutionComboBox->setSelectedItem(std::to_string(gw->window.getSize().x) + "x" + std::to_string(gw->window.getSize().y));
	resolutionComboBox->onItemSelect([&gv, &gw, &cw, applyButton]()
		{
			widgetState = WidgetState::ResolutionComboBoxChanged;
			widgetStateHandler(gv, gw, cw);

			applyButton->setEnabled(true);
		});
	cw->menuGUI.add(resolutionComboBox, "resolutionComboBox");

	tgui::ComboBox::Ptr languageComboBox = tgui::ComboBox::create();
	languageComboBox->setSize("10.4%", "3.7%");
	languageComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	languageComboBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 70.f)));
	languageComboBox->addItem(L"English", "0");
	languageComboBox->addItem(L"Ðóññêèé", "1");
	languageComboBox->setPosition(languageLabel->getPosition().x + 500.f, languageLabel->getPosition().y);
	if (gv->getGameLanguage() == GameLanguage::English) { languageComboBox->setSelectedItemById("0"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { languageComboBox->setSelectedItemById("1"); }
	languageComboBox->onItemSelect([&gv, &gw, &cw, applyButton]()
		{
			widgetState = WidgetState::LanguageComboBoxChanged;
			widgetStateHandler(gv, gw, cw);

			applyButton->setEnabled(true);
		});
	cw->menuGUI.add(languageComboBox, "languageComboBox");

	tgui::ComboBox::Ptr fpsComboBox = tgui::ComboBox::create();
	fpsComboBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	fpsComboBox->getRenderer()->setTextColorDisabled(tgui::Color::Black);
	fpsComboBox->getRenderer()->setArrowBackgroundColorDisabled(gv->greyColor);
	fpsComboBox->getRenderer()->setArrowColorDisabled(gv->greyColor);
	fpsComboBox->setSize("10.4%", "3.7%");
	fpsComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	fpsComboBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 70.f)));
	fpsComboBox->addItem("60", "0");
	fpsComboBox->addItem("75", "1");
	fpsComboBox->addItem("100", "2");
	fpsComboBox->addItem("144", "3");
	fpsComboBox->setPosition(fpsLabel->getPosition().x + 500.f, fpsLabel->getPosition().y);
	fpsComboBox->setSelectedItem(std::to_string(gw->getFPSLimiter()));
	fpsComboBox->onItemSelect([&gv, &gw, &cw, applyButton]()
		{
			widgetState = WidgetState::FPSComboBoxChanged;
			widgetStateHandler(gv, gw, cw);

			applyButton->setEnabled(true);
		});
	if (gw->getIsVsync()) { fpsComboBox->setEnabled(false); }
	else { fpsComboBox->setEnabled(true); }
	cw->menuGUI.add(fpsComboBox, "fpsComboBox");

	tgui::CheckBox::Ptr fullscreenCheckBox = tgui::CheckBox::create();
	fullscreenCheckBox->getRenderer()->setCheckColor(tgui::Color::Black);
	fullscreenCheckBox->setSize("2.6%", "4.6%");
	fullscreenCheckBox->setPosition(fullscreenLabel->getPosition().x + 500.f, fullscreenLabel->getPosition().y);
	if (gw->getIsFullscreen()) { fullscreenCheckBox->setChecked(true); }
	else { fullscreenCheckBox->setChecked(false); }
	fullscreenCheckBox->onChange([&gv, &gw, &cw, applyButton]()
		{
			widgetState = WidgetState::FullscreenCheckBoxChanged;
			widgetStateHandler(gv, gw, cw);

			applyButton->setEnabled(true);
		});
	cw->menuGUI.add(fullscreenCheckBox, "fullscreenCheckBox");

	tgui::CheckBox::Ptr vsyncCheckBox = tgui::CheckBox::create();
	vsyncCheckBox->getRenderer()->setCheckColor(tgui::Color::Black);
	vsyncCheckBox->setSize("2.6%", "4.6%");
	vsyncCheckBox->setPosition(vsyncLabel->getPosition().x + 500.f, vsyncLabel->getPosition().y);
	if (gw->getIsVsync()) { vsyncCheckBox->setChecked(true); }
	else { vsyncCheckBox->setChecked(false); }
	vsyncCheckBox->onChange([&gv, &gw, &cw, applyButton, vsyncCheckBox, fpsComboBox]()
		{
			widgetState = WidgetState::VsyncCheckBoxChanged;
			widgetStateHandler(gv, gw, cw);

			applyButton->setEnabled(true);
			if (vsyncCheckBox->isChecked()) { fpsComboBox->setEnabled(false); }
			else { fpsComboBox->setEnabled(true); }
		});

	cw->menuGUI.add(vsyncCheckBox, "vsyncCheckBox");
}

void settingsMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw)
{
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float winSizeY = static_cast<float>(gw->window.getSize().y);
	float halfWinSizeX = gw->window.getSize().x / 2.f;
	float halfWinSizeY = gw->window.getSize().y / 2.f;
	cw->menuGUI.removeAllWidgets();

	tgui::Button::Ptr graphicsSettingsButton = tgui::Button::create();
	graphicsSettingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	graphicsSettingsButton->getRenderer()->setTextColor(tgui::Color::Black);
	graphicsSettingsButton->setSize(round(winSizeX / 6.5f), round(winSizeX / 12.75f));
	graphicsSettingsButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { graphicsSettingsButton->setText(L"GRAPHICS\nSETTINGS"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { graphicsSettingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ\n ÃÐÀÔÈÊÈ"); }
	graphicsSettingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	graphicsSettingsButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f));
	graphicsSettingsButton->onPress([] {menuAction = MenuAction::OpenGraphicsSettingsMenu; });
	cw->menuGUI.add(graphicsSettingsButton, "graphicsSettingsButton");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize(round(winSizeX / 9.5f), round(winSizeX / 19.f));
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { backButton->setText(L"BACK"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { backButton->setText(L"ÍÀÇÀÄ"); }
	backButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	backButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f));
	backButton->onPress([&gv] {
		if (gv->getGameState() == GameState::MainMenu) { menuAction = MenuAction::OpenMainMenu; }
		else if (gv->getGameState() == GameState::GameMenu) { menuAction = MenuAction::OpenGameMenu; }
		});
	cw->menuGUI.add(backButton, "backButton");
}

void multiplayerMenuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float winSizeY = static_cast<float>(gw->window.getSize().y);
	float halfWinSizeX = static_cast<float>(gw->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gw->window.getSize().y) / 2.f;
	multiplayerMenuError = MultiplayerMenuErrors::NoErrors;
	cw->menuGUI.removeAllWidgets();

	tgui::Label::Ptr enterNicknameLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { enterNicknameLabel->setText(L"ENTER NICKNAME"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { enterNicknameLabel->setText(L"ÂÂÅÄÈÒÅ ÍÈÊÍÅÉÌ"); }
	enterNicknameLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterNicknameLabel->setOrigin(0.5f, 0.5f);
	enterNicknameLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterNicknameLabel->setPosition("50%", "22%");
	cw->menuGUI.add(enterNicknameLabel, "enterNicknameLabel");

	tgui::EditBox::Ptr nicknameEditBox = tgui::EditBox::create();
	nicknameEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	nicknameEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	nicknameEditBox->setSize("25%", "7%");
	nicknameEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	nicknameEditBox->setMaximumCharacters(15);
	nicknameEditBox->setOrigin(0.5f, 0.5f);
	nicknameEditBox->setText(nm->getNickname());
	nicknameEditBox->setPosition("50%", "28%");
	nicknameEditBox->onTextChange([&nm, nicknameEditBox]()
		{
			std::wstring tempNick = nicknameEditBox->getText().toWideString();
			tempNick.erase(remove(tempNick.begin(), tempNick.end(), ' '), tempNick.end());
			nm->setNickname(tempNick);
		});
	cw->menuGUI.add(nicknameEditBox, "nicknameEditBox");

	tgui::Label::Ptr enterIPLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { enterIPLabel->setText(L"ENTER IP"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { enterIPLabel->setText(L"ÂÂÅÄÈÒÅ IP"); }
	enterIPLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterIPLabel->setOrigin(0.5f, 0.5f);
	enterIPLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterIPLabel->setPosition("50%", "38%");
	cw->menuGUI.add(enterIPLabel, "enterIPLabel");

	tgui::EditBox::Ptr IPEditBox = tgui::EditBox::create();
	IPEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	IPEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	IPEditBox->setSize("25%", "7%");
	IPEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	IPEditBox->setMaximumCharacters(15);
	IPEditBox->setOrigin(0.5f, 0.5f);
	IPEditBox->setText(nm->getServerIP());
	IPEditBox->setPosition("50%", "44%");
	IPEditBox->onTextChange([&nm, IPEditBox]()
		{
			std::string tempIP = IPEditBox->getText().toStdString();
			tempIP.erase(remove(tempIP.begin(), tempIP.end(), ' '), tempIP.end());
			nm->setServerIP(tempIP);
		});
	cw->menuGUI.add(IPEditBox, "IPEditBox");

	tgui::Label::Ptr enterPortLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { enterPortLabel->setText(L"ENTER PORT"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { enterPortLabel->setText(L"ÂÂÅÄÈÒÅ ÏÎÐÒ"); }
	enterPortLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterPortLabel->setOrigin(0.5f, 0.5f);
	enterPortLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterPortLabel->setPosition("50%", "54%");
	cw->menuGUI.add(enterPortLabel, "enterPortLabel");

	tgui::EditBox::Ptr portEditBox = tgui::EditBox::create();
	portEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	portEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	portEditBox->setSize("25%", "7%");
	portEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	portEditBox->setMaximumCharacters(15);
	portEditBox->setOrigin(0.5f, 0.5f);
	portEditBox->setText(nm->getTempPort());
	portEditBox->setPosition("50%", "60%");
	portEditBox->onTextChange([&nm, portEditBox]()
		{
			std::string tempPort = portEditBox->getText().toStdString();
			tempPort.erase(remove(tempPort.begin(), tempPort.end(), ' '), tempPort.end());
			nm->setTempPort(tempPort);
			nm->setServerPort(std::atoi(tempPort.c_str()));
		});
	cw->menuGUI.add(portEditBox, "portEditBox");

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	if (gv->getGameLanguage() == GameLanguage::English) { errorLabel->setText(L""); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { errorLabel->setText(L""); }
	errorLabel->setTextSize(40);
	errorLabel->setOrigin(0.5f, 0.5f);
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);
	errorLabel->setPosition("50%", "90%");
	cw->menuGUI.add(errorLabel, "errorLabel");

	tgui::Button::Ptr connectButton = tgui::Button::create();
	connectButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	connectButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	connectButton->getRenderer()->setTextColor(tgui::Color::Black);
	connectButton->setSize("10%", "8%");
	connectButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { connectButton->setText(L"Connect"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { connectButton->setText(L"Âîéòè"); }
	connectButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	connectButton->setPosition("44%", "75%");
	connectButton->onPress([&nm] { nm->setConnectButtonPressed(true); });
	cw->menuGUI.add(connectButton, "connectButton");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize("10%", "8%");
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { backButton->setText(L"Back"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { backButton->setText(L"Íàçàä"); }
	backButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	backButton->setPosition("56%", "75%");
	backButton->onPress([] { menuAction = MenuAction::OpenMainMenu; });
	cw->menuGUI.add(backButton, "backButton");
}

void multiplayerGameUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float winSizeY = static_cast<float>(gw->window.getSize().y);
	float halfWinSizeX = static_cast<float>(gw->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gw->window.getSize().y) / 2.f;
	float columnWidth = gw->window.getSize().x / 5.5f;
	unsigned int itemHeight = static_cast<unsigned int>(round(winSizeX / 35.f));
	cw->gameGUI.removeAllWidgets();

	auto theme = tgui::Theme::getDefault();
	tgui::ScrollbarRenderer(theme->getRenderer("Scrollbar")).setThumbColor(tgui::Color(102, 0, 204));
	tgui::ScrollbarRenderer(theme->getRenderer("Scrollbar")).setThumbColorHover(tgui::Color(102, 0, 204));

	tgui::ChatBox::Ptr chatBox = tgui::ChatBox::create();
	chatBox->getRenderer()->setBackgroundColor(tgui::Color(0, 51, 102));
	chatBox->getRenderer()->setBorders(tgui::Borders(4.f, 4.f, 4.f, 4.f));
	chatBox->getRenderer()->setBorderColor(tgui::Color::Black);
	chatBox->getRenderer()->setScrollbarWidth(24.f);
	chatBox->setScrollbarValue(2000);
	chatBox->setSize("30%", "30%");
	chatBox->setOrigin(0.5f, 0.5f);
	chatBox->setPosition("20%", "70%");
	chatBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 75.f)));
	cw->gameGUI.add(chatBox, "chatBox");

	tgui::EditBox::Ptr editBox = tgui::EditBox::create();
	editBox->getRenderer()->setBackgroundColor(tgui::Color(0, 51, 102));
	editBox->getRenderer()->setBackgroundColorHover(tgui::Color(0, 51, 102));
	editBox->getRenderer()->setBorderColor(tgui::Color::Black);
	editBox->getRenderer()->setTextColor(tgui::Color::Black);
	editBox->getRenderer()->setSelectedTextColor(tgui::Color::Black);
	editBox->getRenderer()->setTextColorDisabled(tgui::Color::Black);
	editBox->getRenderer()->setTextColorFocused(tgui::Color::Black);
	editBox->getRenderer()->setBorders(tgui::Borders(4.f, 3.f, 4.f, 4.f));
	editBox->setMaximumCharacters(200);
	editBox->setSize("30%", "7%");
	editBox->setOrigin(0.5f, 0.5f);
	editBox->setPosition("20%", "88%");
	editBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 75.f)));
	editBox->setReadOnly(true);
	editBox->onMousePress([editBox]
		{
			editBox->setReadOnly(false);
			editBox->getRenderer()->setBackgroundColor(tgui::Color::White);
			editBox->getRenderer()->setBackgroundColorHover(tgui::Color::White);
			editBox->getRenderer()->setOpacity(1.f);
		});

	cw->gameGUI.add(editBox, "editBox");

	tgui::ListView::Ptr playersList = tgui::ListView::create();
	playersList->getRenderer()->setScrollbarWidth(24.f);
	playersList->getRenderer()->setBorders(tgui::Borders(4.f, 4.f, 4.f, 4.f));
	playersList->getRenderer()->setHeaderTextColor(tgui::Color::Black);
	playersList->getRenderer()->setHeaderBackgroundColor(tgui::Color::White);
	playersList->getRenderer()->setBackgroundColor(tgui::Color(102, 0, 51));
	playersList->getRenderer()->setBackgroundColorHover(tgui::Color(102, 0, 51));
	playersList->getRenderer()->setBorderColor(tgui::Color::Black);
	playersList->getRenderer()->setTextColor(tgui::Color::Cyan);
	playersList->getRenderer()->setTextColorHover(tgui::Color::Cyan);
	playersList->getRenderer()->setSeparatorColor(tgui::Color::Black);
	playersList->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	playersList->setSeparatorWidth(3);
	playersList->setHeaderSeparatorHeight(3);
	playersList->setGridLinesWidth(3);
	playersList->setShowVerticalGridLines(true);
	playersList->setShowHorizontalGridLines(true);
	playersList->setItemHeight(itemHeight);
	playersList->setHeaderHeight(round(winSizeX / 35.f));
	playersList->setSize(static_cast<unsigned int>(round(winSizeX / 2.64f)), itemHeight * 13);
	playersList->setTextSize(static_cast<unsigned int>(round(winSizeX / 40.f)));
	playersList->setOrigin(0.5f, 0.5f);
	playersList->setPosition("50%", "50%");
	playersList->setVisible(false);
	playersList->onItemSelect([playersList]()
		{
			playersList->deselectItems();
		});
	if (gv->getGameLanguage() == GameLanguage::English)
	{
		playersList->addColumn(L"Nickname", columnWidth * 1.43f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Ping", columnWidth / 2.f, tgui::ListView::ColumnAlignment::Center);
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		playersList->addColumn(L"Íèêíåéì", columnWidth * 1.43f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Ïèíã", columnWidth / 2.f, tgui::ListView::ColumnAlignment::Center);
	}
	cw->gameGUI.add(playersList, "playersList");

}

void menuUpdate(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<CustomWidget>& cw)
{
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float winSizeY = static_cast<float>(gw->window.getSize().y);
	float halfWinSizeX = static_cast<float>(gw->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gw->window.getSize().y) / 2.f;
	cw->menuGUI.removeAllWidgets();

	if (!gv->getIsSingleplayer() && !gv->getIsMultiplayer() && menuType == MenuType::MainMenu)
	{
		tgui::Button::Ptr singleplayerButton = tgui::Button::create();
		singleplayerButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		singleplayerButton->getRenderer()->setTextColor(tgui::Color::Black);
		singleplayerButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		singleplayerButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == GameLanguage::English) { singleplayerButton->setText(L"SINGLEPLAYER"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { singleplayerButton->setText(L"ÎÄÈÍÎ×ÍÀß ÈÃÐÀ"); }
		singleplayerButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		singleplayerButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
		singleplayerButton->onPress([] { menuAction = MenuAction::StartGame; });
		cw->menuGUI.add(singleplayerButton, "singleplayerButton");

		tgui::Button::Ptr multiplayerButton = tgui::Button::create();
		multiplayerButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		multiplayerButton->getRenderer()->setTextColor(tgui::Color::Black);
		multiplayerButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		multiplayerButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == GameLanguage::English) { multiplayerButton->setText(L"MULTIPLAYER"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { multiplayerButton->setText(L"ÑÅÒÅÂÀß ÈÃÐÀ"); }
		multiplayerButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		multiplayerButton->setPosition(halfWinSizeX, halfWinSizeY);
		multiplayerButton->onPress([] { menuAction = MenuAction::OpenMultiplayerMenu; });
		cw->menuGUI.add(multiplayerButton, "multiplayerButton");
	}
	else if (gv->getIsSingleplayer() && !gv->getIsMultiplayer() && menuType == MenuType::GameMenu)
	{
		if (playerPtr->getIsAlive())
		{
			tgui::Button::Ptr continueButton = tgui::Button::create();
			continueButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
			continueButton->getRenderer()->setTextColor(tgui::Color::Black);
			continueButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
			continueButton->setOrigin(0.5f, 0.5f);
			if (gv->getGameLanguage() == GameLanguage::English) { continueButton->setText(L"CONTINUE"); }
			else if (gv->getGameLanguage() == GameLanguage::Russian) { continueButton->setText(L"ÏÐÎÄÎËÆÈÒÜ"); }
			continueButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
			continueButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
			continueButton->onPress([] { menuAction = MenuAction::ContinueGame; });
			cw->menuGUI.add(continueButton, "continueButton");
		}
		else
		{
			tgui::Button::Ptr restartButton = tgui::Button::create();
			restartButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
			restartButton->getRenderer()->setTextColor(tgui::Color::Black);
			restartButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
			restartButton->setOrigin(0.5f, 0.5f);
			if (gv->getGameLanguage() == GameLanguage::English) { restartButton->setText(L"RESTART"); }
			else if (gv->getGameLanguage() == GameLanguage::Russian) { restartButton->setText(L"ÏÅÐÅÇÀÏÓÑÊ"); }
			restartButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
			restartButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
			restartButton->onPress([] { menuAction = MenuAction::RestartGame; });
			cw->menuGUI.add(restartButton, "restartButton");
		}

		tgui::Button::Ptr backToMenuButton = tgui::Button::create();
		backToMenuButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		backToMenuButton->getRenderer()->setTextColor(tgui::Color::Black);
		backToMenuButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		backToMenuButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == GameLanguage::English) { backToMenuButton->setText(L"BACK TO MENU"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { backToMenuButton->setText(L"ÍÀÇÀÄ Â ÌÅÍÞ"); }
		backToMenuButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		backToMenuButton->setPosition(halfWinSizeX, halfWinSizeY);
		backToMenuButton->onPress([&gv] { menuAction = MenuAction::OpenMainMenu; gv->setIsSingleplayer(false); });
		cw->menuGUI.add(backToMenuButton, "backToMenuButton");
	}
	else if (!gv->getIsSingleplayer() && gv->getIsMultiplayer() && menuType == MenuType::GameMenu)
	{
		tgui::Button::Ptr continueButton = tgui::Button::create();
		continueButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		continueButton->getRenderer()->setTextColor(tgui::Color::Black);
		continueButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		continueButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == GameLanguage::English) { continueButton->setText(L"CONTINUE"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { continueButton->setText(L"ÏÐÎÄÎËÆÈÒÜ"); }
		continueButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		continueButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
		continueButton->onPress([] { menuAction = MenuAction::ContinueGame; });
		cw->menuGUI.add(continueButton, "continueButton");

		tgui::Button::Ptr backToMenuButton = tgui::Button::create();
		backToMenuButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		backToMenuButton->getRenderer()->setTextColor(tgui::Color::Black);
		backToMenuButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		backToMenuButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == GameLanguage::English) { backToMenuButton->setText(L"BACK TO MENU"); }
		else if (gv->getGameLanguage() == GameLanguage::Russian) { backToMenuButton->setText(L"ÍÀÇÀÄ Â ÌÅÍÞ"); }
		backToMenuButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		backToMenuButton->setPosition(halfWinSizeX, halfWinSizeY);
		backToMenuButton->onPress([&gv] { menuAction = MenuAction::ExitGame; gv->setIsMultiplayer(false); });
		cw->menuGUI.add(backToMenuButton, "backToMenuButton");
	}

	tgui::Button::Ptr settingsButton = tgui::Button::create();
	settingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	settingsButton->getRenderer()->setTextColor(tgui::Color::Black);
	settingsButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
	settingsButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { settingsButton->setText(L"SETTINGS"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { settingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ"); }
	settingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	settingsButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f));
	settingsButton->onPress([] { menuAction = MenuAction::OpenSettingsMenu; });
	cw->menuGUI.add(settingsButton, "settingsButton");

	tgui::Button::Ptr exitButton = tgui::Button::create();
	exitButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	exitButton->getRenderer()->setTextColor(tgui::Color::Black);
	exitButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
	exitButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == GameLanguage::English) { exitButton->setText(L"EXIT"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { exitButton->setText(L"ÂÛÕÎÄ"); }
	exitButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	exitButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f));
	exitButton->onPress([&gv, &gw] { gv->setIsSingleplayer(false); gv->setIsMultiplayer(false); gw->window.close(); });
	cw->menuGUI.add(exitButton, "exitButton");
}