#include "Player.h" // подключаем заголовочный файл.

Player::Player(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name)
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

	reloadText.setFont(consolasFont); // устанавливаем шрифт.
	reloadText.setString("RELOAD");
	reloadText.setCharacterSize(50);
	reloadText.setFillColor(sf::Color::Black); // устанавливаем цвет текста.
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);

	nameText.setString(name);
	nameText.setOrigin(round(nameText.getLocalBounds().left + (nameText.getLocalBounds().width / 2.f)), round(nameText.getLocalBounds().top + (nameText.getLocalBounds().height / 2.f)));

}

void Player::update(GameVariables* gv) // функция update (в параметрах передаем время).
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

		if (HP <= 0) // если здоровье игрока равна нулю или меньше, то его жизнь равна False, то есть он мёртв.
		{
			gv->aimLaser.setSize(sf::Vector2f(0.f, 0.f));
			isAlive = false;
		}
	}
}

void Player::rotate(GameVariables* gv)
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window));//переводим их в игровые (уходим от коорд окна)
	float dX = gv->mousePos.x - currentPos.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = gv->mousePos.y - currentPos.y;//он же, координата y
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
	sprite.setRotation(rotation);
	gv->aimLaser.setRotation(rotation + 90.f);
}

void Player::move(GameVariables* gv)
{
	if (isMove == true) { moveToTarget(moveTargetPos, gv); }	
}

void Player::updateLaser(GameVariables* gv)
{
	gv->mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window));//переводим их в игровые (уходим от коорд окна)
	float distance = sqrt(((gv->mousePos.x - currentPos.x) * (gv->mousePos.x - currentPos.x)) + ((gv->mousePos.y - currentPos.y) * (gv->mousePos.y - currentPos.y)));
	gv->aimLaserLength = distance;
	gv->aimLaser.setSize(sf::Vector2f(2.25f, -gv->aimLaserLength));
}

void Player::updateReloadRect()
{
	reloadRectOuter.setSize(sf::Vector2f(200.f, 20.f));
	int tempReloadTime = 0;
	if (reloadTime > 0)
	{
		tempReloadTime = reloadTime / 10;
	}

	int reloadRectOuterSizeX = static_cast<int>(reloadRectOuter.getSize().x);
	
	if (tempReloadTime < reloadRectOuterSizeX)
	{
		reloadRectInner.setSize(sf::Vector2f(tempReloadTime, reloadRectOuter.getSize().y));
	}
	else
	{
		reloadRectInner.setSize(sf::Vector2f(0.f, reloadRectOuter.getSize().y));
	}
	
	reloadRectOuter.setPosition(currentPos.x - 90.f, currentPos.y + 300.f);
	reloadRectInner.setPosition(reloadRectOuter.getPosition().x, reloadRectOuter.getPosition().y);
	reloadText.setPosition(reloadRectOuter.getPosition().x + 15.f, reloadRectOuter.getPosition().y - 100.f);
}