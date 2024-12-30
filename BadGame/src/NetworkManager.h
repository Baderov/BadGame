#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

class NetworkManager
{
private:
	std::mutex mtx;
	sf::UdpSocket sock;
	sf::Clock serverClock;
	std::wstring nickname;
	std::string serverIP;
	std::string tempPort;
	unsigned short serverPort;
	int countOfDotsInIP;
	bool connectsToServer;
	bool serverIsNotAvailable;
	bool isConnected;
	bool isMinimapView;
	bool connectButtonPressed;
	bool allowToSendMsg;
public:
	NetworkManager();
	void resetVariables();

	std::wstring getNickname();
	std::string getServerIP();
	std::string getTempPort();
	unsigned short getServerPort();
	int getCountOfDotsInIP();
	float getServerClockElapsedTime();
	bool getConnectsToServer();
	bool getServerIsNotAvailable();
	bool getIsConnected();
	bool getIsMinimapView();
	bool getConnectButtonPressed();
	bool getAllowToSendMsg();

	void setNickname(std::wstring nickname);
	void setServerIP(std::string serverIP);
	void setTempPort(std::string tempPort);
	void setServerPort(unsigned short serverPort);
	void setCountOfDotsInIP(int countOfDotsInIP);
	void setConnectsToServer(bool connectsToServer);
	void setServerIsNotAvailable(bool serverIsNotAvailable);
	void setIsConnected(bool isConnected);
	void setIsMinimapView(bool isMinimapView);
	void setConnectButtonPressed(bool connectButtonPressed);
	void setAllowToSendMsg(bool allowToSendMsg);
	void restartServerClock();
	void sockSend(sf::Packet& packet, sf::IpAddress&& serverIP, unsigned short&& serverPort);
	bool sockNotRecv(sf::Packet& packet, sf::IpAddress&& remoteAddress, unsigned short&& remotePort);;
};

#endif