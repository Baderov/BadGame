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
	w = static_cast<float>(texture.getSize().x);
	h = static_cast<float>(texture.getSize().y);
	sprite.setOrigin(w / 2.f, h / 2.f);
	sprite.setPosition(sf::Vector2f(960.f, 540.f));
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

sf::Int32 Clients::getClientPing()
{
	c_mtx.lock();
	sf::Int32 tempPing = currentClient->ping;
	c_mtx.unlock();
	return tempPing;
}

void Clients::setClientPing(sf::Int32 tempPing)
{
	c_mtx.lock();
	currentClient->ping = tempPing;
	c_mtx.unlock();
}

sf::Vector2f getClientPos()
{
	c_mtx.lock();
	sf::Vector2f tempPos = currentClient->sprite.getPosition();
	c_mtx.unlock();
	return tempPos;
}

sf::Vector2f getMoveTargetPos()
{
	c_mtx.lock();
	sf::Vector2f tempMoveTargetPos = currentClient->moveTargetPos;
	c_mtx.unlock();
	return tempMoveTargetPos;
}

sf::Vector2f getClientStepPos()
{
	c_mtx.lock();
	sf::Vector2f tempStepPos = currentClient->stepPos;
	c_mtx.unlock();
	return tempStepPos;
}

bool clientIsNullptr()
{
	if (currentClient == nullptr) { return true; }
	else { return false; }
}

bool getClientIsMove()
{
	c_mtx.lock();
	bool tempIsMove = currentClient->isMove;
	c_mtx.unlock();
	return tempIsMove;
}

void callMoveToTarget(GameVariable* gv)
{
	c_mtx.lock();
	currentClient->moveToTarget(gv);
	c_mtx.unlock();
}

void callUpdateLaser(GameVariable* gv)
{
	c_mtx.lock();
	currentClient->updateLaser(gv);
	c_mtx.unlock();
}

void setCurrentClient(Clients* tempClient)
{
	c_mtx.lock();
	currentClient = tempClient;
	c_mtx.unlock();
}

void setMoveTargetPos(sf::Vector2f tempMoveTargetPos)
{
	c_mtx.lock();
	currentClient->moveTargetPos = tempMoveTargetPos;
	c_mtx.unlock();
}

void setIsMove(bool tempIsMove)
{
	c_mtx.lock();
	currentClient->isMove = tempIsMove;
	c_mtx.unlock();
}

void setIsShoot(bool tempIsShoot)
{
	c_mtx.lock();
	currentClient->isShoot = tempIsShoot;
	c_mtx.unlock();
}

