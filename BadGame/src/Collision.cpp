#include "pch.h"
#include "RectangularBoundaryCollision.hpp"
#include "Collision.h"

bool collisionHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, Entity* entity1, Entity* entity2)
{
	if (entity1 == entity2 || entity1 == nullptr || entity2 == nullptr || (!(collision::areColliding(entity1->getCollisionRect(), entity2->getCollisionRect())))) { return false; }

	if (gv->getIsSingleplayer())
	{
		if (dynamic_cast<Bullet*>(entity1) && (entity1->getCreatorName() != entity2->getName()) && (dynamic_cast<Box*>(entity2) || dynamic_cast<Player*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Enemy*>(entity2)))
		{
			entity1->setIsAlive(false);
			entity2->setHP(entity2->getHP() - entity1->getHP()); // everyone takes damage.
			//if (!dynamic_cast<Player*>(entity2)) { entity2->setIsAlive(false); } // no one can kill the player, everything else dies with 1 bullet.
		}

		if (dynamic_cast<Enemy*>(entity1) && entity1->getIsMove() && !entity1->getIsCollision())
		{
			if (dynamic_cast<Player*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Box*>(entity2))
			{
				entity1->setIsCollision(true);
				entity1->setIsMove(false);
			}
		}

		if (dynamic_cast<Player*>(entity1) && entity1->getIsMove() && !entity1->getIsCollision())
		{
			if (dynamic_cast<Enemy*>(entity2) || dynamic_cast<Box*>(entity2) || dynamic_cast<Wall*>(entity2))
			{
				entity1->setIsCollision(true);
				entity1->setIsMove(false);
			}

			if (dynamic_cast<Item*>(entity2) && entity2->getItemType() == ItemType::GoldCoin)
			{
				entity1->setGoldCoins(entity1->getGoldCoins() + 1);
				entity2->setIsAlive(false);
			}

			if (dynamic_cast<Item*>(entity2) && entity2->getItemType() == ItemType::Health && entity1->getHP() < 100)
			{
				entity1->setHP(entity1->getHP() + 30);
				if (entity1->getHP() >= 100) { entity1->setHP(entity1->getHP() - (entity1->getHP() - 100)); }
				entity2->setIsAlive(false);
			}
		}
	}

	else if (gv->getIsMultiplayer())
	{
		if (dynamic_cast<Bullet*>(entity1) && (entity1->getCreatorName() != entity2->getName()) && (dynamic_cast<Box*>(entity2) || dynamic_cast<Player*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Client*>(entity2)))
		{
			entity1->setIsAlive(false);
			//entity2->setHP(entity2->getHP() - entity1->getHP()); // everyone takes damage.
			//if (!dynamic_cast<Player*>(entity2)) { entity2->setIsAlive(false); } // no one can kill the player, everything else dies with 1 bullet.
		}

		if (dynamic_cast<Client*>(entity1) && (dynamic_cast<Client*>(entity2) || dynamic_cast<Wall*>(entity2)))
		{
			entity1->setIsCollision(true);
			if (!entity1->getIsGhost() && entity1->getIsMove())
			{
				entity1->setIsMove(false);
			}
		}
	}

	return true;
}