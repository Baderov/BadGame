#include "pch.h"
#include "NetworkRequest.h"

void respawnRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& nickname, sf::Vector2f&& startPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"respawn";
	packet << prefix << nickname << startPos.x << startPos.y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void connectedToServerRequest(std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"connected";
	packet << prefix << nm->getCurrentNickname();
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void regNickRequest(std::unique_ptr<NetworkManager>& nm, std::unique_ptr<GameVariable>& gv)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"regNick";
	packet << prefix << nm->getCurrentNickname() << gv->getGameVersion();
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void messageRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& msg)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"msg";
	packet << prefix << nm->getCurrentNickname() << msg;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void moveRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& currentClientStepPos)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"move";
	packet << prefix << nm->getCurrentNickname() << currentClientStepPos.x << currentClientStepPos.y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void hitRequest(std::unique_ptr<NetworkManager>& nm, std::wstring&& woundedClientNick)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"hit";
	packet << prefix << nm->getCurrentNickname() << woundedClientNick;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void shootRequest(std::unique_ptr<NetworkManager>& nm, sf::Vector2f&& aimPos, sf::Vector2f&& bulletPos, sf::Vector2f&& currentVelocity)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"shoot";
	packet << prefix << nm->getCurrentNickname() << aimPos.x << aimPos.y << bulletPos.x << bulletPos.y << currentVelocity.x << currentVelocity.y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void mousePosRequest(std::unique_ptr<GameVariable>& gv, std::unique_ptr<NetworkManager>& nm)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"mousePos";
	packet << prefix << nm->getCurrentNickname() << gv->getMousePos().x << gv->getMousePos().y;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void ghostRequest(std::unique_ptr<NetworkManager>& nm, bool&& isGhost)
{
	sf::Packet packet;
	packet.clear();
	std::wstring prefix = L"ghost";
	packet << prefix << nm->getCurrentNickname() << isGhost;
	nm->sockSend(packet, nm->getServerIP(), nm->getServerPort());
}

void sendClientRequests(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::unique_ptr<CustomWidget>& cw)
{
	mousePosRequest(gv, nm);

	std::lock_guard<std::mutex> lock(clients_mtx);
	for (size_t i = 0; i < clientsVec.size(); ++i)
	{
		if (clientsVec[i]->getName() != nm->getCurrentNickname()) { continue; }
		if (!clientsVec[i]->getSendMoveRequest() || clientsVec[i]->getMoveReceived()) { return; }

		clientsVec[i]->setIsCollision(false);
		clientsVec[i]->moveCollider();
		clientsVec[i]->checkCollision(gv, gw, sm, nm);
		clientsVec[i]->returnCollider();

		if (!clientsVec[i]->getIsCollision() && clientsVec[i]->getIsGhost() && clientsVec[i]->getIsMove())
		{
			clientsVec[i]->setSendMoveRequest(false);
			bool isGhost = false;
			ghostRequest(nm, std::move(isGhost));
		}

		else if (!clientsVec[i]->getIsCollision() || clientsVec[i]->getIsGhost())
		{
			clientsVec[i]->setSendMoveRequest(false);
			moveRequest(nm, clientsVec[i]->getStepPos());
		}

		break;
	}
}