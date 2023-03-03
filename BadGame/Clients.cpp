#include "Clients.h"

std::mutex c_mtx; // mutex for clients.
Clients* currentClient = nullptr;

Clients::Clients(GameVariable* gv) // second clients constructor.
{
	id = 0;
	HP = 100;
	ping = 0;
	pingClock.restart();
	distance = 0.f;
	maxSpeed = 5.f;
	DTMultiplier = 1000.f;
	currentVelocity = sf::Vector2f(0.6f, 0.6f);
	nickname = L"";
	isAlive = true;
	isMove = false;

	nickText.setFont(gv->consolasFont);
	nickText.setFillColor(sf::Color::Green);
	nickText.setCharacterSize(40);
	nickText.setOutlineThickness(2.f);

	image.loadFromFile("Images/player.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	width = static_cast<float>(texture.getSize().x);
	height = static_cast<float>(texture.getSize().y);
	sprite.setOrigin(width / 2.f, height / 2.f);
	sprite.setPosition(sf::Vector2f(960.f, 540.f));

	icon.setRadius(static_cast<float>(image.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);

}
void Clients::update(GameVariable* gv)
{
	if (isAlive == true)
	{
		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}
void Clients::rotate(GameVariable* gv, sf::Vector2f& mousePos) // player rotate function.
{
	float dX = mousePos.x - sprite.getPosition().x;
	float dY = mousePos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}
void Clients::updateLaser(GameVariable* gv) // laser update function.
{
	float dist = sqrt(((gv->getMousePos().x - sprite.getPosition().x) * (gv->getMousePos().x - sprite.getPosition().x)) + ((gv->getMousePos().y - sprite.getPosition().y) * (gv->getMousePos().y - sprite.getPosition().y)));
	gv->setAimLaserLength(dist);
	gv->aimLaser.setSize(sf::Vector2f(2.25f, -gv->getAimLaserLength()));
}
void Clients::moveToTarget(GameVariable* gv) // a function to move the sprite to the target.
{
	// distance from the current position of the sprite to the target position.
	distance = sqrt(((moveTargetPos.x - sprite.getPosition().x) * (moveTargetPos.x - sprite.getPosition().x)) + ((moveTargetPos.y - sprite.getPosition().y) * (moveTargetPos.y - sprite.getPosition().y)));

	// crutch, so that the player does not twitch when reaching the goal.
	if (distance > 7)
	{
		// stepPos - increment to the current position.
		stepPos.x = round((currentVelocity.x * (gv->getDT() * DTMultiplier) * (moveTargetPos.x - sprite.getPosition().x)) / distance);
		stepPos.y = round((currentVelocity.y * (gv->getDT() * DTMultiplier) * (moveTargetPos.y - sprite.getPosition().y)) / distance);
	}
	else { isMove = false; } // else don`t move.
}

sf::Int32 Clients::getPing()
{
	c_mtx.lock();
	sf::Int32 tempPing = ping;
	c_mtx.unlock();
	return tempPing;
}
std::wstring Clients::getNickname()
{
	c_mtx.lock();
	std::wstring tempNick = nickname;
	c_mtx.unlock();
	return tempNick;
}
sf::Vector2f Clients::getMoveTargetPos()
{
	c_mtx.lock();
	sf::Vector2f tempMoveTargetPos = moveTargetPos;
	c_mtx.unlock();
	return tempMoveTargetPos;
}
sf::Vector2f Clients::getCurrentVelocity()
{
	c_mtx.lock();
	sf::Vector2f tempCurrentVelocity = currentVelocity;
	c_mtx.unlock();
	return tempCurrentVelocity;
}
sf::Vector2f Clients::getStepPos()
{
	c_mtx.lock();
	sf::Vector2f tempStepPos = stepPos;
	c_mtx.unlock();
	return tempStepPos;
}
int Clients::getId()
{
	c_mtx.lock();
	int tempId = id;
	c_mtx.unlock();
	return tempId;
}
int Clients::getHP()
{
	c_mtx.lock();
	int tempHP = HP;
	c_mtx.unlock();
	return tempHP;
}
float Clients::getMaxSpeed()
{
	c_mtx.lock();
	float tempMaxSpeed = maxSpeed;
	c_mtx.unlock();
	return tempMaxSpeed;
}
float Clients::getDistance()
{
	c_mtx.lock();
	float tempDistance = distance;
	c_mtx.unlock();
	return tempDistance;
}
float Clients::getWidth()
{
	c_mtx.lock();
	float tempWidth = width;
	c_mtx.unlock();
	return tempWidth;
}
float Clients::getHeight()
{
	c_mtx.lock();
	float tempHeight = height;
	c_mtx.unlock();
	return tempHeight;
}
float Clients::getDTMultiplier()
{
	c_mtx.lock();
	float tempDTMultiplier = DTMultiplier;
	c_mtx.unlock();
	return tempDTMultiplier;
}
bool Clients::getIsAlive()
{
	c_mtx.lock();
	bool tempIsAlive = isAlive;
	c_mtx.unlock();
	return tempIsAlive;
}
bool Clients::getIsMove()
{
	c_mtx.lock();
	bool tempIsMove = isMove;
	c_mtx.unlock();
	return tempIsMove;
}
bool Clients::getIsShoot()
{
	c_mtx.lock();
	bool tempIsShoot = isShoot;
	c_mtx.unlock();
	return tempIsShoot;
}
bool Clients::getIsReload()
{
	c_mtx.lock();
	bool tempIsReload = isReload;
	c_mtx.unlock();
	return tempIsReload;
}

void Clients::setPing(sf::Int32 tempPing)
{
	c_mtx.lock();
	ping = tempPing;
	c_mtx.unlock();
}
void Clients::setNickname(std::wstring tempNick)
{
	c_mtx.lock();
	nickname = tempNick;
	c_mtx.unlock();
}
void Clients::setMoveTargetPos(sf::Vector2f tempMoveTargetPos)
{
	c_mtx.lock();
	moveTargetPos = tempMoveTargetPos;
	c_mtx.unlock();
}
void Clients::setCurrentVelocity(sf::Vector2f tempCurrentVelocity)
{
	c_mtx.lock();
	currentVelocity = tempCurrentVelocity;
	c_mtx.unlock();
}
void Clients::setStepPos(sf::Vector2f tempStepPos)
{
	c_mtx.lock();
	stepPos = tempStepPos;
	c_mtx.unlock();
}
void Clients::setId(int tempId)
{
	c_mtx.lock();
	id = tempId;
	c_mtx.unlock();
}
void Clients::setHP(int tempHP)
{
	c_mtx.lock();
	HP = tempHP;
	c_mtx.unlock();
}
void Clients::setMaxSpeed(float tempMaxSpeed)
{
	c_mtx.lock();
	maxSpeed = tempMaxSpeed;
	c_mtx.unlock();
}
void Clients::setDistance(float tempDistance)
{
	c_mtx.lock();
	distance = tempDistance;
	c_mtx.unlock();
}
void Clients::setWidth(float tempWidth)
{
	c_mtx.lock();
	width = tempWidth;
	c_mtx.unlock();
}
void Clients::setHeight(float tempHeight)
{
	c_mtx.lock();
	height = tempHeight;
	c_mtx.unlock();
}
void Clients::setDTMultiplier(float tempDTMultiplier)
{
	c_mtx.lock();
	DTMultiplier = tempDTMultiplier;
	c_mtx.unlock();
}
void Clients::setIsAlive(bool tempIsAlive)
{
	c_mtx.lock();
	isAlive = tempIsAlive;
	c_mtx.unlock();
}
void Clients::setIsMove(bool tempIsMove)
{
	c_mtx.lock();
	isMove = tempIsMove;
	c_mtx.unlock();
}
void Clients::setIsShoot(bool tempIsShoot)
{
	c_mtx.lock();
	isShoot = tempIsShoot;
	c_mtx.unlock();
}
void Clients::setIsReload(bool tempIsReload)
{
	c_mtx.lock();
	isReload = tempIsReload;
	c_mtx.unlock();
}
void Clients::setPosition(sf::Vector2f& tempStepPos)
{
	c_mtx.lock();
	sprite.move(tempStepPos);
	icon.move(tempStepPos);
	c_mtx.unlock();
}
void Clients::setNickPosition()
{
	c_mtx.lock();
	nickText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 80.f);
	c_mtx.unlock();
}

bool currentClientIsNullptr()
{
	if (currentClient == nullptr) { return true; }
	else { return false; }
}
sf::Vector2f getCurrentClientPos()
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		sf::Vector2f tempPos = currentClient->sprite.getPosition();
		c_mtx.unlock();
		return tempPos;
	}
}
sf::Vector2f getCurrentClientMoveTargetPos()
{
	if (currentClient != nullptr) { return currentClient->getMoveTargetPos(); }
}
sf::Vector2f getCurrentClientStepPos()
{
	if (currentClient != nullptr) { return currentClient->getStepPos(); }
}
bool getCurrentClientIsMove()
{
	if (currentClient != nullptr) { return currentClient->getIsMove(); }
}

void setCurrentClient(Clients* tempClient)
{
	c_mtx.lock();
	currentClient = tempClient;
	c_mtx.unlock();
}
void setCurrentClientMoveTargetPos(sf::Vector2f tempMoveTargetPos)
{
	if (currentClient != nullptr) { currentClient->setMoveTargetPos(tempMoveTargetPos); }
}
void setCurrentClientIsMove(bool tempIsMove)
{
	if (currentClient != nullptr) { currentClient->setIsMove(tempIsMove); }
}
void setCurrentClientIsShoot(bool tempIsShoot)
{
	if (currentClient != nullptr) { currentClient->setIsShoot(tempIsShoot); }
}

void callMoveToTarget(GameVariable* gv)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		currentClient->moveToTarget(gv);
		c_mtx.unlock();
	}
}
void callUpdateLaser(GameVariable* gv)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		currentClient->updateLaser(gv);
		c_mtx.unlock();
	}
}