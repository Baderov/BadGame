#pragma once
#include "Entity.h"

sf::Vector2f getCurrentClientPos();

class Clients : public Entity
{
private:
	friend sf::Vector2f getCurrentClientPos();
public:
	Clients(sf::Font& consolasFont, sf::Image& image, sf::Vector2f startPos, std::wstring name); // player constructor.
	void update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer) override;
	void move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) override;
	void rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos) override;
};

sf::Vector2f getCurrentClientMoveTargetPos();
sf::Vector2f getCurrentClientStepPos();
bool currentClientIsNullptr();
bool getCurrentClientIsMove();

void setCurrentClient(Entity* tempClient);
void setCurrentClientMoveTargetPos(sf::Vector2f tempMoveTargetPos);
void setCurrentClientIsMove(bool tempIsMove);
void setCurrentClientIsShoot(bool tempIsShoot);

void callMoveToTarget(float dt, bool isSinglePlayer);
void callUpdateLaser(sf::Vector2f mousePos, sf::RectangleShape& aimLaser);