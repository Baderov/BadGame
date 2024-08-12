#ifndef WALL_H
#define WALL_H

#include "Entity.h"
#include "ObjectPool.hpp"
#include "Collision.h"

class Wall : public Entity
{
private:
	static unsigned int wallID;
public:
	explicit Wall(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, WallType wallType);
	void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
};

inline ObjectPool<Wall> wallsPool;
inline std::mutex walls_mtx;
inline std::vector<std::unique_ptr<Wall>> wallsVec;

#endif