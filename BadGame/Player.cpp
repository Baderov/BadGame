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
	moveTargetPos = currentPos;

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

void Player::update(GameVariable* gv) // player update function.
{
	if (isAlive == true)
	{
		gv->setMousePos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)));
		rotate(gv);
		updateLaser(gv);
		move(gv);

		if (isReload == true)
		{
			reloadTime = reloadClock.getElapsedTime().asSeconds() - menuTime;
			if (reloadTime < 0.f) { reloadTime = 0.f; }
			updateReloadRect();
		}
		nameText.setPosition(currentPos.x, currentPos.y - 90.f);

		sprite.setPosition(currentPos);
		icon.setPosition(currentPos);
		rectHitbox.setPosition(currentPos);
		gv->aimLaser.setPosition(currentPos);
	
		gv->setGameViewCenter(sprite.getPosition());
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

void Player::rotate(GameVariable* gv) // player rotate function.
{
	float dX = gv->getMousePos().x - currentPos.x;
	float dY = gv->getMousePos().y - currentPos.y;
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265f; // get the angle in radians and convert it to degrees
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

void Player::move(GameVariable* gv) // player move function.
{
	if (isMove == true) { moveToTarget(moveTargetPos, gv); }
}

void Player::updateLaser(GameVariable* gv) // laser update function.
{
	float dist = sqrt(((gv->getMousePos().x - currentPos.x) * (gv->getMousePos().x - currentPos.x)) + ((gv->getMousePos().y - currentPos.y) * (gv->getMousePos().y - currentPos.y)));
	gv->setAimLaserLength(dist);
	gv->aimLaser.setSize(sf::Vector2f(2.25f, -gv->getAimLaserLength()));
}

void Player::updateReloadRect() // update reload rect function.
{
	reloadRectOuter.setSize(sf::Vector2f(200.f, 20.f));
	float tempReloadTime = 0.f;
	if (reloadTime > 0.f) { tempReloadTime = (reloadTime * 1000.f) / 10.f; }
	float reloadRectOuterSizeX = reloadRectOuter.getSize().x;
	if (tempReloadTime < reloadRectOuterSizeX) { reloadRectInner.setSize(sf::Vector2f(tempReloadTime, reloadRectOuter.getSize().y)); }
	else { reloadRectInner.setSize(sf::Vector2f(0.f, reloadRectOuter.getSize().y)); }
	reloadRectOuter.setPosition(currentPos.x - 90.f, currentPos.y + 300.f);
	reloadRectInner.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);
}