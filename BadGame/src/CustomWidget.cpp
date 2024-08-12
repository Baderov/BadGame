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


// EditBox.
void CustomWidget::updateEditBox()
{
	std::lock_guard<std::mutex> lock(mtx);
	auto editBox = gameGUI.get<tgui::EditBox>("editBox");

	if (!editBox->isMouseDown())
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
	return editBox->isReadOnly();
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


// ListView.
size_t CustomWidget::addClientToPlayersList(std::wstring& clientNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	return playersList->addItem({ clientNick, "-" });
}

void CustomWidget::removeClientFromPlayersList(size_t&& clientID)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->removeItem(clientID);
}

void CustomWidget::changeItemInPlayersList(size_t&& clientID, std::wstring&& clientNick, std::wstring&& ping)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->changeItem(clientID, { clientNick, ping });
}

void CustomWidget::updatePlayersList(GameLanguage&& gameLanguage)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");

	size_t firstColumn = 0;
	size_t secondColumn = 1;

	if (gameLanguage == GameLanguage::English)
	{
		playersList->setColumnText(firstColumn, L"Nickname");
		playersList->setColumnText(secondColumn, L"Ping");
	}
	else if (gameLanguage == GameLanguage::Russian)
	{
		playersList->setColumnText(firstColumn, L"Никнейм");
		playersList->setColumnText(secondColumn, L"Пинг");
	}
}

void CustomWidget::setPlayersListVisible(bool&& isVisible)
{
	std::lock_guard<std::mutex> lock(mtx);
	auto playersList = gameGUI.get<tgui::ListView>("playersList");
	playersList->setVisible(isVisible);
}


// ChatBox.
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