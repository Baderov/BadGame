#include "pch.h"
#include "ObjectPool.hpp"
#include "ClientRequest.h"

void connectToServerRequest(std::unique_ptr<GameVariable>& gv) // function to connect to the server.
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"regNick";
	packet << prefix << gv->getNickname();
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void messageRequest(std::unique_ptr<GameVariable>& gv, Chat& chat) // function to send message to the server.
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"msg";
	packet << prefix << gv->getNickname() << chat.getUserStr() << chat.getNumOfLinesInUserTextBox();
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void moveRequest(std::unique_ptr<GameVariable>& gv, sf::Vector2f currentClientStepPos) // sending a move request to the server
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"move";
	packet << prefix << gv->getNickname() << std::move(currentClientStepPos.x) << std::move(currentClientStepPos.y);
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void collisionRequest(std::unique_ptr<GameVariable>& gv, std::wstring entityName, sf::Vector2f entityPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"collision";
	packet << prefix << std::move(entityName) << std::move(entityPos.x) << std::move(entityPos.y);
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void createBulletRequest(std::unique_ptr<GameVariable>& gv, std::wstring bulletName, std::wstring creatorName, sf::Vector2f aimPos, sf::Vector2f bulletPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"createBullet";
	packet << prefix << std::move(bulletName) << std::move(creatorName) << std::move(aimPos.x) << std::move(aimPos.y) << std::move(bulletPos.x) << std::move(bulletPos.y);
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void shootRequest(std::unique_ptr<GameVariable>& gv, std::wstring bulletName, sf::Vector2f bulletPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"shoot";
	packet << prefix << std::move(bulletName) << std::move(bulletPos.x) << std::move(bulletPos.y);
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void mousePosRequest(std::unique_ptr<GameVariable>& gv)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"mousePos";
	packet << prefix << gv->getNickname() << gv->getMousePos().x << gv->getMousePos().y;
	gv->sock.send(packet, gv->getServerIP(), gv->getServerPort());
}

void sendClientRequests(std::unique_ptr<GameVariable>& gv, Chat& chat)
{
	std::lock_guard<std::mutex> lock(client_mtx);
	for (auto& client : clientVec)
	{
		if (client == nullptr || client->getName() != gv->getNickname()) { continue; }

		if (client->getAllowToSendMousePos()) { client->setAllowToSendMousePos(false); mousePosRequest(gv); }

		if (client->getAllowToSendMsg() && chat.getSendMsg())
		{
			client->setAllowToSendMsg(false);
			chat.setSendMsg(false);
			messageRequest(gv, chat);
		}
		if (client->getAllowToMove() && client->getIsMove() && !client->getIsCollision())
		{
			client->setAllowToMove(false);
			client->moveToTarget(gv, client->getMoveTargetPos());
			moveRequest(gv, client->getStepPos());
			//std::cout << "sendMoveRequest, client posX : " << client->getSpritePos().x << " posY : " << client->getSpritePos().y << "\n";
		}
	}
}

void sendBulletRequests(std::unique_ptr<GameVariable>& gv)
{
	std::lock_guard<std::mutex> lock(bullet_mtx);
	for (auto& bullet : bulletVec)
	{
		if (bullet == nullptr) { continue; }

		if (bullet->getAllowToShoot() && bullet->getIsAlive())
		{
			bullet->setAllowToShoot(false);
			bullet->move(gv);
			shootRequest(gv, bullet->getName(), bullet->getSpritePos());
		}
	}
}