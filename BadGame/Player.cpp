#include "pch.h"
#include "Player.h" // header file for player.

Player::Player(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // player constructor.
{
	entityType = "Player";
	isMove = false;
	isReload = false;
	currentVelocity = sf::Vector2f(0.6f, 0.6f);
	maxSpeed = 5.f;
	HP = 100;
	goldCoins = 0;
	maxHP = HP;
	moveTargetPos = sprite.getPosition();

	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;

	reloadTime = 0.f;

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(sf::Vector2f(h, h));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);

	reloadRectOuter.setFillColor(grayColor);
	reloadRectOuter.setOutlineThickness(2.f);
	reloadRectOuter.setOutlineColor(sf::Color::Black);

	reloadRectInner.setFillColor(sf::Color::Black);
	reloadRectInner.setOutlineThickness(2.f);
	reloadRectInner.setOutlineColor(sf::Color::Black);

	reloadText.setFont(consolasFont);
	reloadText.setString("RELOAD");
	reloadText.setCharacterSize(50);
	reloadText.setFillColor(sf::Color::Black);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);

	nameText.setString(name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));

	icon.setFillColor(sf::Color::Green);
}

void Player::update(sf::RenderWindow& window, sf::RectangleShape& aimLaser, sf::Vector2f mousePos, char gameLanguage, float dt, bool isSinglePlayer) // player update function.
{
	if (isAlive == true)
	{
		mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		move(aimLaser, dt, isSinglePlayer);
		rotate(aimLaser, mousePos);
		updateLaser(mousePos, aimLaser);

		if (isReload == true)
		{
			reloadTime = reloadClock.getElapsedTime().asSeconds() - menuTime;
			if (reloadTime < 0.f) { reloadTime = 0.f; }
			updateReloadRect(gameLanguage);
		}
		nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 90.f);

		icon.setPosition(sprite.getPosition());
		rectHitbox.setPosition(sprite.getPosition());
		aimLaser.setPosition(sprite.getPosition());
		updateHPBar();

		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);

		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Player::rotate(sf::RectangleShape& aimLaser, sf::Vector2f targetPos) // rotate function.
{
	float dX = targetPos.x - sprite.getPosition().x;
	float dY = targetPos.y - sprite.getPosition().y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	aimLaser.setRotation(rotation + 90.f);
}

void Player::move(sf::RectangleShape& aimLaser, float dt, bool isSinglePlayer) // player move function.
{
	if (isMove == true) { moveToTarget(moveTargetPos, dt, isSinglePlayer); }
}

void Player::updateReloadRect(char gameLanguage) // update reload rect function.
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
	if (gameLanguage == 'e')
	{
		reloadText.setString("RELOAD");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	else if (gameLanguage == 'r')
	{
		reloadText.setString(L"ÏÅÐÅÇÀÐßÄÊÀ");
		reloadText.setOrigin(round(reloadText.getLocalBounds().left + (reloadText.getLocalBounds().width / 2.f)), round(reloadText.getLocalBounds().top + (reloadText.getLocalBounds().height / 2.f)));
	}
	reloadText.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y - 50.f);
}