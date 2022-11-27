#include "Text.h" // header file for working with text.

void setGameInfo(GameVariable* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities) // function for setting game information.
{
	gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // get mouse coordinates.

	gv->gameInfoText.setString("GAME INFO\nMouse X pos: " + std::to_string(gv->getMousePos().x) + "\nMouse Y pos: " + std::to_string(gv->getMousePos().y) +
		"\nNumber of entities: " + std::to_string(entities.size()) + "\nFPS: " + std::to_string((int)gv->getFPS()));

	if (player != nullptr) // if the player is alive.
	{
		gv->playerInfoText.setString(std::to_string(player->getGoldCoins()));
		if (gv->getGameLanguage() == 'e')
		{
			gv->playerAmmoText.setString("Ammo: " + std::to_string(player->getCurrentAmmo()) + "/" + std::to_string(player->getMaxAmmo()));
		}
		else if (gv->getGameLanguage() == 'r')
		{
			gv->playerAmmoText.setString(L"Патроны: " + std::to_wstring(player->getCurrentAmmo()) + L"/" + std::to_wstring(player->getMaxAmmo()));
		}	
	}

	gv->gameInfoText.setPosition(gv->getViewCenter().x - 600.f, gv->getViewCenter().y - 350.f);
	gv->playerInfoText.setPosition(gv->getViewCenter().x + 700.f, gv->getViewCenter().y - 400.f);
	gv->goldCoinHUDSprite.setPosition(gv->getViewCenter().x + 600.f, gv->getViewCenter().y - 400.f);
	gv->playerAmmoText.setPosition(gv->getViewCenter().x + 500.f, gv->getViewCenter().y + 300.f);

}

void drawGameInfo(GameVariable* gv) // function for drawing game information.
{
	if (gv->getShowLogs() == true) { gv->window.draw(gv->gameInfoText); }
	gv->window.draw(gv->goldCoinHUDSprite);
	gv->window.draw(gv->playerInfoText);
	gv->window.draw(gv->playerAmmoText);
}