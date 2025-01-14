#include "pch.h"
#include "CustomWidget.h"

CustomWidget::CustomWidget(std::unique_ptr<GameWindow>& gw) { updateGUI(gw); }

void CustomWidget::updateGUI(std::unique_ptr<GameWindow>& gw)
{
	tempGameLanguage = GameLanguage::English;
	tempWindowSize = sf::Vector2u(0, 0);
	tempFPSLimiter = 0;
	tempIsFullscreen = false;
	tempIsVsync = false;

	menuGUI.setWindow(gw->window);
	gameGUI.setWindow(gw->window);

	tguiFont.setGlobalFont("Fonts\\consolas.ttf");

	menuGUI.setFont(tguiFont);
	gameGUI.setFont(tguiFont);
}

GameLanguage CustomWidget::getTempGameLanguage()
{
	std::lock_guard<std::mutex> lock(mtx);
	GameLanguage tempGameLanguage = this->tempGameLanguage;
	return tempGameLanguage;
}
sf::Vector2u CustomWidget::getTempWindowSize()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Vector2u tempWindowSize = this->tempWindowSize;
	return tempWindowSize;
}
unsigned int CustomWidget::getTempFPSLimiter()
{
	std::lock_guard<std::mutex> lock(mtx);
	unsigned int tempFPSLimiter = this->tempFPSLimiter;
	return tempFPSLimiter;
}
bool CustomWidget::getTempIsFullscreen()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool tempIsFullscreen = this->tempIsFullscreen;
	return tempIsFullscreen;
}
bool CustomWidget::getTempIsVsync()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool tempIsVsync = this->tempIsVsync;
	return tempIsVsync;
}


void CustomWidget::setTempGameLanguage(GameLanguage tempGameLanguage)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempGameLanguage = std::move(tempGameLanguage);
}
void CustomWidget::setTempWindowSize(sf::Vector2u tempWindowSize)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempWindowSize = std::move(tempWindowSize);
}
void CustomWidget::setTempFPSLimiter(unsigned int tempFPSLimiter)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempFPSLimiter = std::move(tempFPSLimiter);
}
void CustomWidget::setTempIsFullscreen(bool tempIsFullscreen)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempIsFullscreen = std::move(tempIsFullscreen);
}
void CustomWidget::setTempIsVsync(bool tempIsVsync)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempIsVsync = std::move(tempIsVsync);
}



// MultiplayerMenu.
void CustomWidget::enableMultiplayerMenuWidgets()
{
	std::lock_guard<std::mutex> lock(mtx);

	tgui::EditBox::Ptr nicknameEditBox = menuGUI.get<tgui::EditBox>("nicknameEditBox");
	tgui::EditBox::Ptr IPEditBox = menuGUI.get<tgui::EditBox>("IPEditBox");
	tgui::EditBox::Ptr portEditBox = menuGUI.get<tgui::EditBox>("portEditBox");
	tgui::Button::Ptr connectButton = menuGUI.get<tgui::Button>("connectButton");
	tgui::Button::Ptr backButton = menuGUI.get<tgui::Button>("backButton");

	nicknameEditBox->setEnabled(true);
	IPEditBox->setEnabled(true);
	portEditBox->setEnabled(true);
	connectButton->setEnabled(true);
	backButton->setEnabled(true);
}

void CustomWidget::disableMultiplayerMenuWidgets()
{
	std::lock_guard<std::mutex> lock(mtx);

	tgui::EditBox::Ptr nicknameEditBox = menuGUI.get<tgui::EditBox>("nicknameEditBox");
	tgui::EditBox::Ptr IPEditBox = menuGUI.get<tgui::EditBox>("IPEditBox");
	tgui::EditBox::Ptr portEditBox = menuGUI.get<tgui::EditBox>("portEditBox");
	tgui::Button::Ptr connectButton = menuGUI.get<tgui::Button>("connectButton");
	tgui::Button::Ptr backButton = menuGUI.get<tgui::Button>("backButton");

	nicknameEditBox->setEnabled(false);
	IPEditBox->setEnabled(false);
	portEditBox->setEnabled(false);
	connectButton->setEnabled(false);
	backButton->setEnabled(false);
}




// Button.
bool CustomWidget::connectButtonIsEnabled()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto connectButton = menuGUI.get<tgui::Button>("connectButton");
	return connectButton->isEnabled();
}

// Label.
void CustomWidget::setErrorLabelText(tgui::String&& text)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto errorLabel = menuGUI.get<tgui::Label>("errorLabel");
	errorLabel->setText(text);
}




// KillList
void CustomWidget::updateKillListTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto killList = gameGUI.get<tgui::ChatBox>("killList");

	this->killListTime = killListClock.getElapsedTime().asMilliseconds();

	if (this->killListTime >= 10000)
	{
		killList->removeAllLines();
		killListClock.restart();
	}
}

void CustomWidget::createKillList(std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw)
{
	std::lock_guard<std::mutex> lock(mtx);
	float winSizeX = static_cast<float>(gw->window.getSize().x);

	tgui::ChatBox::Ptr killList = tgui::ChatBox::create();
	killList->getRenderer()->setBackgroundColor(sf::Color::Transparent);
	killList->getRenderer()->setBorders(tgui::Borders(0.f, 0.f, 0.f, 0.f));
	killList->setLinesStartFromTop(true);
	killList->setTextSize(static_cast<unsigned int>(round(winSizeX / 80.f)));
	killList->setSize("30%", "30%");
	killList->setOrigin(0.5f, 0.5f);
	killList->setPosition("17%", "20%");
	killList->setTextStyle(tgui::TextStyle::Bold);
	cw->gameGUI.add(killList, "killList");
}

void CustomWidget::updateKillList(std::unique_ptr<GameWindow>& gw)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto killList = gameGUI.get<tgui::ChatBox>("killList");
	float winSizeX = static_cast<float>(gw->window.getSize().x);

	killList->setTextSize(static_cast<unsigned int>(round(winSizeX / 80.f)));
	killList->setSize("30%", "30%");
	killList->setOrigin(0.5f, 0.5f);
	killList->setPosition("17%", "20%");
}

void CustomWidget::addKillText(std::wstring& shooterClientNick, std::wstring& deadClientNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto killList = gameGUI.get<tgui::ChatBox>("killList");
	if (killList->getLineAmount() < 8)
	{
		killList->addLine(shooterClientNick + L" kills " + deadClientNick, tgui::Color::Blue);
	}
	else
	{
		killList->removeLine(0);
		killList->addLine(shooterClientNick + L" kills " + deadClientNick, tgui::Color::Blue);
	}
	killListClock.restart();
}



// Chat.
void CustomWidget::createChat(std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw)
{
	std::lock_guard<std::mutex> lock(mtx);
	float winSizeX = static_cast<float>(gw->window.getSize().x);

	tgui::ChatBox::Ptr chatBox = tgui::ChatBox::create();
	chatBox->getRenderer()->setBackgroundColor(tgui::Color(0, 51, 102));
	chatBox->getRenderer()->setBorders(tgui::Borders(4.f, 4.f, 4.f, 4.f));
	chatBox->getRenderer()->setBorderColor(tgui::Color::Black);
	chatBox->getRenderer()->setScrollbarWidth(24.f);
	chatBox->setScrollbarValue(2000);
	chatBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 75.f)));
	chatBox->setSize("30%", "30%");
	chatBox->setOrigin(0.5f, 0.5f);
	chatBox->setPosition("20%", "70%");
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
}

void CustomWidget::updateChat(std::unique_ptr<GameWindow>& gw)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto chatBox = gameGUI.get<tgui::ChatBox>("chatBox");
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	float winSizeX = static_cast<float>(gw->window.getSize().x);

	chatBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 75.f)));
	chatBox->setSize("30%", "30%");
	chatBox->setOrigin(0.5f, 0.5f);
	chatBox->setPosition("20%", "70%");

	editBox->setSize("30%", "7%");
	editBox->setOrigin(0.5f, 0.5f);
	editBox->setPosition("20%", "88%");
	editBox->setTextSize(static_cast<unsigned int>(round(winSizeX / 75.f)));

}

void CustomWidget::addLineToChatBox(tgui::String&& text, tgui::Color&& color)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto chatBox = gameGUI.get<tgui::ChatBox>("chatBox");
	chatBox->addLine(text, color);
}

void CustomWidget::setChatBoxVisible(bool&& isVisible)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto chatBox = gameGUI.get<tgui::ChatBox>("chatBox");
	chatBox->setVisible(isVisible);
}

void CustomWidget::setChatBoxEnabled(bool&& isEnabled)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto chatBox = gameGUI.get<tgui::ChatBox>("chatBox");
	chatBox->setEnabled(isEnabled);
}

bool CustomWidget::chatBoxIsVisible()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto chatBox = gameGUI.get<tgui::ChatBox>("chatBox");
	return chatBox->isVisible();
}

void CustomWidget::updateEditBox()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");

	if (editBox != nullptr && !editBox->isMouseDown())
	{
		editBox->setReadOnly(true);
		editBox->getRenderer()->setBackgroundColor(tgui::Color(0, 51, 102));
		editBox->getRenderer()->setBackgroundColorHover(tgui::Color(0, 51, 102));
	}
}

void CustomWidget::setEditBoxVisible(bool&& isVisible)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	editBox->setVisible(isVisible);
}

void CustomWidget::setEditBoxEnabled(bool&& isEnabled)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	editBox->setEnabled(isEnabled);
}

void CustomWidget::setEditBoxText(tgui::String&& text)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	editBox->setText(text);
}

bool CustomWidget::editBoxIsReadOnly()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	if (editBox != nullptr) { return editBox->isReadOnly(); }
	else { return false; }
}

bool CustomWidget::editBoxIsVisible()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	return editBox->isVisible();
}

const tgui::String& CustomWidget::getEditBoxText()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");
	return editBox->getText();
}






// PlayersList.
void CustomWidget::createPlayersList(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<CustomWidget>& cw)
{
	std::lock_guard<std::mutex> lock(mtx);
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	float columnWidth = gw->window.getSize().x / 5.5f;
	unsigned int itemHeight = static_cast<unsigned int>(round(winSizeX / 35.f));

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
	playersList->setResizableColumns(false);
	playersList->setShowVerticalGridLines(true);
	playersList->setShowHorizontalGridLines(true);
	playersList->setExpandLastColumn(true);
	playersList->setItemHeight(itemHeight);
	playersList->setHeaderHeight(round(winSizeX / 35.f));
	playersList->setSize(static_cast<unsigned int>(round(winSizeX / 1.6f)), itemHeight * 13);
	playersList->setTextSize(static_cast<unsigned int>(round(winSizeX / 42.f)));
	playersList->setOrigin(0.5f, 0.5f);
	playersList->setPosition("50%", "50%");
	playersList->setVisible(false);
	playersList->onItemSelect([playersList]()
		{
			playersList->deselectItems();
		});
	if (gv->getGameLanguage() == GameLanguage::English)
	{
		playersList->addColumn(L"Nickname", columnWidth * 1.35f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Kills", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Deaths", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Ping", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		playersList->addColumn(L"Никнейм", columnWidth * 1.35f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Убийства", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Смерти", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
		playersList->addColumn(L"Пинг", columnWidth / 1.6f, tgui::ListView::ColumnAlignment::Center);
	}
	cw->gameGUI.add(playersList, "playersList");
}

size_t CustomWidget::addClientToPlayersList(std::wstring& clientNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	size_t index = playersList->addItem({ clientNick, L"0", L"0", L"-" });
	return index;
}

void CustomWidget::removeClientFromPlayersList(size_t&& clientID)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->removeItem(clientID);
}

void CustomWidget::changeItemInPlayersList(size_t&& clientID, std::wstring&& clientNick, std::wstring&& numOfKills, std::wstring&& numOfDeaths, std::wstring&& ping)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->changeItem(clientID, { clientNick, numOfKills, numOfDeaths, ping });
}

void CustomWidget::updatePlayersList(std::unique_ptr<GameWindow>& gw, std::unique_ptr<GameVariable>& gv)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	float winSizeX = static_cast<float>(gw->window.getSize().x);
	unsigned int itemHeight = static_cast<unsigned int>(round(winSizeX / 35.f));
	float columnWidth = gw->window.getSize().x / 5.5f;

	size_t firstColumn = 0;
	size_t secondColumn = 1;
	size_t thirdColumn = 2;
	size_t fourthColumn = 3;

	if (gv->getGameLanguage() == GameLanguage::English)
	{
		playersList->setColumnText(firstColumn, L"Nickname");
		playersList->setColumnText(secondColumn, L"Kills");
		playersList->setColumnText(thirdColumn, L"Deaths");
		playersList->setColumnText(fourthColumn, L"Ping");
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		playersList->setColumnText(firstColumn, L"Никнейм");
		playersList->setColumnText(secondColumn, L"Убийства");
		playersList->setColumnText(thirdColumn, L"Смерти");
		playersList->setColumnText(fourthColumn, L"Пинг");
	}

	playersList->setColumnWidth(0, columnWidth * 1.35f);
	playersList->setColumnWidth(1, columnWidth / 1.6f);
	playersList->setColumnWidth(2, columnWidth / 1.6f);
	playersList->setColumnWidth(3, columnWidth / 1.6f);

	playersList->setItemHeight(itemHeight);
	playersList->setHeaderHeight(round(winSizeX / 35.f));
	playersList->setSize(static_cast<unsigned int>(round(winSizeX / 1.6f)), itemHeight * 13);
	playersList->setTextSize(static_cast<unsigned int>(round(winSizeX / 42.f)));
	playersList->setOrigin(0.5f, 0.5f);
	playersList->setPosition("50%", "50%");
}

void CustomWidget::setPlayersListVisible(bool&& isVisible)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->setVisible(isVisible);
}






// GUI.
void CustomWidget::handleGameGUIEvent(sf::Event& event)
{
	std::lock_guard<std::mutex> lock(mtx);
	gameGUI.handleEvent(event);
}

void CustomWidget::drawGameGUI()
{
	std::lock_guard<std::mutex> lock(mtx);
	gameGUI.draw();
}