#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

class Client : public Entity
{
private:
	sf::Int32 ping;
	sf::Clock pingClock;
	bool allowToMove, allowToSendMsg, allowToSendMousePos, allowToCollision;
public:
	const sf::Int32 pingDelay = 100;

	explicit Client(std::unique_ptr<GameVariable>& gv);
	void init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name);
	void update(std::unique_ptr<GameVariable>& gv) override;
	void move(std::unique_ptr<GameVariable>& gv) override;
	void rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos) override;

	sf::Int32 getPing();
	sf::Int32 getPingClockElapsedTime();
	bool getAllowToMove();
	bool getAllowToSendMsg();
	bool getAllowToSendMousePos();
	bool getAllowToCollision();

	void setClientPosition(sf::Vector2f tempPos);
	void setPing(sf::Int32 ping);
	void setNickPosition();
	void setAllowToMove(bool allowToMove);
	void setAllowToSendMsg(bool allowToSendMsg);
	void setAllowToSendMousePos(bool allowToSendMousePos);
	void setAllowToCollision(bool allowToCollision);

	void moveClient(sf::Vector2f tempStepPos);
};

#endif