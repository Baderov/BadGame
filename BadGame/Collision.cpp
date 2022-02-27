#include "Collision.h" // подключаем заголовочный файл.

int tempHP = 0;

void collision(Entity* entity, Entity* entity2) // функция обработки коллизий.
{
	if (entity->getRectHitbox().getGlobalBounds().intersects(entity2->getRectHitbox().getGlobalBounds()) == true)
	{
		if (dynamic_cast<Bullet*>(entity) && (dynamic_cast<Box*>(entity2) || dynamic_cast<Player*>(entity2) || dynamic_cast<Enemy*>(entity2)) && entity->getCreatorName() != entity2->getName())
		{
			entity->setIsAlive(false);
			entity2->setHP(entity2->getHP() - entity->getHP());
		}

		if (dynamic_cast<Player*>(entity))
		{
			if (dynamic_cast<Box*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Enemy*>(entity2))
			{
				if (entity->getIsMove() == true)
				{
					entity->setIsMove(false);
				}
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}

			if (entity2->getName() == "GoldCoin")
			{
				entity->setGoldCoins(entity->getGoldCoins() + 1);
				entity2->setIsAlive(false);
			}
			if (entity2->getName() == "HPBonus" && entity->getHP() < 100)
			{
				entity->setHP(entity->getHP() + 30);
				if (entity->getHP() >= 100)
				{
					tempHP = entity->getHP() - 100;
					entity->setHP(entity->getHP() - tempHP);
				}
				entity2->setIsAlive(false);
			}
		}

		if (dynamic_cast<Enemy*>(entity))
		{
			if (dynamic_cast<Player*>(entity2))
			{
				// ударить игрока мечом.
			}

			if (dynamic_cast<Wall*>(entity2) || dynamic_cast<Box*>(entity2))
			{
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}
		}
	}
}