#include "GameUpdate.h" // game update header file.
#include "RectangularBoundaryCollision.hpp"

Entity* playerPtr = nullptr; // create a pointer to the player.

bool resolutionComboBoxChanged = false;
bool languageComboBoxChanged = false;
bool fpsComboBoxChanged = false;
bool fullscreenCheckBoxChanged = false;
bool vsyncCheckBoxChanged = false;

Entity* getPlayerPtr()
{
	return playerPtr;
}

void setPlayerPtr(Entity* ptr)
{
	playerPtr = ptr;
}

void collisionHandler(Entity* entity, Entity* entity2)
{
	if (entity != nullptr && entity2 != nullptr && entity != entity2 && collision::areColliding(entity->getRectHitbox(), entity2->getRectHitbox()))
	{
		if (entity->getEntityType() == "Bullet" && (entity2->getEntityType() == "Box" || entity2->getEntityType() == "Player" || entity2->getEntityType() == "Wall" || entity2->getEntityType() == "Enemy") && entity->getCreatorName() != entity2->getName())
			// if the entity is a bullet or box or player or enemy and creator name does not equal entity name.
		{
			entity->setIsAlive(false);
			entity2->setHP(entity2->getHP() - entity->getHP());
		}

		if (entity->getEntityType() == "Player") // if the entity is a player.
		{
			if (entity2->getEntityType() == "Box" || entity2->getEntityType() == "Wall" || entity2->getEntityType() == "Enemy") // if the entity2 is a box or wall or enemy.
			{
				if (entity->getIsMove() == true) { entity->setIsMove(false); }
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}

			if (entity2->getEntityType() == "Item" && entity2->getName() == L"GoldCoin") // if the entity2 name is a gold coin.
			{
				entity->setGoldCoins(entity->getGoldCoins() + 1);
				entity2->setIsAlive(false);
			}
			if (entity2->getEntityType() == "Item" && entity2->getName() == L"HPBonus" && entity->getHP() < 100) // if the entity2 name is a HP bonus and entity HP less than 100.
			{
				entity->setHP(entity->getHP() + 30);
				if (entity->getHP() >= 100) { entity->setHP(entity->getHP() - (entity->getHP() - 100)); }
				entity2->setIsAlive(false);
			}
		}

		if (entity->getEntityType() == "Enemy") // if the entity is an enemy.
		{
			if (entity2->getEntityType() == "Player") // if the entity2 is a player.
			{
				// for example - hit the player with a sword.
			}

			if (entity2->getEntityType() == "Wall" || entity2->getEntityType() == "Box") // if the entity2 is a wall or box.
			{
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}
		}
	}
}

void applyButtonPressed(GameVariable* gv, Minimap& minimap)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	auto resolutionComboBox = gv->gui.get<tgui::ComboBox>("resolutionComboBox");
	auto languageComboBox = gv->gui.get<tgui::ComboBox>("languageComboBox");
	auto fpsComboBox = gv->gui.get<tgui::ComboBox>("fpsComboBox");
	auto fullscreenCheckBox = gv->gui.get<tgui::CheckBox>("fullscreenCheckBox");
	auto vsyncCheckBox = gv->gui.get<tgui::CheckBox>("vsyncCheckBox");

	if (languageComboBoxChanged == true)
	{
		if (languageComboBox->getSelectedItemId() == "0") { gv->setGameLanguage('e'); }
		else if (languageComboBox->getSelectedItemId() == "1") { gv->setGameLanguage('r'); }
		languageComboBoxChanged = false;
	}

	if (vsyncCheckBoxChanged == true)
	{
		if (vsyncCheckBox->isChecked())
		{
			gv->setIsVsync(true);
			gv->setFPSLimiter(0);
		}
		else
		{
			gv->setIsVsync(false);
			if (fpsComboBox->getSelectedItemId() == "0") { gv->setFPSLimiter(60); }
			else if (fpsComboBox->getSelectedItemId() == "1") { gv->setFPSLimiter(75); }
			else if (fpsComboBox->getSelectedItemId() == "2") { gv->setFPSLimiter(100); }
			else if (fpsComboBox->getSelectedItemId() == "3") { gv->setFPSLimiter(144); }
		}

		gv->window.setVerticalSyncEnabled(gv->getIsVsync());
		gv->window.setFramerateLimit(gv->getFPSLimiter());
		vsyncCheckBoxChanged = false;
	}

	if (fpsComboBoxChanged == true)
	{
		if (fpsComboBox->getSelectedItemId() == "0") { gv->setFPSLimiter(60); }
		else if (fpsComboBox->getSelectedItemId() == "1") { gv->setFPSLimiter(75); }
		else if (fpsComboBox->getSelectedItemId() == "2") { gv->setFPSLimiter(100); }
		else if (fpsComboBox->getSelectedItemId() == "3") { gv->setFPSLimiter(144); }
		gv->window.setVerticalSyncEnabled(gv->getIsVsync());
		gv->window.setFramerateLimit(gv->getFPSLimiter());
		fpsComboBoxChanged = false;
	}

	if (fullscreenCheckBoxChanged == true)
	{
		if (fullscreenCheckBox->isChecked())
		{
			gv->setIsFullscreen(true);
			gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "Bad Game", sf::Style::Fullscreen), settings;
		}
		else
		{
			gv->setIsFullscreen(false);
			gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "Bad Game", sf::Style::Close), settings;
		}
		gv->window.setVerticalSyncEnabled(gv->getIsVsync());
		gv->window.setFramerateLimit(gv->getFPSLimiter());
		gv->gui.setWindow(gv->window);
		fullscreenCheckBoxChanged = false;
	}

	if (resolutionComboBoxChanged == true)
	{
		std::string tempResolution = resolutionComboBox->getSelectedItem().trim().toStdString();
		std::string width = tempResolution.substr(0, tempResolution.find('x'));
		std::string height = tempResolution.substr(tempResolution.find('x') + 1, tempResolution.size());
		if ((gv->getWindowSize().x != std::atoi(width.c_str())) || (gv->getWindowSize().y != std::atoi(height.c_str())))
		{
			gv->setMenuNum(0);
			gv->setWindowSize(sf::Vector2u(std::atoi(width.c_str()), std::atoi(height.c_str())));
			if (gv->getIsFullscreen() == true) { gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "Bad Game", sf::Style::Fullscreen), settings; }
			else { gv->window.create(sf::VideoMode(gv->getWindowSize().x, gv->getWindowSize().y), "Bad Game", sf::Style::Close), settings; }
			gv->window.setVerticalSyncEnabled(gv->getIsVsync());
			gv->window.setFramerateLimit(gv->getFPSLimiter());
			gv->gui.setWindow(gv->window);
			minimap.setViewport(sf::Vector2f(0.8f, 0.f), sf::Vector2f(0.2f, 0.355f));
			minimap.setBorderSize(sf::Vector2f(minimap.getViewport().width * gv->getGameViewSize().x, minimap.getViewport().height * gv->getGameViewSize().y));
			gv->setMenuViewSize(sf::Vector2f(static_cast<float>(gv->window.getSize().x), static_cast<float>(gv->window.getSize().y)));
			gv->setMenuViewCenter(sf::Vector2f(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f));
			gv->setWindowView(gv->getMenuView());
		}
		resolutionComboBoxChanged = false;
	}
	graphicsSettingsMenuUpdate(gv, minimap);
}

void graphicsSettingsMenuUpdate(GameVariable* gv, Minimap& minimap) // graphic settings menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);
	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->gui.removeAllWidgets();

	tgui::Button::Ptr applyButton = tgui::Button::create();
	applyButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	applyButton->getRenderer()->setTextColor(tgui::Color::Black);
	applyButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	applyButton->getRenderer()->setTextColorDisabled(tgui::Color::Black);
	applyButton->setSize("14%", "7%");
	applyButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { applyButton->setText(L"Apply"); }
	else if (gv->getGameLanguage() == 'r') { applyButton->setText(L"Ïðèìåíèòü"); }
	applyButton->setTextSize(35);
	applyButton->setPosition("50%", "80%");
	applyButton->onPress(&applyButtonPressed, gv, std::ref(minimap));
	applyButton->setEnabled(false);
	gv->gui.add(applyButton);

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize("14%", "7%");
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { backButton->setText(L"Back"); }
	else if (gv->getGameLanguage() == 'r') { backButton->setText(L"Íàçàä"); }
	backButton->setTextSize(35);
	backButton->setPosition("50%", "90%");
	backButton->onPress([=] { gv->setMenuNum(6); });
	gv->gui.add(backButton);

	tgui::Label::Ptr graphicsSettingsLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { graphicsSettingsLabel->setText(L"GRAPHICS SETTINGS"); }
	else if (gv->getGameLanguage() == 'r') { graphicsSettingsLabel->setText(L"ÍÀÑÒÐÎÉÊÈ ÃÐÀÔÈÊÈ"); }
	graphicsSettingsLabel->setTextSize(70);
	graphicsSettingsLabel->setOrigin(0.5f, 0.5f);
	graphicsSettingsLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	graphicsSettingsLabel->setPosition("50%", "15%");
	gv->gui.add(graphicsSettingsLabel, "graphicsSettingsLabel");

	tgui::Label::Ptr resolutionLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { resolutionLabel->setText(L"Resolution"); }
	else if (gv->getGameLanguage() == 'r') { resolutionLabel->setText(L"Ðàçðåøåíèå ýêðàíà"); }
	resolutionLabel->setTextSize(40);
	resolutionLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	resolutionLabel->setPosition("5%", "22%");
	gv->gui.add(resolutionLabel, "resolutionLabel");

	tgui::Label::Ptr fullscreenLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { fullscreenLabel->setText(L"Fullscreen"); }
	else if (gv->getGameLanguage() == 'r') { fullscreenLabel->setText(L"Ïîëíûé ýêðàí"); }
	fullscreenLabel->setTextSize(40);
	fullscreenLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	fullscreenLabel->setPosition("5%", "32%");
	gv->gui.add(fullscreenLabel, "fullscreenLabel");

	tgui::Label::Ptr vsyncLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { vsyncLabel->setText(L"Vsync"); }
	else if (gv->getGameLanguage() == 'r') { vsyncLabel->setText(L"Âåðò. ñèíõðîíèçàöèÿ"); }
	vsyncLabel->setTextSize(40);
	vsyncLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	vsyncLabel->setPosition("5%", "42%");
	gv->gui.add(vsyncLabel, "vsyncLabel");

	tgui::Label::Ptr fpsLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { fpsLabel->setText(L"FPS"); }
	else if (gv->getGameLanguage() == 'r') { fpsLabel->setText(L"ÔÏÑ"); }
	fpsLabel->setTextSize(40);
	fpsLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	fpsLabel->setPosition("5%", "52%");
	gv->gui.add(fpsLabel, "fpsLabel");

	tgui::Label::Ptr languageLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { languageLabel->setText(L"Language"); }
	else if (gv->getGameLanguage() == 'r') { languageLabel->setText(L"ßçûê"); }
	languageLabel->setTextSize(40);
	languageLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	languageLabel->setPosition("5%", "62%");
	gv->gui.add(languageLabel, "languageLabel");

	tgui::ComboBox::Ptr resolutionComboBox = tgui::ComboBox::create();
	resolutionComboBox->setSize(200.f, 40.f);
	resolutionComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	resolutionComboBox->setTextSize(25);
	int i = 0;
	for (auto& el : sf::VideoMode::getFullscreenModes())
	{
		resolutionComboBox->addItem(std::to_string(el.width) + "x" + std::to_string(el.height), std::to_string(i));
		i++;
	}
	resolutionComboBox->setPosition(resolutionLabel->getPosition().x + 500.f, resolutionLabel->getPosition().y);
	resolutionComboBox->setSelectedItem(std::to_string(gv->getWindowSize().x) + "x" + std::to_string(gv->getWindowSize().y));
	resolutionComboBox->onItemSelect([=]() { resolutionComboBoxChanged = true; applyButton->setEnabled(true); });
	gv->gui.add(resolutionComboBox, "resolutionComboBox");

	tgui::ComboBox::Ptr languageComboBox = tgui::ComboBox::create();
	languageComboBox->setSize(200.f, 40.f);
	languageComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	languageComboBox->setTextSize(25);
	languageComboBox->addItem(L"English", "0");
	languageComboBox->addItem(L"Ðóññêèé", "1");
	languageComboBox->setPosition(languageLabel->getPosition().x + 500.f, languageLabel->getPosition().y);
	if (gv->getGameLanguage() == 'e') { languageComboBox->setSelectedItemById("0"); }
	else if (gv->getGameLanguage() == 'r') { languageComboBox->setSelectedItemById("1"); }
	languageComboBox->onItemSelect([=]() { languageComboBoxChanged = true; applyButton->setEnabled(true); });
	gv->gui.add(languageComboBox, "languageComboBox");

	tgui::ComboBox::Ptr fpsComboBox = tgui::ComboBox::create();
	fpsComboBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	fpsComboBox->getRenderer()->setTextColorDisabled(tgui::Color::Black);
	fpsComboBox->getRenderer()->setArrowBackgroundColorDisabled(gv->greyColor);
	fpsComboBox->getRenderer()->setArrowColorDisabled(gv->greyColor);
	fpsComboBox->setSize(200.f, 40.f);
	fpsComboBox->getRenderer()->setTextColor(tgui::Color::Black);
	fpsComboBox->setTextSize(25);
	fpsComboBox->addItem("60", "0");
	fpsComboBox->addItem("75", "1");
	fpsComboBox->addItem("100", "2");
	fpsComboBox->addItem("144", "3");
	fpsComboBox->setPosition(fpsLabel->getPosition().x + 500.f, fpsLabel->getPosition().y);
	fpsComboBox->setSelectedItem(std::to_string(gv->getFPSLimiter()));
	fpsComboBox->onItemSelect([=]() { fpsComboBoxChanged = true; applyButton->setEnabled(true); });
	if (gv->getIsVsync()) { fpsComboBox->setEnabled(false); }
	else { fpsComboBox->setEnabled(true); }
	gv->gui.add(fpsComboBox, "fpsComboBox");

	tgui::CheckBox::Ptr fullscreenCheckBox = tgui::CheckBox::create();
	fullscreenCheckBox->getRenderer()->setCheckColor(tgui::Color::Black);
	fullscreenCheckBox->setSize(50.f, 50.f);
	fullscreenCheckBox->setPosition(fullscreenLabel->getPosition().x + 500.f, fullscreenLabel->getPosition().y);
	if (gv->getIsFullscreen() == true) { fullscreenCheckBox->setChecked(true); }
	else { fullscreenCheckBox->setChecked(false); }
	fullscreenCheckBox->onChange([=]() { fullscreenCheckBoxChanged = true; applyButton->setEnabled(true); });
	gv->gui.add(fullscreenCheckBox, "fullscreenCheckBox");

	tgui::CheckBox::Ptr vsyncCheckBox = tgui::CheckBox::create();
	vsyncCheckBox->getRenderer()->setCheckColor(tgui::Color::Black);
	vsyncCheckBox->setSize(50.f, 50.f);
	vsyncCheckBox->setPosition(vsyncLabel->getPosition().x + 500.f, vsyncLabel->getPosition().y);
	if (gv->getIsVsync() == true) { vsyncCheckBox->setChecked(true); }
	else { vsyncCheckBox->setChecked(false); }
	vsyncCheckBox->onChange([=]()
		{
			vsyncCheckBoxChanged = true;
			applyButton->setEnabled(true);
			if (vsyncCheckBox->isChecked()) { fpsComboBox->setEnabled(false); }
			else { fpsComboBox->setEnabled(true); }
		});

	gv->gui.add(vsyncCheckBox, "vsyncCheckBox");
}

void settingsMenuUpdate(GameVariable* gv) // settings menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);
	float halfWinSizeX = gv->window.getSize().x / 2.f;
	float halfWinSizeY = gv->window.getSize().y / 2.f;
	gv->gui.removeAllWidgets();

	tgui::Button::Ptr graphicsSettingsButton = tgui::Button::create();
	graphicsSettingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	graphicsSettingsButton->getRenderer()->setTextColor(tgui::Color::Black);
	graphicsSettingsButton->setSize(round(winSizeX / 6.5f), round(winSizeX / 12.75f));
	graphicsSettingsButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { graphicsSettingsButton->setText(L"GRAPHICS\nSETTINGS"); }
	else if (gv->getGameLanguage() == 'r') { graphicsSettingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ\n ÃÐÀÔÈÊÈ"); }
	graphicsSettingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	graphicsSettingsButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 21.f));
	graphicsSettingsButton->onPress([=] { gv->setMenuNum(4); });
	gv->gui.add(graphicsSettingsButton, "graphicsSettingsButton");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize(round(winSizeX / 9.5f), round(winSizeX / 19.f));
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { backButton->setText(L"BACK"); }
	else if (gv->getGameLanguage() == 'r') { backButton->setText(L"ÍÀÇÀÄ"); }
	backButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	backButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 38.f));
	backButton->onPress([=] { gv->setMenuNum(5); });
	gv->gui.add(backButton, "backButton");
}

void multiplayerMenuUpdate(GameVariable* gv) // multiplayer menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);
	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;
	gv->gui.removeAllWidgets();

	tgui::Label::Ptr enterNicknameLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { enterNicknameLabel->setText(L"ENTER NICKNAME"); }
	else if (gv->getGameLanguage() == 'r') { enterNicknameLabel->setText(L"ÂÂÅÄÈÒÅ ÍÈÊÍÅÉÌ"); }
	enterNicknameLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterNicknameLabel->setOrigin(0.5f, 0.5f);
	enterNicknameLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterNicknameLabel->setPosition("50%", "22%");
	gv->gui.add(enterNicknameLabel, "enterNicknameLabel");

	tgui::EditBox::Ptr nicknameEditBox = tgui::EditBox::create();
	nicknameEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	nicknameEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	nicknameEditBox->setSize("25%", "7%");
	nicknameEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	nicknameEditBox->setMaximumCharacters(15);
	nicknameEditBox->setOrigin(0.5f, 0.5f);
	nicknameEditBox->setText(gv->getNickname());
	nicknameEditBox->setPosition("50%", "28%");
	nicknameEditBox->onTextChange([=]()
		{
			std::wstring tempNick = nicknameEditBox->getText().toWideString();
			tempNick.erase(remove(tempNick.begin(), tempNick.end(), ' '), tempNick.end());
			gv->setNickname(tempNick);
		});
	gv->gui.add(nicknameEditBox, "nicknameEditBox");

	tgui::Label::Ptr enterIPLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { enterIPLabel->setText(L"ENTER IP"); }
	else if (gv->getGameLanguage() == 'r') { enterIPLabel->setText(L"ÂÂÅÄÈÒÅ IP"); }
	enterIPLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterIPLabel->setOrigin(0.5f, 0.5f);
	enterIPLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterIPLabel->setPosition("50%", "38%");
	gv->gui.add(enterIPLabel, "enterIPLabel");

	tgui::EditBox::Ptr IPEditBox = tgui::EditBox::create();
	IPEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	IPEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	IPEditBox->setSize("25%", "7%");
	IPEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	IPEditBox->setMaximumCharacters(15);
	IPEditBox->setOrigin(0.5f, 0.5f);
	IPEditBox->setText(gv->getServerIP());
	IPEditBox->setPosition("50%", "44%");
	IPEditBox->onTextChange([=]()
		{
			std::string tempIP = IPEditBox->getText().toStdString();
			tempIP.erase(remove(tempIP.begin(), tempIP.end(), ' '), tempIP.end());
			gv->setServerIP(tempIP);
		});
	gv->gui.add(IPEditBox, "IPEditBox");

	tgui::Label::Ptr enterPortLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { enterPortLabel->setText(L"ENTER PORT"); }
	else if (gv->getGameLanguage() == 'r') { enterPortLabel->setText(L"ÂÂÅÄÈÒÅ ÏÎÐÒ"); }
	enterPortLabel->setTextSize(static_cast<unsigned int>(round(winSizeX / 38.f)));
	enterPortLabel->setOrigin(0.5f, 0.5f);
	enterPortLabel->getRenderer()->setTextColor(tgui::Color::Cyan);
	enterPortLabel->setPosition("50%", "54%");
	gv->gui.add(enterPortLabel, "enterPortLabel");

	tgui::EditBox::Ptr portEditBox = tgui::EditBox::create();
	portEditBox->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	portEditBox->getRenderer()->setTextColor(tgui::Color::Black);
	portEditBox->setSize("25%", "7%");
	portEditBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 35.f)));
	portEditBox->setMaximumCharacters(15);
	portEditBox->setOrigin(0.5f, 0.5f);
	portEditBox->setText(gv->getTempPort());
	portEditBox->setPosition("50%", "60%");
	portEditBox->onTextChange([=]()
		{
			std::string tempPort = portEditBox->getText().toStdString();
			tempPort.erase(remove(tempPort.begin(), tempPort.end(), ' '), tempPort.end());
			gv->setTempPort(tempPort);
			gv->setServerPort(std::atoi(tempPort.c_str()));
		});
	gv->gui.add(portEditBox, "portEditBox");

	tgui::Label::Ptr errorLabel = tgui::Label::create();
	if (gv->getGameLanguage() == 'e') { errorLabel->setText(L""); }
	else if (gv->getGameLanguage() == 'r') { errorLabel->setText(L""); }
	errorLabel->setTextSize(40);
	errorLabel->setOrigin(0.5f, 0.5f);
	errorLabel->getRenderer()->setTextColor(tgui::Color::Red);
	errorLabel->setPosition("50%", "90%");
	gv->gui.add(errorLabel, "errorLabel");

	tgui::Button::Ptr connectButton = tgui::Button::create();
	connectButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	connectButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	connectButton->getRenderer()->setTextColor(tgui::Color::Black);
	connectButton->setSize("10%", "8%");
	connectButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { connectButton->setText(L"Connect"); }
	else if (gv->getGameLanguage() == 'r') { connectButton->setText(L"Âîéòè"); }
	connectButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	connectButton->setPosition("44%", "75%");
	connectButton->onPress([=] { gv->setConnectButtonPressed(true); });
	gv->gui.add(connectButton, "connectButton");

	tgui::Button::Ptr backButton = tgui::Button::create();
	backButton->getRenderer()->setBackgroundColorDisabled(gv->greyColor);
	backButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
	backButton->getRenderer()->setTextColor(tgui::Color::Black);
	backButton->setSize("10%", "8%");
	backButton->setOrigin(0.5f, 0.5f);
	if (gv->getGameLanguage() == 'e') { backButton->setText(L"Back"); }
	else if (gv->getGameLanguage() == 'r') { backButton->setText(L"Íàçàä"); }
	backButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
	backButton->setPosition("56%", "75%");
	backButton->onPress([=] { gv->setMenuNum(5); });
	gv->gui.add(backButton, "backButton");
}

void mainMenuUpdate(GameVariable* gv) // main menu update function.
{
	float winSizeX = static_cast<float>(gv->window.getSize().x);
	float winSizeY = static_cast<float>(gv->window.getSize().y);
	float halfWinSizeX = static_cast<float>(gv->window.getSize().x) / 2.f;
	float halfWinSizeY = static_cast<float>(gv->window.getSize().y) / 2.f;
	gv->gui.removeAllWidgets();

	if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == false)
	{
		tgui::Button::Ptr singleplayerButton = tgui::Button::create();
		singleplayerButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		singleplayerButton->getRenderer()->setTextColor(tgui::Color::Black);
		singleplayerButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		singleplayerButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { singleplayerButton->setText(L"SINGLEPLAYER"); }
		else if (gv->getGameLanguage() == 'r') { singleplayerButton->setText(L"ÎÄÈÍÎ×ÍÀß ÈÃÐÀ"); }
		singleplayerButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		singleplayerButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
		singleplayerButton->onPress([=] { gv->setMenuNum(1); });
		gv->gui.add(singleplayerButton, "singleplayerButton");

		tgui::Button::Ptr multiplayerButton = tgui::Button::create();
		multiplayerButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		multiplayerButton->getRenderer()->setTextColor(tgui::Color::Black);
		multiplayerButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		multiplayerButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { multiplayerButton->setText(L"MULTIPLAYER"); }
		else if (gv->getGameLanguage() == 'r') { multiplayerButton->setText(L"ÑÅÒÅÂÀß ÈÃÐÀ"); }
		multiplayerButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		multiplayerButton->setPosition(halfWinSizeX, halfWinSizeY);
		multiplayerButton->onPress([=] { gv->setMenuNum(8); });
		gv->gui.add(multiplayerButton, "multiplayerButton");

		tgui::Button::Ptr settingsButton = tgui::Button::create();
		settingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		settingsButton->getRenderer()->setTextColor(tgui::Color::Black);
		settingsButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		settingsButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { settingsButton->setText(L"SETTINGS"); }
		else if (gv->getGameLanguage() == 'r') { settingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ"); }
		settingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		settingsButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f));
		settingsButton->onPress([=] { gv->setMenuNum(2); });
		gv->gui.add(settingsButton, "settingsButton");

		tgui::Button::Ptr exitButton = tgui::Button::create();
		exitButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		exitButton->getRenderer()->setTextColor(tgui::Color::Black);
		exitButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		exitButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { exitButton->setText(L"EXIT"); }
		else if (gv->getGameLanguage() == 'r') { exitButton->setText(L"ÂÛÕÎÄ"); }
		exitButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		exitButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f));
		exitButton->onPress([=] { gv->setMenuNum(3); });
		gv->gui.add(exitButton, "exitButton");
	}
	else if (gv->getSinglePlayerGame() == true && gv->getMultiPlayerGame() == false)
	{
		if (getPlayerPtr() == nullptr)
		{
			tgui::Button::Ptr restartButton = tgui::Button::create();
			restartButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
			restartButton->getRenderer()->setTextColor(tgui::Color::Black);
			restartButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
			restartButton->setOrigin(0.5f, 0.5f);
			if (gv->getGameLanguage() == 'e') { restartButton->setText(L"RESTART"); }
			else if (gv->getGameLanguage() == 'r') { restartButton->setText(L"ÏÅÐÅÇÀÏÓÑÊ"); }
			restartButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
			restartButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
			restartButton->onPress([=] { gv->setMenuNum(1); });
			gv->gui.add(restartButton, "restartButton");
		}
		else if (getPlayerPtr() != nullptr)
		{
			tgui::Button::Ptr continueButton = tgui::Button::create();
			continueButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
			continueButton->getRenderer()->setTextColor(tgui::Color::Black);
			continueButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
			continueButton->setOrigin(0.5f, 0.5f);
			if (gv->getGameLanguage() == 'e') { continueButton->setText(L"CONTINUE"); }
			else if (gv->getGameLanguage() == 'r') { continueButton->setText(L"ÏÐÎÄÎËÆÈÒÜ"); }
			continueButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
			continueButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
			continueButton->onPress([=] { gv->setMenuNum(9); });
			gv->gui.add(continueButton, "continueButton");
		}

		tgui::Button::Ptr backToMenuButton = tgui::Button::create();
		backToMenuButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		backToMenuButton->getRenderer()->setTextColor(tgui::Color::Black);
		backToMenuButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		backToMenuButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { backToMenuButton->setText(L"BACK TO MENU"); }
		else if (gv->getGameLanguage() == 'r') { backToMenuButton->setText(L"ÍÀÇÀÄ Â ÌÅÍÞ"); }
		backToMenuButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		backToMenuButton->setPosition(halfWinSizeX, halfWinSizeY);
		backToMenuButton->onPress([=] { gv->setMenuNum(7); });
		gv->gui.add(backToMenuButton, "backToMenuButton");

		tgui::Button::Ptr settingsButton = tgui::Button::create();
		settingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		settingsButton->getRenderer()->setTextColor(tgui::Color::Black);
		settingsButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		settingsButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { settingsButton->setText(L"SETTINGS"); }
		else if (gv->getGameLanguage() == 'r') { settingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ"); }
		settingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		settingsButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f));
		settingsButton->onPress([=] { gv->setMenuNum(2); });
		gv->gui.add(settingsButton, "settingsButton");

		tgui::Button::Ptr exitButton = tgui::Button::create();
		exitButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		exitButton->getRenderer()->setTextColor(tgui::Color::Black);
		exitButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		exitButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { exitButton->setText(L"EXIT"); }
		else if (gv->getGameLanguage() == 'r') { exitButton->setText(L"ÂÛÕÎÄ"); }
		exitButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		exitButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f));
		exitButton->onPress([=] { gv->setMenuNum(3); });
		gv->gui.add(exitButton, "exitButton");
	}
	else if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == true)
	{
		tgui::Button::Ptr continueButton = tgui::Button::create();
		continueButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		continueButton->getRenderer()->setTextColor(tgui::Color::Black);
		continueButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		continueButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { continueButton->setText(L"CONTINUE"); }
		else if (gv->getGameLanguage() == 'r') { continueButton->setText(L"ÏÐÎÄÎËÆÈÒÜ"); }
		continueButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		continueButton->setPosition(halfWinSizeX, halfWinSizeY - round(winSizeX / 18.f));
		continueButton->onPress([=] { gv->setMenuNum(9); });
		gv->gui.add(continueButton, "continueButton");

		tgui::Button::Ptr backToMenuButton = tgui::Button::create();
		backToMenuButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		backToMenuButton->getRenderer()->setTextColor(tgui::Color::Black);
		backToMenuButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		backToMenuButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { backToMenuButton->setText(L"BACK TO MENU"); }
		else if (gv->getGameLanguage() == 'r') { backToMenuButton->setText(L"ÍÀÇÀÄ Â ÌÅÍÞ"); }
		backToMenuButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		backToMenuButton->setPosition(halfWinSizeX, halfWinSizeY);
		backToMenuButton->onPress([=] { gv->setMenuNum(7); });
		gv->gui.add(backToMenuButton, "backToMenuButton");

		tgui::Button::Ptr settingsButton = tgui::Button::create();
		settingsButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		settingsButton->getRenderer()->setTextColor(tgui::Color::Black);
		settingsButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		settingsButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { settingsButton->setText(L"SETTINGS"); }
		else if (gv->getGameLanguage() == 'r') { settingsButton->setText(L"ÍÀÑÒÐÎÉÊÈ"); }
		settingsButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		settingsButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 18.f));
		settingsButton->onPress([=] { gv->setMenuNum(2); });
		gv->gui.add(settingsButton, "settingsButton");

		tgui::Button::Ptr exitButton = tgui::Button::create();
		exitButton->getRenderer()->setBackgroundColorHover(tgui::Color::Yellow);
		exitButton->getRenderer()->setTextColor(tgui::Color::Black);
		exitButton->setSize(round(winSizeX / 4.8f), round(winSizeY / 10.5f));
		exitButton->setOrigin(0.5f, 0.5f);
		if (gv->getGameLanguage() == 'e') { exitButton->setText(L"EXIT"); }
		else if (gv->getGameLanguage() == 'r') { exitButton->setText(L"ÂÛÕÎÄ"); }
		exitButton->setTextSize(static_cast<unsigned int>(round(winSizeX / 45.f)));
		exitButton->setPosition(halfWinSizeX, halfWinSizeY + round(winSizeX / 8.96f));
		exitButton->onPress([=] { gv->setMenuNum(3); });
		gv->gui.add(exitButton, "exitButton");
	}
}

void restartGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec) // game restart function.
{
	entitiesVec.clear();

	gv->setNumberOfPlayers(0);
	gv->setNumberOfEnemies(0);
	gv->setMenuTimer(0.f);

	entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"LeftWall", wallSize)); // create a left wall and throw it into the vector of entities.
	entitiesVec.emplace_back(new Wall(sf::Vector2f(5000.f, 0.f), L"RightWall", wallSize)); // create a right wall and throw it into the vector of entities.
	entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 0.f), L"TopWall", wallSize)); // create a top wall and throw it into the vector of entities.
	entitiesVec.emplace_back(new Wall(sf::Vector2f(0.f, 4936.f), L"BottomWall", wallSize)); // create a bottom wall and throw it into the vector of entities.
	entitiesVec.emplace_back(new Player(gv->playerImage, sf::Vector2f(gv->getPlayerStartPos()), gv->getNickname())); // create a player and throw it into the vector of entities.
	setPlayerPtr(entitiesVec.back().get()); // assign the value of the pointer to the player.
	for (int i = 0; i < 10 + rand() % 41; i++)
	{
		entitiesVec.emplace_back(new Enemy(gv->enemyImage, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)), L"Enemy")); // create an enemy and throw it into the vector of entities.
		gv->setNumberOfEnemies(gv->getNumberOfEnemies() + 1);
	}

	for (int i = 0; i < 20 + rand() % 51; i++)
	{
		entitiesVec.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(static_cast<float>(500 + rand() % 4000), static_cast<float>(500 + rand() % 4000)), L"HPBonus")); // create a HP Bonus and throw it into the vector of entities.
	}

	gv->setNumberOfPlayers(gv->getNumberOfPlayers() + 1);

	for (int i = 0; i < std::size(gv->boxStartPositions); i++)
	{
		entitiesVec.emplace_back(new Box(gv->boxImage, sf::Vector2f(gv->boxStartPositions[i]), L"Box")); // create a box and throw it into the vector of entities.
	}
}

bool s_enterMenu(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec, Minimap& minimap) // enter menu for singleplayer.
{
	gv->menuClock.restart();
	menuEventHandler(gv, minimap);
	gv->setMenuTimer(gv->menuClock.getElapsedTime().asSeconds());

	for (auto& el : entitiesVec)
	{
		Entity* entity = el.get();
		if (getPlayerPtr() != nullptr && (entity->getEntityType() == "Enemy" || entity->getEntityType() == "Player"))
		{
			entity->setMenuTime(gv->getMenuTimer() + entity->getMenuTime());
		}
	}

	gv->gameClock.restart();
	gv->setWindowView(gv->getGameView());
	if (gv->getSinglePlayerGame() == false) { return true; }
	else { return false; }
}

void updateGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec) // game update function. 
{
	gv->setDT(gv->gameClock.restart().asSeconds());
	if (gv->getRestartGame() == true)
	{
		restartGame(gv, entitiesVec);
		gv->setRestartGame(false);
	}

	for (auto& el : entitiesVec)
	{
		auto entity = el.get(); // create a pointer object and assign the value of the first iterator to make the code easier to read.
		if (getPlayerPtr() == nullptr && entity->getEntityType() == "Enemy")
		{
			entity->setIsAlive(false);
			continue;
		}

		for (auto& el2 : entitiesVec)
		{
			auto entity2 = el2.get(); // create a pointer object and assign the value of the first iterator to make the code easier to read.
			collisionHandler(entity, entity2); // calling the collision handling function.	
			if (entity->getEntityType() == "Enemy" && entity2->getEntityType() == "Player") { entity->setAimPos(entity2->getCurrentPos()); }
		}
		if (getPlayerPtr() != nullptr && getPlayerPtr()->getCurrentAmmo() < 30 && getPlayerPtr()->getIsReload() == true && getPlayerPtr()->getReloadTime() >= 2.f)
		{
			getPlayerPtr()->setMissingAmmo(getPlayerPtr()->getMagazineAmmo() - getPlayerPtr()->getCurrentAmmo());
			if (getPlayerPtr()->getMaxAmmo() < getPlayerPtr()->getMagazineAmmo())
			{
				if (getPlayerPtr()->getMaxAmmo() + getPlayerPtr()->getCurrentAmmo() <= 30)
				{
					getPlayerPtr()->setCurrentAmmo(getPlayerPtr()->getCurrentAmmo() + getPlayerPtr()->getMaxAmmo());
					getPlayerPtr()->setMaxAmmo(0);
				}
				else
				{
					int tempAmmo = getPlayerPtr()->getMagazineAmmo() - getPlayerPtr()->getCurrentAmmo();
					getPlayerPtr()->setCurrentAmmo(getPlayerPtr()->getCurrentAmmo() + tempAmmo);
					getPlayerPtr()->setMaxAmmo(getPlayerPtr()->getMaxAmmo() - tempAmmo);
				}
			}
			else
			{
				getPlayerPtr()->setCurrentAmmo(getPlayerPtr()->getCurrentAmmo() + getPlayerPtr()->getMissingAmmo());
				getPlayerPtr()->setMaxAmmo(getPlayerPtr()->getMaxAmmo() - getPlayerPtr()->getMissingAmmo());
			}

			getPlayerPtr()->setIsReload(false);
		}
		if (getPlayerPtr() != nullptr && gv->getNumberOfEnemies() == 0)
		{
			int gc = getPlayerPtr()->getGoldCoins();
			restartGame(gv, entitiesVec);
			getPlayerPtr()->setGoldCoins(gc);
			return;
		}
		if (entity->getIsShoot() == true)
		{
			if (entity->getEntityType() == "Player") // if the entity is a player.
			{
				if (entity->getCurrentAmmo() > 0 && getPlayerPtr()->getIsReload() == false)
				{
					entitiesVec.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), L"Bullet", entity->getName(), gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)))); // create a bullet and throw it into the vector of entities.
					entity->setCurrentAmmo(entity->getCurrentAmmo() - 1);
				}
				entity->setIsShoot(false);
			}
			if (entity->getEntityType() == "Enemy") // if the entity is an enemy.
			{
				float distance = sqrt(((entity->getAimPos().x - entity->getCurrentPos().x) * (entity->getAimPos().x - entity->getCurrentPos().x)) + ((entity->getAimPos().y - entity->getCurrentPos().y) * (entity->getAimPos().y - entity->getCurrentPos().y)));
				if (distance < 750.f)
				{
					entitiesVec.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), L"Bullet", entity->getName(), entity->getAimPos())); // create a bullet and throw it into the vector of entities.
				}
				entity->setIsShoot(false);
			}
		}
		entity->update(gv); // call the update function for all entities.
		if (entity->getIsAlive() == false) // if entity is dead.
		{
			if (entity->getEntityType() == "Box") // if the entity is a Box.
			{
				int itemNum = 0 + rand() % 3;
				{
					if (itemNum == 1)
					{
						for (int i = 0; i < 0 + rand() % 2; i++)
						{
							entitiesVec.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"HPBonus")); // create a HP Bonus and throw it into the vector of entities.
						}
					}
					else if (itemNum == 2)
					{
						for (int i = 0; i < 0 + rand() % 3; i++)
						{
							entitiesVec.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"GoldCoin")); // create a gold coin and throw it into the vector of entities.
						}
					}
				}
			}
			if (entity->getEntityType() == "Player") // if the entity is a player.
			{
				gv->setNumberOfPlayers(gv->getNumberOfPlayers() - 1);
				setPlayerPtr(nullptr);
			}
			if (entity->getEntityType() == "Enemy") // if the entity is an enemy.
			{
				gv->setNumberOfEnemies(gv->getNumberOfEnemies() - 1);
				for (int i = 0; i < 0 + rand() % 6; i++)
				{
					entitiesVec.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), L"GoldCoin")); // create a gold coin and throw it into the vector of entities.
				}

			}
		}
	}

	entitiesVec.erase(std::remove_if(entitiesVec.begin(), entitiesVec.end(), [&](std::unique_ptr<Entity>& entity) { return entity->getIsAlive() == false; }), entitiesVec.end());
	setGameInfo(gv, getPlayerPtr(), entitiesVec.size()); // call the function for setting game information.
}

void drawMinimap(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec)
{
	for (auto& el : entitiesVec)
	{
		Entity* entity = el.get();
		if (entity->getEntityType() == "Player" || entity->getEntityType() == "Enemy") { gv->window.draw(entity->getIcon()); }
		if (entity->getEntityType() == "Wall") { gv->window.draw(entity->getRectHitbox()); }
		if (entity->getEntityType() == "Box") { gv->window.draw(entity->getSprite()); }
	}
}

void drawEntities(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec, Minimap& minimap)
{
	for (auto& el : entitiesVec)
	{
		Entity* entity = el.get();
		if (gv->getShowHitbox() == true || entity->getEntityType() == "Wall") { gv->window.draw(entity->getRectHitbox()); }
		else { gv->window.draw(entity->getSprite()); }
		if (entity->getIsMove() == true && entity->getEntityType() == "Player") { gv->window.draw(gv->playerDestination); }
		if (gv->getShowAimLaser() == true && gv->getFocusEvent() == true && entity->getEntityType() == "Player") { gv->window.draw(gv->aimLaser); }
	}

	for (auto& el : entitiesVec)
	{
		Entity* entity = el.get();
		if (entity->getEntityType() == "Player" || entity->getEntityType() == "Enemy") // if the entity is a player or enemy.
		{
			gv->window.draw(entity->getHPBarOuter());
			gv->window.draw(entity->getHPBarInner());
			if (entity->getIsReload() == true) // if the entity is reloading.
			{
				gv->window.draw(entity->getReloadRectOuter());
				gv->window.draw(entity->getReloadRectInner());
				gv->window.draw(entity->getReloadText());
			}
			gv->window.draw(entity->getHPText());
			gv->window.draw(entity->getNameText());
		}
	}

	minimap.drawBorder(gv);
}

void drawGame(GameVariable* gv, std::vector<std::unique_ptr<Entity>>& entitiesVec, Minimap& minimap) // game drawing function.
{
	gv->window.clear(gv->backgroundColor);
	if (getPlayerPtr() != nullptr) { gv->setGameViewCenter(getPlayerPtr()->getSprite().getPosition()); }
	if (gv->getShowMinimap() == true)
	{
		minimap.setViewCenter(sf::Vector2f((minimap.getView().getSize().x / 2.f) - 300.f, (minimap.getView().getSize().y / 2.f) - 250.f));
		minimap.setBorderPos(sf::Vector2f(gv->getGameViewCenter().x + (0.3f * gv->getGameViewSize().x), gv->getGameViewCenter().y - (0.5f * gv->getGameViewSize().y)));
	}
	gv->setWindowView(gv->getGameView());
	drawEntities(gv, entitiesVec, minimap);
	if (gv->getShowMinimap() == true)
	{
		gv->setWindowView(minimap.getView());
		drawMinimap(gv, entitiesVec);
		gv->setWindowView(gv->getGameView());
	}
	drawGameInfo(gv); // calling the function for drawing game information.
	gv->window.display();
}