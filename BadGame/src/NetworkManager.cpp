#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	sock.setBlocking(false);
	currentNickname = L"";
	serverIP = "";
	tempPort = "";
	serverPort = 0;
	countOfDotsInIP = 0;
	numOfConnectedClients = 0;
	connectsToServer = false;
	serverIsNotAvailable = false;
	isConnected = false;
	isMinimapView = false;
	connectButtonPressed = false;
	msgReceived = true;
	serverClock.restart();
}

void NetworkManager::resetVariables()
{
	isConnected = false;
	serverIsNotAvailable = false;
	isMinimapView = false;
	msgReceived = true;
	serverClock.restart();
}


// GETTERS.
std::wstring NetworkManager::getCurrentNickname()
{
	std::lock_guard<std::mutex> lock(mtx);
	std::wstring nickname = this->currentNickname;
	return nickname;
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

int NetworkManager::getNumOfConnectedClients()
{
	std::lock_guard<std::mutex> lock(mtx);
	int numOfConnectedClients = this->numOfConnectedClients;
	return numOfConnectedClients;
}

sf::Int32 NetworkManager::getServerClockElapsedTime()
{
	std::lock_guard<std::mutex> lock(mtx);
	sf::Int32 elapsedTime = this->serverClock.getElapsedTime().asMilliseconds();
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

bool NetworkManager::getMsgReceived()
{
	std::lock_guard<std::mutex> lock(mtx);
	bool msgReceived = this->msgReceived;
	return msgReceived;
}




// SETTERS.
void NetworkManager::setCurrentNickname(std::wstring nickname)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->currentNickname = std::move(nickname);
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

void NetworkManager::setNumOfConnectedClients(int numOfConnectedClients)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->numOfConnectedClients = std::move(numOfConnectedClients);
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

void NetworkManager::setMsgReceived(bool msgReceived)
{
	std::lock_guard<std::mutex> lock(mtx);
	this->msgReceived = std::move(msgReceived);
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