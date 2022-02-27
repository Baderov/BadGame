#include "Text.h" // ���������� ������������ ����.

void setGameInfo(GameVariables* gv, Entity* player, std::list<std::unique_ptr<Entity>>& entities) // ������� ��������� ������� ����������.
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window));//��������� �� � ������� (������ �� ����� ����)

	gv->gameInfoText.setString("GAME INFO\nMouse X pos: " + std::to_string(gv->mousePos.x) + "\nMouse Y pos: " + std::to_string(gv->mousePos.y) +
		"\nNumber of entities: " + std::to_string(entities.size()) + "\nFPS: " + std::to_string((int)gv->fps));

	if (player != nullptr)
	{
		gv->playerInfoText.setString(std::to_string(player->getGoldCoins())); // ������������� �����.
		gv->playerAmmoText.setString("Ammo: " + std::to_string(player->getCurrentAmmo()) + "/" + std::to_string(player->getMaxAmmo())); // ������������� �����.
	}

	gv->gameInfoText.setPosition(gv->view.getCenter().x - 600.f, gv->view.getCenter().y - 350.f);
	gv->playerInfoText.setPosition(gv->view.getCenter().x + 700.f, gv->view.getCenter().y - 400.f);
	gv->goldCoinHUDSprite.setPosition(gv->view.getCenter().x + 600.f, gv->view.getCenter().y - 400.f);
	gv->playerAmmoText.setPosition(gv->view.getCenter().x + 500.f, gv->view.getCenter().y + 300.f);

}

void drawGameInfo(GameVariables* gv) // ������� ������� ������� ����������.
{
	if (gv->showLogs == true) { gv->window.draw(gv->gameInfoText); } // ������ �����.
	gv->window.draw(gv->goldCoinHUDSprite);
	gv->window.draw(gv->playerInfoText); // ������ �����.
	gv->window.draw(gv->playerAmmoText); // ������ �����.
}