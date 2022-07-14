#include "Enemy.h" // подключаем заголовочный файл.

Enemy::Enemy(sf::Image& image, sf::Vector2f startPos, std::wstring name) : Entity(image, startPos, name)
{
	currentVelocity = sf::Vector2f(0.4f, 0.4f);
	maxSpeed = 5.f;
	HP = 100;
	maxHP = HP;
	shootDelay = 2000;
	shootTime = 0;
	shootOffset = 0 + rand() % (shootDelay / 2);
	moveTargetPos.x = 0 + rand() % 3000;
	moveTargetPos.y = 0 + rand() % 3000;

	rectHitbox.setFillColor(sf::Color::Red);
	rectHitbox.setSize(sf::Vector2f(h, h));
	rectHitbox.setOrigin(rectHitbox.getSize().x / 2.f, rectHitbox.getSize().y / 2.f);
}

void Enemy::update(GameVariables* gv) // функция update (в параметрах передаем время).
{
	if (isAlive == true)
	{
		updateHPBar();
		shootTime = (shootClock.getElapsedTime().asMilliseconds() + shootOffset) - menuTime;		
		if (shootTime >= shootDelay)
		{
			isShoot = true;
			menuTime = 0;
			shootClock.restart();
			moveTargetPos.x = 0 + rand() % 3000;
			moveTargetPos.y = 0 + rand() % 3000;
		}
		rotate();
		move(gv);
		hpText.setString(std::to_string(HP));
		hpText.setPosition(HPBarOuter.getPosition().x + 5.f, HPBarOuter.getPosition().y - 3.f);
		sprite.setPosition(currentPos);
		rectHitbox.setPosition(currentPos);
		if (HP <= 0) { isAlive = false; } // если здоровье игрока равна нулю или меньше, то его жизнь равна False, то есть он мёртв.
	}
}

void Enemy::rotate()
{
	float dX = aimPos.x - currentPos.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = aimPos.y - currentPos.y;//он же, координата y
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
	sprite.setRotation(rotation);
}

void Enemy::move(GameVariables* gv)
{
	moveToTarget(moveTargetPos, gv);	
}