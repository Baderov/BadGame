#include "pch.h"
#include "Clients.h"

std::mutex c_mtx; // mutex for clients.
Entity* currentClient = nullptr;

Clients::Clients(sf::Font& consolasFont, sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // second clients constructor.
{
	entityType = "Client";

	numOfClients++;

	this->startPos = startPos;
	this->name = name;

	HP = 100;
	ping = 0;
	pingClock.restart();
	distance = 0.f;
	maxSpeed = 5.f;
	DTMultiplier = 1000.f;
	currentVelocity = sf::Vector2f(0.6f, 0.6f);
	isAlive = true;
	isMove = false;

	image.loadFromFile("Images/player.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	w = static_cast<float>(texture.getSize().x);
	h = static_cast<float>(texture.getSize().y);
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(startPos);

	nameText.setFont(consolasFont);
	nameText.setFillColor(sf::Color::Green);
	nameText.setCharacterSize(40);
	nameText.setOutlineThickness(2.f);
	nameText.setString(name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));
	nameText.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 80.f));

	icon.setRadius(static_cast<float>(image.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);

}

void Clients::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) {}

void Clients::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer)
{
	if (isAlive == true)
	{
		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Clients::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos)
{
	float dX = targetPos.x - sprite.getPosition().x;
	float dY = targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	aimLaser.setRotation(rotation + 90.f);
}


//std::wstring Clients::getNickname()
//{
//	c_mtx.lock();
//	std::wstring tempNick = nickname;
//	c_mtx.unlock();
//	return tempNick;
//}
//sf::Vector2f Clients::getMoveTargetPos()
//{
//	c_mtx.lock();
//	sf::Vector2f tempMoveTargetPos = moveTargetPos;
//	c_mtx.unlock();
//	return tempMoveTargetPos;
//}
//sf::Vector2f Clients::getCurrentVelocity()
//{
//	c_mtx.lock();
//	sf::Vector2f tempCurrentVelocity = currentVelocity;
//	c_mtx.unlock();
//	return tempCurrentVelocity;
//}
//sf::Vector2f Clients::getStepPos()
//{
//	c_mtx.lock();
//	sf::Vector2f tempStepPos = stepPos;
//	c_mtx.unlock();
//	return tempStepPos;
//}

//int Clients::getHP()
//{
//	c_mtx.lock();
//	int tempHP = HP;
//	c_mtx.unlock();
//	return tempHP;
//}
//float Clients::getMaxSpeed()
//{
//	c_mtx.lock();
//	float tempMaxSpeed = maxSpeed;
//	c_mtx.unlock();
//	return tempMaxSpeed;
//}
//float Clients::getDistance()
//{
//	c_mtx.lock();
//	float tempDistance = distance;
//	c_mtx.unlock();
//	return tempDistance;
//}
//float Clients::getWidth()
//{
//	c_mtx.lock();
//	float tempWidth = width;
//	c_mtx.unlock();
//	return tempWidth;
//}
//float Clients::getHeight()
//{
//	c_mtx.lock();
//	float tempHeight = height;
//	c_mtx.unlock();
//	return tempHeight;
//}
//float Clients::getDTMultiplier()
//{
//	c_mtx.lock();
//	float tempDTMultiplier = DTMultiplier;
//	c_mtx.unlock();
//	return tempDTMultiplier;
//}
//bool Clients::getIsAlive()
//{
//	c_mtx.lock();
//	bool tempIsAlive = isAlive;
//	c_mtx.unlock();
//	return tempIsAlive;
//}
//bool Clients::getIsMove()
//{
//	c_mtx.lock();
//	bool tempIsMove = isMove;
//	c_mtx.unlock();
//	return tempIsMove;
//}
//bool Clients::getIsShoot()
//{
//	c_mtx.lock();
//	bool tempIsShoot = isShoot;
//	c_mtx.unlock();
//	return tempIsShoot;
//}
//bool Clients::getIsReload()
//{
//	c_mtx.lock();
//	bool tempIsReload = isReload;
//	c_mtx.unlock();
//	return tempIsReload;
//}

//void Clients::setNickname(std::wstring tempNick)
//{
//	c_mtx.lock();
//	nickname = tempNick;
//	c_mtx.unlock();
//}
//void Clients::setMoveTargetPos(sf::Vector2f tempMoveTargetPos)
//{
//	c_mtx.lock();
//	moveTargetPos = tempMoveTargetPos;
//	c_mtx.unlock();
//}
//void Clients::setCurrentVelocity(sf::Vector2f tempCurrentVelocity)
//{
//	c_mtx.lock();
//	currentVelocity = tempCurrentVelocity;
//	c_mtx.unlock();
//}
//void Clients::setStepPos(sf::Vector2f tempStepPos)
//{
//	c_mtx.lock();
//	stepPos = tempStepPos;
//	c_mtx.unlock();
//}
//void Clients::setHP(int tempHP)
//{
//	c_mtx.lock();
//	HP = tempHP;
//	c_mtx.unlock();
//}
//void Clients::setMaxSpeed(float tempMaxSpeed)
//{
//	c_mtx.lock();
//	maxSpeed = tempMaxSpeed;
//	c_mtx.unlock();
//}
//void Clients::setDistance(float tempDistance)
//{
//	c_mtx.lock();
//	distance = tempDistance;
//	c_mtx.unlock();
//}
//void Clients::setWidth(float tempWidth)
//{
//	c_mtx.lock();
//	width = tempWidth;
//	c_mtx.unlock();
//}
//void Clients::setHeight(float tempHeight)
//{
//	c_mtx.lock();
//	height = tempHeight;
//	c_mtx.unlock();
//}
//void Clients::setDTMultiplier(float tempDTMultiplier)
//{
//	c_mtx.lock();
//	DTMultiplier = tempDTMultiplier;
//	c_mtx.unlock();
//}
//void Clients::setIsAlive(bool tempIsAlive)
//{
//	c_mtx.lock();
//	isAlive = tempIsAlive;
//	c_mtx.unlock();
//}
//void Clients::setIsMove(bool tempIsMove)
//{
//	c_mtx.lock();
//	isMove = tempIsMove;
//	c_mtx.unlock();
//}
//void Clients::setIsShoot(bool tempIsShoot)
//{
//	c_mtx.lock();
//	isShoot = tempIsShoot;
//	c_mtx.unlock();
//}
//void Clients::setIsReload(bool tempIsReload)
//{
//	c_mtx.lock();
//	isReload = tempIsReload;
//	c_mtx.unlock();
//}
//void Clients::setPosition(sf::Vector2f tempStepPos)
//{
//	c_mtx.lock();
//	sprite.move(tempStepPos);
//	icon.move(tempStepPos);
//	c_mtx.unlock();
//}



bool currentClientIsNullptr()
{
	std::lock_guard<std::mutex> lock(c_mtx);
	if (currentClient == nullptr) { return true; }
	else { return false; }
}
sf::Vector2f getCurrentClientPos()
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		sf::Vector2f tempPos = currentClient->getSprite().getPosition();
		return tempPos;
	}
}
sf::Vector2f getCurrentClientMoveTargetPos()
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		sf::Vector2f tempMoveTargetPos = currentClient->getMoveTargetPos();
		return tempMoveTargetPos;
	}
}
sf::Vector2f getCurrentClientStepPos()
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		sf::Vector2f tempStepPos = currentClient->getStepPos();
		return tempStepPos;
	}
}
bool getCurrentClientIsMove()
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		bool tempIsMove = currentClient->getIsMove();
		return tempIsMove;
	}
}

void setCurrentClient(Entity* tempClient)
{
	std::lock_guard<std::mutex> lock(c_mtx);
	currentClient = tempClient;
}
void setCurrentClientMoveTargetPos(sf::Vector2f tempMoveTargetPos)
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		currentClient->setMoveTargetPos(tempMoveTargetPos);
	}
}
void setCurrentClientIsMove(bool tempIsMove)
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		currentClient->setIsMove(tempIsMove);
	}
}
void setCurrentClientIsShoot(bool tempIsShoot)
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		currentClient->setIsShoot(tempIsShoot);
	}
}
void callMoveToTarget(float dt, bool isSinglePlayer)
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		currentClient->moveToTarget(currentClient->getMoveTargetPos(), dt, isSinglePlayer);
	}
}
void callUpdateLaser(sf::Vector2f mousePos, sf::RectangleShape& aimLaser)
{
	if (currentClient != nullptr)
	{
		std::lock_guard<std::mutex> lock(c_mtx);
		currentClient->updateLaser(mousePos, aimLaser);
	}
}