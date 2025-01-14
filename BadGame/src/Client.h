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
	sf::Vector2f newPos;
	bool moveReceived;
	bool sendMoveRequest;
	bool isBot;
public:
	const sf::Int32 pingDelay = 100;

	explicit Client(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm);
	void init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, std::wstring name, sf::Vector2f startPos, int HP);
	void respawn(sf::Vector2f startPos);
	void update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw) override;
	void move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void checkCollision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;
	void createBullet(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm,
	sf::Vector2f&& startPos, sf::Vector2f&& aimPos, std::wstring&& creatorName, sf::Vector2f&& currentVelocity);
	void shoot(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw);


	size_t getPlayersListID();
	sf::Int32 getPing();
	sf::Int32 getPingClockElapsedTime();
	sf::Vector2f getNewPos();
	bool getMoveReceived();
	bool getSendMoveRequest();
	bool getIsBot();

	void setPlayersListID(size_t playersListID);
	void setPing(sf::Int32 ping);
	void setNewPos(sf::Vector2f newPos);
	void setMoveReceived(bool moveReceived);
	void setSendMoveRequest(bool sendMoveRequest);
	void setIsBot(bool isBot);
};

inline ObjectPool<Client> clientsPool;
inline std::mutex clients_mtx;
inline std::vector<std::unique_ptr<Client>> clientsVec;

#endif