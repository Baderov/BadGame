#include "pch.h"
#include "Player.h" // header file for player.

Player::Player(std::unique_ptr<GameVariable>& gv) : Entity(gv) {}

void Player::init(std::unique_ptr<GameVariable>& gv, sf::Vector2f startPos, std::wstring name)
{
	isAlive = true;
	isMove = false;
	isReload = false;

	this->startPos = std::move(startPos);
	this->name = std::move(name);

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

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(static_cast<sf::Vector2f>(sf::Vector2u(texture.getSize().y, texture.getSize().y)));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);

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

void Player::update(std::unique_ptr<GameVariable>& gv) // player update function.
{
	if (isAlive)
	{
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)));
		move(gv);
		rotate(gv, gv->getMousePos());
		updateLaser(gv);

		if (isReload)
		{
			reloadTime = reloadClock.getElapsedTime().asSeconds() - menuTime;
			if (reloadTime < 0.f) { reloadTime = 0.f; }
			updateReloadRect(gv);
		}
		nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 90.f);

		icon.setPosition(sprite.getPosition());
		rectHitbox.setPosition(sprite.getPosition());
		updateHPBar();

		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);

		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Player::rotate(std::unique_ptr<GameVariable>& gv, sf::Vector2f targetPos)
{
	this->targetPos = std::move(targetPos);
	float dX = this->targetPos.x - sprite.getPosition().x;
	float dY = this->targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

void Player::move(std::unique_ptr<GameVariable>& gv) // player move function.
{
	if (isMove) { moveToTarget(gv, moveTargetPos); }
}

void Player::updateReloadRect(std::unique_ptr<GameVariable>& gv) // update reload rect function.
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
	if (gv->getGameLanguage() == 'e')
	{
		reloadText.setString("RELOAD");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	else if (gv->getGameLanguage() == 'r')
	{
		reloadText.setString(L"œ≈–≈«¿–ﬂƒ ¿");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	reloadText.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y - 50.f);
}