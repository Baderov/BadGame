#include "Player.h" // header file for player.

Player::Player(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name) // player constructor.
{
	isMove = false;
	isReload = false;
	currentVelocity = sf::Vector2f(0.6f, 0.6f);
	maxSpeed = 5.f;
	HP = 100;
	goldCoins = 0;
	maxHP = HP;
	moveTargetPos = currentPos;

	magazineAmmo = 30;
	currentAmmo = magazineAmmo;
	maxAmmo = 500;
	missingAmmo = 0;

	reloadTime = 0;

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

}

void Player::update(GameVariables* gv) // player update function.
{
	if (isAlive == true)
	{
		if (isReload == true) 
		{
			reloadTime = reloadClock.getElapsedTime().asMilliseconds() - menuTime;
			if (reloadTime < 0) { reloadTime = 0; }
			updateReloadRect();
		}
		nameText.setPosition(currentPos.x, currentPos.y - 90.f);
		updateHPBar();

		rotate(gv);
		updateLaser(gv);
		move(gv);
		sprite.setPosition(currentPos);
		rectHitbox.setPosition(currentPos);
		gv->aimLaser.setPosition(currentPos);
		gv->view.setCenter(currentPos);

		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);

		if (HP <= 0) // if the player's health is zero or less, then he is dead.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Player::rotate(GameVariables* gv) // player rotate function.
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // get mouse coordinates.
	float dX = gv->mousePos.x - currentPos.x;
	float dY = gv->mousePos.y - currentPos.y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

void Player::move(GameVariables* gv) // player move function.
{
	if (isMove == true) { moveToTarget(moveTargetPos, gv); }	
}

void Player::updateLaser(GameVariables* gv) // laser update function.
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // get mouse coordinates.
	float distance = sqrt(((gv->mousePos.x - currentPos.x) * (gv->mousePos.x - currentPos.x)) + ((gv->mousePos.y - currentPos.y) * (gv->mousePos.y - currentPos.y)));
	gv->aimLaserLength = distance;
	gv->aimLaser.setSize(sf::Vector2f(2.25f, -gv->aimLaserLength));
}

void Player::updateReloadRect() // update reload rect function.
{
	reloadRectOuter.setSize(sf::Vector2f(200.f, 20.f));
	sf::Int32 tempReloadTime = 0;
	if (reloadTime > 0)
	{
		tempReloadTime = reloadTime / static_cast<sf::Int32>(10);
	}

	sf::Int32 reloadRectOuterSizeX = static_cast<sf::Int32>(reloadRectOuter.getSize().x);
	
	if (tempReloadTime < reloadRectOuterSizeX)
	{
		reloadRectInner.setSize(sf::Vector2f(static_cast<float>(tempReloadTime), reloadRectOuter.getSize().y));
	}
	else
	{
		reloadRectInner.setSize(sf::Vector2f(0.f, reloadRectOuter.getSize().y));
	}
	
	reloadRectOuter.setPosition(currentPos.x - 90.f, currentPos.y + 300.f);
	reloadRectInner.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);
}