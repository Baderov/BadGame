#include "GameUpdate.h" // ���������� ������������ ���� ���������� ����.

void boxSpawn(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities)
{
	for (int i = 0; i < std::size(gv->boxStartPositions); i++)
	{
		entities.emplace_back(new Box(gv->boxImage, sf::Vector2f(gv->boxStartPositions[i]), "Box")); // ������ ������� � ���������� � ����� ������.
	}
}

void restartGame(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, Entity*& player)
{
	gv->view.setSize(1920.f, 1080.f);

	entities.clear();

	gv->numberOfPlayers = 0;
	gv->numberOfEnemies = 0;
	gv->menuTimer = 0;

	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 0.f), "LeftWall"));
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(3000.f, 0.f), "RightWall"));
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 0.f), "TopWall"));
	entities.emplace_back(new Wall(gv->wallImage, sf::Vector2f(0.f, 2936.f), "BottomWall"));
	entities.emplace_back(new Player(gv->playerImage, sf::Vector2f(gv->playerStartPos), gv->nickname)); // �������� ����� � ������������ � ������ entities(������, ����, ������� � �.�).
	player = entities.back().get();

	for (int i = 0; i < 10 + rand() % 21; i++)
	{
		entities.emplace_back(new Enemy(gv->enemyImage, sf::Vector2f(100 + rand() % 2600, 100 + rand() % 2600), "Enemy"));
		gv->numberOfEnemies++;
	}

	for (int i = 0; i < 20 + rand() % 31; i++)
	{
		entities.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(100 + rand() % 2600, 100 + rand() % 2600), "HPBonus"));
	}

	gv->numberOfPlayers++;

	boxSpawn(gv, entities);
}

void updateEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it, std::list<std::unique_ptr<Entity>>::iterator& it2, Entity*& player) // ������� ���������� ���������.
{
	for (it = entities.begin(); it != entities.end();) // ���������� �� ������ �� ������ �� �����.
	{
		Entity* entity = (*it).get(); // ������ ������-��������� � ����������� �������� ������� ��������� ��� ���������� ������ ����.
		if (player == nullptr && dynamic_cast<Enemy*>(entity))
		{
			entity->setIsAlive(false);
		}
		for (it2 = entities.begin(); it2 != entities.end(); it2++) // ���������� �� ������ �� ������ �� �����.
		{
			Entity* entity2 = (*it2).get(); // ������ ������-��������� � ����������� �������� ������� ��������� ��� ���������� ������ ����.
			collision(entity, entity2); // ����� ������� ��������� ��������.			
			if (dynamic_cast<Enemy*>(entity) && dynamic_cast<Player*>(entity2))
			{
				entity->setAimPos(entity2->getCurrentPos());
			}
		}

		if (player != nullptr && player->getCurrentAmmo() < 30 && player->getIsReload() == true && player->getReloadTime() >= 2000)
		{
			player->setMissingAmmo(player->getMagazineAmmo() - player->getCurrentAmmo());
			if (player->getMaxAmmo() < player->getMagazineAmmo())
			{
				player->setCurrentAmmo(player->getCurrentAmmo() + player->getMaxAmmo());
				player->setMaxAmmo(0);
			}
			else
			{
				player->setCurrentAmmo(player->getCurrentAmmo() + player->getMissingAmmo());
				player->setMaxAmmo(player->getMaxAmmo() - player->getMissingAmmo());
			}

			player->setIsReload(false);
		}

		if (gv->numberOfEnemies == 0 && player != nullptr)
		{
			int gc = player->getGoldCoins();
			restartGame(gv, entities, player);
			player->setGoldCoins(gc);
			return;
		}		
		if (entity->getIsShoot() == true)
		{
			if (dynamic_cast<Player*>(entity))
			{
				if (entity->getCurrentAmmo() > 0 && player->getIsReload() == false)
				{
					entities.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), "Bullet", entity->getName(), gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)))); // ������ ���� � ���������� � ����� ������.
					entity->setCurrentAmmo(entity->getCurrentAmmo() - 1);
				}
				entity->setIsShoot(false);
			}
			if (dynamic_cast<Enemy*>(entity))
			{
				float distance = sqrt(((entity->getAimPos().x - entity->getCurrentPos().x) * (entity->getAimPos().x - entity->getCurrentPos().x)) + ((entity->getAimPos().y - entity->getCurrentPos().y) * (entity->getAimPos().y - entity->getCurrentPos().y)));
				if (distance < 750.f)
				{
					entities.emplace_back(new Bullet(gv->bulletImage, sf::Vector2f(entity->getCurrentPos()), "Bullet", entity->getName(), entity->getAimPos())); // ������ ���� � ���������� � ����� ������.
				}
				entity->setIsShoot(false);
			}
		}

		entity->update(gv); // �������� ������� update ��� ���� ��������.
		if (entity->getIsAlive() == false) // ���� ���� ������ �����
		{
			if (dynamic_cast<Box*>(entity)) // ���� �������� ��� �������.
			{
				int itemNum = 0 + rand() % 3;
				{
					if (itemNum == 1)
					{
						for (int i = 0; i < 0 + rand() % 2; i++)
						{
							entities.emplace_back(new Item(gv->hpBonusImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), "HPBonus"));
						}
					}
					else if (itemNum == 2)
					{
						for (int i = 0; i < 0 + rand() % 3; i++)
						{
							entities.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), "GoldCoin"));
						}
					}
				}
			}
			if (dynamic_cast<Player*>(entity)) // ���� �������� ��� �����.
			{
				gv->numberOfPlayers--; // ��������� ���������� �������.
				player = nullptr;
			}
			if (dynamic_cast<Enemy*>(entity)) // ���� �������� ��� ����.
			{
				gv->numberOfEnemies--; // ��������� ���������� ������. 			
				for (int i = 0; i < 0 + rand() % 6; i++)
				{
					entities.emplace_back(new Item(gv->goldCoinImage, sf::Vector2f(entity->getCurrentPos().x + (i * 15), entity->getCurrentPos().y), "GoldCoin"));
				}
			}
			it = entities.erase(it); // ������� �������.
		}
		else it++; // ���� ���������� � ���� �������, � ������ ��� �� ����� ��������� ������.
	}
}

void drawEntities(GameVariables* gv, std::list<std::unique_ptr<Entity>>& entities, std::list<std::unique_ptr<Entity>>::iterator& it) // ������� ������� ���������.
{	
	if (gv->showAimLaser == true)
	{
		gv->window.draw(gv->aimLaser);
	}
	for (it = entities.begin(); it != entities.end(); it++) // ���������� �� ������ �� ������ �� �����.
	{
		if (gv->showHitbox == true) // ���� ���������� ��������.
		{
			gv->window.draw((*it)->getRectHitbox());	// ������ ������������� ��������.
		}
		else // ���� �� ���������� ��������.
		{
			gv->window.draw((*it)->getSprite()); // ������ ������� ���������.
		}

		if ((*it)->getIsMove() == true && dynamic_cast<Player*>((*it).get())) // ���� ����� ���������.
		{
			gv->window.draw(gv->playerDestination); // ������ �����.
		}
	}
	for (it = entities.begin(); it != entities.end(); it++) // ���������� �� ������ �� ������ �� �����.
	{
		if (dynamic_cast<Player*>((*it).get()) || dynamic_cast<Enemy*>((*it).get()))
		{
			gv->window.draw((*it)->getHPBarOuter());
			gv->window.draw((*it)->getHPBarInner());
			if ((*it)->getIsReload() == true)
			{
				gv->window.draw((*it)->getReloadRectOuter());
				gv->window.draw((*it)->getReloadRectInner());
				gv->window.draw((*it)->getReloadText());
			}
			gv->window.draw((*it)->getHPText());
			gv->window.draw((*it)->getNameText());
		}
	}
}