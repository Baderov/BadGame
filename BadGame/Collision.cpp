#include "Collision.h" // file header for collisions.

int tempHP = 0; // initialize a temporary global variable to store HP.

void collisionHandler(Entity* entity, Entity* entity2) // collision handling function.
{
	if (entity->getRectHitbox().getGlobalBounds().intersects(entity2->getRectHitbox().getGlobalBounds()) == true)
	{
		if (dynamic_cast<Bullet*>(entity) && (dynamic_cast<Box*>(entity2) || dynamic_cast<Player*>(entity2) || dynamic_cast<Enemy*>(entity2)) && entity->getCreatorName() != entity2->getName())
		// if the entity is a bullet or box or player or enemy and creator name does not equal entity name.
		{
			entity->setIsAlive(false);
			entity2->setHP(entity2->getHP() - entity->getHP());
		}

		if (dynamic_cast<Player*>(entity)) // if the entity is a player.
		{
			if (dynamic_cast<Box*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Enemy*>(entity2)) // if the entity2 is a box or wall or enemy.
			{
				if (entity->getIsMove() == true)
				{
					entity->setIsMove(false);
				}
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}

			if (entity2->getName() == L"GoldCoin") // if the entity2 name is a gold coin.
			{
				entity->setGoldCoins(entity->getGoldCoins() + 1);
				entity2->setIsAlive(false);
			}
			if (entity2->getName() == L"HPBonus" && entity->getHP() < 100) // if the entity2 name is a HP bonus and entity HP less than 100.
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

		if (dynamic_cast<Enemy*>(entity)) // if the entity is an enemy.
		{
			if (dynamic_cast<Player*>(entity2)) // if the entity2 is a player.
			{
				// for example - hit the player with a sword.
			}

			if (dynamic_cast<Wall*>(entity2) || dynamic_cast<Box*>(entity2)) // if the entity2 is a wall or box.
			{
				entity->setCurrentPos(entity->getCurrentPos() - entity->getStepPos());
			}
		}
	}
}