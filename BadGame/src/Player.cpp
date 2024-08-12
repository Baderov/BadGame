#include "pch.h"
#include "Player.h"

Player::Player(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) : Entity(gv, gw, sm, nm) {}

void Player::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos)
{
	isAlive = true;
	isMove = false;
	isReload = false;

	this->startPos = std::move(startPos);
	this->name = L"";

	currentVelocity = sf::Vector2f(0.85f, 0.85f);
	moveTargetPos = this->startPos;
	maxSpeed = 5.f;
	reloadTime = 0.f;

	HP = 100;
	goldCoins = 0;
	maxHP = HP;
	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;

	texture.loadFromImage(gv->playerImage);
	sprite.setTexture(texture, true);
	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(this->startPos);

	collisionRect.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	collisionRect.setOrigin(collisionRect.getSize().x / 2.f, collisionRect.getSize().y / 2.f);
	collisionRect.setFillColor(sf::Color::Green);
	collisionRect.setPosition(this->startPos);

	reloadRectOuter.setFillColor(grayColor);
	reloadRectOuter.setOutlineThickness(2.f);
	reloadRectOuter.setOutlineColor(sf::Color::Black);

	reloadRectInner.setFillColor(sf::Color::Black);
	reloadRectInner.setOutlineThickness(2.f);
	reloadRectInner.setOutlineColor(sf::Color::Black);

	reloadText.setFont(gv->consolasFont);
	reloadText.setString("RELOAD");
	reloadText.setCharacterSize(50);
	reloadText.setFillColor(sf::Color::Black);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);

	nameText.setString(this->name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));

	icon.setFillColor(sf::Color::Green);
	icon.setRadius(static_cast<float>(gv->playerImage.getSize().x));
	icon.setOutlineThickness(15.f);
	icon.setOutlineColor(sf::Color::Black);
	icon.setOrigin(icon.getRadius() / 2.f, icon.getRadius() / 2.f);
}

void Player::update(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (isAlive)
	{
		gv->setMousePos(gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window)));

		move(gv, gw, sm, nm);
		shoot(gv, gw, sm);
		rotate(gv, gv->getMousePos());
		updateLaser(gv);
		gw->setGameViewCenter(sprite.getPosition());

		nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 90.f);
		icon.setPosition(sprite.getPosition());
		updateHPBar();
		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);

		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
	else { sm->setGameResultGoldCoins(getGoldCoins()); }
}

void Player::move(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	isCollision = false;
	if (isMove)
	{
		calcTarget(moveTargetPos, gv->getDT());
		moveCollisionRect();
		collision(gv, gw, sm, nm);

		if (isCollision) { returnCollisionRect(); }
		else { sprite.move(stepPos); }
	}
}

void Player::draw(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	if (nm->getIsMinimapView()) { drawIcon(gw); }
	else
	{
		if (gv->getShowAimLaser() && gv->getFocusEvent()) { gw->window.draw(gv->aimLaser); }
		if (isMove) { gw->window.draw(gv->playerDestination); }
		if (gv->getShowCollisionRect()) { drawCollisionRect(gw); }
		else
		{
			drawSprite(gw);
			drawHPBarOuter(gw);
			drawHPBarInner(gw);
			if (isReload)
			{
				drawReloadRectOuter(gw);
				drawReloadRectInner(gw);
				drawReloadText(gw);
			}
			drawHPText(gw);
			drawNameText(gw);
		}
	}
}

void Player::collision(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	for (size_t i = 0; i < wallsVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, wallsVec[i].get());
	}

	for (size_t i = 0; i < boxesVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, boxesVec[i].get());
	}

	for (size_t i = 0; i < enemiesVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, enemiesVec[i].get());
	}

	for (size_t i = 0; i < itemsVec.size(); ++i)
	{
		collisionHandler(gv, nm, this, itemsVec[i].get());
	}
}

void Player::returnToPool(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm) {}

void Player::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

void Player::updateReloadRect(std::unique_ptr<GameVariable>& gv)
{
	reloadRectOuter.setSize(sf::Vector2f(200.f, 20.f));
	reloadRectOuter.setOrigin(reloadRectOuter.getSize() / 2.f);
	float tempReloadTime = 0.f;
	if (reloadTime > 0.f) { tempReloadTime = (reloadTime * 1000.f) / 10.f; }
	float reloadRectOuterSizeX = reloadRectOuter.getSize().x;
	if (tempReloadTime < reloadRectOuterSizeX) { reloadRectInner.setSize(sf::Vector2f(tempReloadTime, reloadRectOuter.getSize().y)); }
	else { reloadRectInner.setSize(sf::Vector2f(0.f, reloadRectOuter.getSize().y)); }
	reloadRectOuter.setPosition(sprite.getPosition().x, sprite.getPosition().y + 400.f);
	reloadRectInner.setPosition(reloadRectOuter.getPosition().x - (reloadRectOuter.getSize().x / 2.f), reloadRectOuter.getPosition().y - (reloadRectOuter.getSize().y / 2.f));
	if (gv->getGameLanguage() == GameLanguage::English)
	{
		reloadText.setString("RELOAD");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	else if (gv->getGameLanguage() == GameLanguage::Russian)
	{
		reloadText.setString(L"œ≈–≈«¿–ﬂƒ ¿");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	reloadText.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y - 50.f);
}

void Player::shoot(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm)
{
	if (currentAmmo < 30 && isReload && reloadTime >= 2.f)
	{
		missingAmmo = magazineAmmo - currentAmmo;
		if (maxAmmo < magazineAmmo)
		{
			if (maxAmmo + currentAmmo <= 30)
			{
				currentAmmo = currentAmmo + maxAmmo;
				maxAmmo = 0;
			}
			else
			{
				int tempAmmo = magazineAmmo - currentAmmo;
				currentAmmo = currentAmmo + tempAmmo;
				maxAmmo = maxAmmo - tempAmmo;
			}
		}
		else
		{
			currentAmmo = currentAmmo + missingAmmo;
			maxAmmo = maxAmmo - missingAmmo;
		}

		isReload = false;
	}

	if (isShoot && currentAmmo > 0 && !isReload && bulletsPool.getFromPool(bulletsVec))
	{
		sf::Vector2f startPos = sprite.getPosition();
		sf::Vector2f aimPos = gw->window.mapPixelToCoords(sf::Mouse::getPosition(gw->window));
		std::wstring creatorName = name;

		bulletsVec.back()->init(gv, startPos, aimPos, creatorName);
		currentAmmo--;
		isShoot = false;
	}

	if (isReload)
	{
		reloadTime = reloadClock.getElapsedTime().asSeconds() - menuTime;
		if (reloadTime < 0.f) { reloadTime = 0.f; }
		updateReloadRect(gv);
	}
}