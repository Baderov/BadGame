#include "pch.h"
#include "ServerIsNotAvailable.h"

void setServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw)
{
	gv->connectionErrorRS.setSize(sf::Vector2f(1000.f, 300.f));
	gv->connectionErrorRS.setFillColor(sf::Color(0, 0, 0, 200));
	gv->connectionErrorRS.setOrigin(gv->connectionErrorRS.getSize() / 2.f);
	gv->connectionErrorRS.setPosition(gw->getGameViewCenter());
	gv->OKButtonRS.setSize(sf::Vector2f(130.f, 130.f));
	gv->OKButtonRS.setFillColor(sf::Color(255, 255, 255, 200));
	gv->OKButtonRS.setOrigin(gv->OKButtonRS.getSize() / 2.f);
	gv->OKButtonRS.setPosition(gv->connectionErrorRS.getPosition().x, gv->connectionErrorRS.getPosition().y + 40.f);

	gv->connectionErrorText.setFont(gv->consolasFont);
	gv->connectionErrorText.setCharacterSize(70);
	gv->connectionErrorText.setFillColor(sf::Color::Red);
	if (gv->getGameLanguage() == GameLanguage::English) { gv->connectionErrorText.setString(L"SERVER IS NOT AVAILABLE!"); }
	else if (gv->getGameLanguage() == GameLanguage::Russian) { gv->connectionErrorText.setString(L"яепбеп меднярсоем!"); }
	gv->connectionErrorText.setOrigin(round(gv->connectionErrorText.getLocalBounds().left + (gv->connectionErrorText.getLocalBounds().width / 2.f)), round(gv->connectionErrorText.getLocalBounds().top + (gv->connectionErrorText.getLocalBounds().height / 2.f)));
	gv->connectionErrorText.setPosition(gv->connectionErrorRS.getPosition().x, gv->connectionErrorRS.getPosition().y - 80.f);

	gv->OKButtonText.setFont(gv->consolasFont);
	gv->OKButtonText.setCharacterSize(70);
	gv->OKButtonText.setFillColor(sf::Color::Black);
	gv->OKButtonText.setString("OK");
	gv->OKButtonText.setOrigin(round(gv->OKButtonText.getLocalBounds().left + (gv->OKButtonText.getLocalBounds().width / 2.f)), round(gv->OKButtonText.getLocalBounds().top + (gv->OKButtonText.getLocalBounds().height / 2.f)));
	gv->OKButtonText.setPosition(gv->OKButtonRS.getPosition());
}

void updateServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	if (nm->getServerIsNotAvailable())
	{
		setServerIsNotAvailable(gv, gw);

		gv->OKButtonRS.setFillColor(sf::Color(255, 255, 255, 200));
		if (gv->OKButtonRS.getGlobalBounds().contains(gv->getMousePos().x, gv->getMousePos().y) && nm->getServerIsNotAvailable())
		{
			networkAction = NetworkAction::ServerIsNotAvailable;
			gv->OKButtonRS.setFillColor(sf::Color::White);
		}

		cw->setChatBoxEnabled(false);
		cw->setEditBoxText("");
		cw->setEditBoxEnabled(false);
	}
}

void drawServerIsNotAvailable(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<NetworkManager>& nm)
{
	if (nm->getServerIsNotAvailable() && gv->getIsMultiplayer())
	{
		gw->window.draw(gv->connectionErrorRS);
		gw->window.draw(gv->OKButtonRS);
		gw->window.draw(gv->connectionErrorText);
		gw->window.draw(gv->OKButtonText);
	}
}