#ifndef COLLISION_H
#define COLLISION_H

#include "Variables.h"
#include "Network.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Box.h"
#include "Client.h"
#include "Item.h"
#include "Wall.h"

void collisionHandler(std::unique_ptr<GameVariable>& gv, Entity* entity, Entity* entity2);

#endif