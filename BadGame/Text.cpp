#include "Text.h" // header file for working with text.

void setGameInfo(GameVariables* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities) // function for setting game information.
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // get mouse coordinates.

	gv->gameInfoText.setString("GAME INFO\nMouse X pos: " + std::to_string(gv->mousePos.x) + "\nMouse Y pos: " + std::to_string(gv->mousePos.y) +
		"\nNumber of entities: " + std::to_string(entities.size()) + "\nFPS: " + std::to_string((int)gv->fps));

	if (player != nullptr) // if the player is alive.
	{
		gv->playerInfoText.setString(std::to_string(player->getGoldCoins()));
		if (gv->gameLanguage == 'e')
		{
			gv->playerAmmoText.setString("Ammo: " + std::to_string(player->getCurrentAmmo()) + "/" + std::to_string(player->getMaxAmmo()));
		}
		else if (gv->gameLanguage == 'r')
		{
			gv->playerAmmoText.setString(L"Патроны: " + std::to_wstring(player->getCurrentAmmo()) + L"/" + std::to_wstring(player->getMaxAmmo()));
		}	
	}

	gv->gameInfoText.setPosition(gv->view.getCenter().x - 600.f, gv->view.getCenter().y - 350.f);
	gv->playerInfoText.setPosition(gv->view.getCenter().x + 700.f, gv->view.getCenter().y - 400.f);
	gv->goldCoinHUDSprite.setPosition(gv->view.getCenter().x + 600.f, gv->view.getCenter().y - 400.f);
	gv->playerAmmoText.setPosition(gv->view.getCenter().x + 500.f, gv->view.getCenter().y + 300.f);

}

void drawGameInfo(GameVariables* gv) // function for drawing game information.
{
	if (gv->showLogs == true) { gv->window.draw(gv->gameInfoText); }
	gv->window.draw(gv->goldCoinHUDSprite);
	gv->window.draw(gv->playerInfoText);
	gv->window.draw(gv->playerAmmoText);
}