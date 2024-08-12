#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	sock.setBlocking(false);
	serverClock.restart();
	nickname = L"";
	movedClientNick = L"";
	serverIP = "";
	tempPort = "";
	serverPort = 0;
	countOfDotsInIP = 0;
	connectsToServer = false;
	serverIsNotAvailable = false;
	isConnected = false;
	isMinimapView = false;
	connectButtonPressed = false;
	moveReceived = false;
	clientMoved = false;
	allowToSendMsg = true;
}

void NetworkManager::resetVariables()
{
	serverClock.restart();
	movedClientNick = L"";
	serverIsNotAvailable = false;
	isMinimapView = false;
	moveReceived = false;
	clientMoved = false;
	allowToSendMsg = true;
}

// GETTERS.

std::wstring NetworkManager::getNickname()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::wstring nickname = this->nickname;
	return nickname;
}

std::wstring NetworkManager::getMovedClientNick()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::wstring movedClientNick = this->movedClientNick;
	return movedClientNick;
}

std::string NetworkManager::getServerIP()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::string serverIP = this->serverIP;
	return serverIP;
}

std::string NetworkManager::getTempPort()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::string tempPort = this->tempPort;
	return tempPort;
}

unsigned short NetworkManager::getServerPort()
{
	std::lock_guard<std::mutex> lock(mtx);
	unsigned short serverPort = this->serverPort;
	return serverPort;
}

int NetworkManager::getCountOfDotsInIP()
{
	std::lock_guard<std::mutex> lock(mtx);
	int countOfDotsInIP = this->countOfDotsInIP;
	return countOfDotsInIP;
}

float NetworkManager::getServerClockElapsedTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	float elapsedTime = this->serverClock.getElapsedTime().asSeconds();
	return elapsedTime;
}

bool NetworkManager::getIsConnected()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isConnected = this->isConnected;
	return isConnected;
}

bool NetworkManager::getIsMinimapView()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool isMinimapView = this->isMinimapView;
	return isMinimapView;
}

bool NetworkManager::getConnectButtonPressed()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool connectButtonPressed = this->connectButtonPressed;
	return connectButtonPressed;
}

bool NetworkManager::getConnectsToServer()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool connectsToServer = this->connectsToServer;
	return connectsToServer;
}

bool NetworkManager::getServerIsNotAvailable()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool serverIsNotAvailable = this->serverIsNotAvailable;
	return serverIsNotAvailable;
}

bool NetworkManager::getMoveReceived()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool moveReceived = this->moveReceived;
	return moveReceived;
}

bool NetworkManager::getClientMoved()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool clientMoved = this->clientMoved;
	return clientMoved;
}

bool NetworkManager::getAllowToSendMsg()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool allowToSendMsg = this->allowToSendMsg;
	return allowToSendMsg;
}



// SETTERS.
void NetworkManager::setNickname(std::wstring nickname)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->nickname = std::move(nickname);
}

void NetworkManager::setMovedClientNick(std::wstring movedClientNick)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->movedClientNick = std::move(movedClientNick);
}

void NetworkManager::setServerIP(std::string serverIP)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->serverIP = std::move(serverIP);
}

void NetworkManager::setTempPort(std::string tempPort)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->tempPort = std::move(tempPort);
}

void NetworkManager::setServerPort(unsigned short serverPort)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->serverPort = std::move(serverPort);
}

void NetworkManager::setCountOfDotsInIP(int countOfDotsInIP)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->countOfDotsInIP = std::move(countOfDotsInIP);
}

void NetworkManager::setIsConnected(bool isConnected)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isConnected = std::move(isConnected);
}

void NetworkManager::setIsMinimapView(bool isMinimapView)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->isMinimapView = std::move(isMinimapView);
}

void NetworkManager::setConnectButtonPressed(bool connectButtonPressed)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->connectButtonPressed = std::move(connectButtonPressed);
}

void NetworkManager::setConnectsToServer(bool connectsToServer)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->connectsToServer = std::move(connectsToServer);
}

void NetworkManager::setServerIsNotAvailable(bool serverIsNotAvailable)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->serverIsNotAvailable = std::move(serverIsNotAvailable);
}

void NetworkManager::setMoveReceived(bool moveReceived)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->moveReceived = std::move(moveReceived);
}

void NetworkManager::setClientMoved(bool clientMoved)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->clientMoved = std::move(clientMoved);
}

void NetworkManager::setAllowToSendMsg(bool allowToSendMsg)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->allowToSendMsg = std::move(allowToSendMsg);
}

void NetworkManager::restartServerClock()
{
	std::lock_guard<std::mutex> lock(mtx);
	this->serverClock.restart();
}

void NetworkManager::sockSend(sf::Packet& packet, sf::IpAddress&& remoteAddress, unsigned short&& remotePort)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->sock.send(packet, remoteAddress, remotePort);
}

bool NetworkManager::sockNotRecv(sf::Packet& packet, sf::IpAddress&& remoteAddress, unsigned short&& remotePort)
{
	std::lock_guard<std::mutex> lock(mtx);
	if (this->sock.receive(packet, remoteAddress, remotePort) != sf::Socket::Done) { return true; }
	return false;
}