#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "ObjectPool.hpp"
#include "Collision.h"

class Enemy : public Entity
{
private:
	static unsigned int enemyID;
public:
	explicit Enemy(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos);
	void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
	void dropItem(std::unique_ptr<GameVariable>& gv);
	void shoot(std::unique_ptr<GameVariable>& gv, std::unique_ptr<SingleplayerManager>& sm);
};

inline ObjectPool<Enemy> enemiesPool;
inline std::mutex enemies_mtx;
inline std::vector<std::unique_ptr<Enemy>> enemiesVec;

#endif