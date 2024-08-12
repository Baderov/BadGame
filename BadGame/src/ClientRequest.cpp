#include "pch.h"
#include "ClientRequest.h"

void connectedToServerRequest(std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"connected";
	packet << prefix << nm->getNickname();
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void regNickRequest(std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"regNick";
	packet << prefix << nm->getNickname();
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void messageRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& msg)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"msg";
	packet << prefix << nm->getNickname() << msg;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void moveRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& currentClientStepPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"move";
	packet << prefix << nm->getNickname() << currentClientStepPos.x << currentClientStepPos.y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void shootRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& creatorName, sf::Vector2f&& aimPos, sf::Vector2f&& bulletPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"shoot";
	packet << prefix << creatorName << aimPos.x << aimPos.y << bulletPos.x << bulletPos.y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void mousePosRequest(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"mousePos";
	packet << prefix << nm->getNickname() << gv->getMousePos().x << gv->getMousePos().y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void ghostRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& nickname, bool&& isGhost)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"ghost";
	packet << prefix << nickname << isGhost;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void sendClientRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	mousePosRequest(gv, nm);

	if (!nm->getClientMoved() || nm->getMoveReceived()) { return; }

	std::lock_guard<std::mutex> lock(clients_mtx);
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		if (clientsVec[i]->getName() != nm->getNickname()) { continue; }
		if (!clientsVec[i]->getIsMove()) { break; }

		clientsVec[i]->setIsCollision(false);
		clientsVec[i]->calcTarget(clientsVec[i]->getMoveTargetPos(), gv->getDT());
		clientsVec[i]->moveCollisionRect();
		clientsVec[i]->collision(gv, gw, sm, nm);
		clientsVec[i]->returnCollisionRect();		

		if (!clientsVec[i]->getIsCollision() || clientsVec[i]->getIsGhost())
		{
			nm->setClientMoved(false);

			moveRequest(nm, clientsVec[i]->getStepPos());
		}

		if (!clientsVec[i]->getIsCollision() && clientsVec[i]->getIsGhost())
		{
			bool tempIsGhost = false;
			ghostRequest(nm, clientsVec[i]->getName(), std::move(tempIsGhost));
		}

		break;
	}
}

void sendBulletRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	std::lock_guard<std::mutex> lock(bullets_mtx);
	for (size_t i = 0; i < bulletsVec.size(); ++i)
	{
		if (bulletsVec[i]->getAllowToShoot() && bulletsVec[i]->getIsAlive())
		{
			bulletsVec[i]->setAllowToShoot(false);
			bulletsVec[i]->move(gv, gw, sm, nm);
		}
	}
}