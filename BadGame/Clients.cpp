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

	icon.setRadius(image.getSize().x);
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

sf::Int32 Clients::getClientPing()
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		sf::Int32 tempPing = ping;
		c_mtx.unlock();
		return tempPing;
	}
}

void Clients::setClientPing(sf::Int32 tempPing)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		ping = tempPing;
		c_mtx.unlock();
	}
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

sf::Vector2f getMoveTargetPos()
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		sf::Vector2f tempMoveTargetPos = currentClient->moveTargetPos;
		c_mtx.unlock();
		return tempMoveTargetPos;
	}
}

sf::Vector2f getCurrentClientStepPos()
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		sf::Vector2f tempStepPos = currentClient->stepPos;
		c_mtx.unlock();
		return tempStepPos;
	}
}

bool getCurrentClientIsMove()
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		bool tempIsMove = currentClient->isMove;
		c_mtx.unlock();
		return tempIsMove;
	}
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

void setCurrentClient(Clients* tempClient)
{
	c_mtx.lock();
	currentClient = tempClient;
	c_mtx.unlock();
}

void setMoveTargetPos(sf::Vector2f tempMoveTargetPos)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		currentClient->moveTargetPos = tempMoveTargetPos;
		c_mtx.unlock();
	}
}

void setIsMove(bool tempIsMove)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		currentClient->isMove = tempIsMove;
		c_mtx.unlock();
	}
}

void setIsShoot(bool tempIsShoot)
{
	if (currentClient != nullptr)
	{
		c_mtx.lock();
		currentClient->isShoot = tempIsShoot;
		c_mtx.unlock();
	}
}

void moveClient(std::unique_ptr<Clients>& client, sf::Vector2f& tempStepPos)
{
	if (client != nullptr)
	{
		c_mtx.lock();
		client->sprite.move(tempStepPos);
		client->icon.move(tempStepPos);
		c_mtx.unlock();
	}
}

void setClientNickPosition(std::unique_ptr<Clients>& client)
{
	if (client != nullptr)
	{
		c_mtx.lock();
		client->nickText.setPosition(client->sprite.getPosition().x, client->sprite.getPosition().y - 80.f);
		c_mtx.unlock();
	}
}