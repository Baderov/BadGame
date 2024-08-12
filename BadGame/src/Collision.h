#ifndef COLLISION_H
#define COLLISION_H

#include "ClientRequest.h"
#include "Wall.h"
#include "Box.h"
#include "Bullet.h"
#include "Client.h"
#include "Item.h"
#include "Enemy.h"
#include "Player.h"

bool collisionHandler(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, Entity* entity1, Entity* entity2);

#endif