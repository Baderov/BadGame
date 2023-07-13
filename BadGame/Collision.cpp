#include "pch.h"
#include "RectangularBoundaryCollision.hpp"
#include "Collision.h"

void collisionHandler(std::unique_ptr<GameVariable>& gv, Entity* entity, Entity* entity2)
{
	if (entity == entity2 || entity == nullptr || entity2 == nullptr || (!(collision::areColliding(entity->getRectHitbox(), entity2->getRectHitbox())))) { return; }

	if (gv->getIsSingleplayer())
	{
		if (dynamic_cast<Bullet*>(entity) && (entity->getCreatorName() != entity2->getName()) && (dynamic_cast<Box*>(entity2) || dynamic_cast<Player*>(entity2) || dynamic_cast<Wall*>(entity2) || dynamic_cast<Enemy*>(entity2)))
		{
			entity->setIsAlive(false);
			entity2->setHP(entity2->getHP() - entity->getHP()); // при попадании пули в сущность - сущность получает урон равной ХП пули.
			//if (!dynamic_cast<Player*>(entity2) && !dynamic_cast<Wall*>(entity2)) { entity2->setIsAlive(false); } // при попадании пули в сущность (кроме игрока или стен) - сущность умирает.
			//if (dynamic_cast<Player*>(entity2)) { entity2->setHP(entity2->getHP() - entity->getHP()); }
		}

		if (dynamic_cast<Player*>(entity))
		{
			if (dynamic_cast<Enemy*>(entity2))
			{
				if (entity->getIsMove()) { entity->setIsMove(false); entity->setSpritePos(entity->getSpritePos() - entity->getStepPos() - entity->getStepPos()); }
				if (entity2->getIsMove()) { entity2->setIsMove(false); entity2->setSpritePos(entity2->getSpritePos() - entity2->getStepPos() - entity2->getStepPos()); }
			}
			if (dynamic_cast<Box*>(entity2) || dynamic_cast<Wall*>(entity2))
			{
				if (entity->getIsMove()) { entity->setIsMove(false); entity->setSpritePos(entity->getSpritePos() - entity->getStepPos()); }
			}
			if (dynamic_cast<Item*>(entity2) && entity2->getName() == L"GoldCoin")
			{
				entity->setGoldCoins(entity->getGoldCoins() + 1);
				entity2->setIsAlive(false);
			}
			if (dynamic_cast<Item*>(entity2) && entity2->getName() == L"HPBonus" && entity->getHP() < 100)
			{
				entity->setHP(entity->getHP() + 30);
				if (entity->getHP() >= 100) { entity->setHP(entity->getHP() - (entity->getHP() - 100)); }
				entity2->setIsAlive(false);
			}
		}

		if (dynamic_cast<Enemy*>(entity))
		{
			if (dynamic_cast<Wall*>(entity2) || dynamic_cast<Box*>(entity2))
			{
				entity->setSpritePos(entity->getSpritePos() - entity->getStepPos());
			}
		}
	}

	else if (gv->getIsMultiplayer())
	{
		if (entity->getIsCollision()) { return; }

		if (dynamic_cast<Client*>(entity) && (dynamic_cast<Client*>(entity2) || dynamic_cast<Wall*>(entity2)))
		{
			if (entity->getIsMove())
			{
				//std::cout << "collisionHandler: move, entity posX : " << entity->getSpritePos().x << " posY : " << entity->getSpritePos().y << "\n";
				entity->setIsCollision(true);
				entity->setIsMove(false);
				sf::Vector2f entityPos = entity->getSpritePos() - entity->getStepPos();
				collisionRequest(gv, entity->getName(), entityPos);
			}
			if (entity2->getIsMove())
			{
				//std::cout << "collisionHandler: move, entity2 posX : " << entity2->getSpritePos().x << " posY : " << entity2->getSpritePos().y << "\n";
				entity2->setIsCollision(true);
				entity2->setIsMove(false);
				sf::Vector2f entity2Pos = entity2->getSpritePos() - entity2->getStepPos();
				collisionRequest(gv, entity2->getName(), entity2Pos);
			}
		}
	}
}