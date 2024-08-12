#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"
#include "ObjectPool.hpp"
#include "Collision.h"

class Client : public Entity
{
private:
	size_t playersListID;
	sf::Int32 ping;
	sf::Clock pingClock;
public:
	const sf::Int32 pingDelay = 100;

	explicit Client(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	void init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, sf::Vector2f startPos, std::wstring name);
	void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;

	size_t getPlayersListID();
	sf::Int32 getPing();
	sf::Int32 getPingClockElapsedTime();

	void setPlayersListID(size_t playersListID);
	void setPing(sf::Int32 ping);
};

inline ObjectPool<Client> clientsPool;
inline std::mutex clients_mtx;
inline std::vector<std::unique_ptr<Client>> clientsVec;

#endif