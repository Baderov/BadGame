﻿#include "Source.h" // подключаем заголовочный файл исходника проекта.

std::list<std::unique_ptr<Entity>> entities; // список сущностей.
std::list<std::unique_ptr<Entity>>::iterator it; // первый итератор для прохождения по списку сущностей.
std::list<std::unique_ptr<Entity>>::iterator it2; // второй итератор для прохождения по списку сущностей.

Entity* player = nullptr; // создаём указатель на игрока.

void updateTime(GameVariables* gv) // функция обновления времени.
{
	gv->dt = gv->clock.getElapsedTime().asMicroseconds(); // в переменную gv->dt присваиваются прошедшие микросекунды с момента создания переменной gv->clock.
	gv->clock.restart(); // перезагружает время.
	gv->dt = gv->dt / gv->divisor; // скорость игры, чем больше делитель (divisor), тем медленнее и наоборот.
}

void updateFPS(GameVariables* gv) // функция обновления FPS.
{
	gv->fpsCurrentTime = gv->fpsClock.getElapsedTime(); // присваиваем переменной gv->fpsCurrentTime прошедшее время 
	gv->fps = floor(1.0f / (gv->fpsCurrentTime.asSeconds() - gv->fpsPreviousTime.asSeconds())); // рассчитываем fps.
	gv->fpsPreviousTime = gv->fpsCurrentTime; // присваиваем переменной gv->fpsPreviousTime текущее время.
}

void eventHandler(sf::Event& event, GameVariables* gv) // функция обработки событий.
{
	switch (gv->event.type) // проверка по типу событий.
	{
	case sf::Event::Closed: // если событие приняло значение "Закрыто".
		gv->window.close(); // закрываем окно.
		break; // выходим.
	case sf::Event::MouseButtonPressed: // если нажата кнопка мыши.
		switch (gv->event.mouseButton.button) // проверка по кнопке мыши.
		{
		case sf::Mouse::Left: // если левая кнопка мыши.
			if (player != nullptr)
			{
				player->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // записываем в переменную moveTargetPos координаты курсора мыши.
				player->setIsMove(true); // игрок может двигаться.
				gv->playerDestination.setPosition(player->getMoveTargetPos()); // устанавливаем позицию метки в место клика мыши. 
				gv->playerDestination.setOutlineColor(sf::Color::Yellow); // устанавливаем цвет контура метки.
			}
			break; // выходим.
		case sf::Mouse::Right: // если правая кнопка мыши.
			if (player != nullptr) { player->setIsShoot(true); }
			break; // выходим.
		}
		break;
	case sf::Event::KeyReleased: // если отпустили клавишу.
		switch (gv->event.key.code) // проверка по клавише.
		{
		case sf::Keyboard::Z: // если клавиша Z.
			if (gv->showLogs == false) { gv->showLogs = true; } // если логи не были показаны - показываем.
			else { gv->showLogs = false; } // если логи были показаны - не показываем.
			break; // выходим.

		case sf::Keyboard::X: // если клавиша X.
			if (gv->showHitbox == false) { gv->showHitbox = true; } // если хитбоксы не были показаны - показываем.
			else { gv->showHitbox = false; } // если хитбоксы были показаны - не показываем.
			break; // выходим.

		case sf::Keyboard::C: // если клавиша C.
			if (gv->showAimLaser == false) { gv->showAimLaser = true; } // если прицельный лазер не был показан - показываем.
			else { gv->showAimLaser = false; } // если прицельный лазер был показан - не показываем.
			break; // выходим.

		case sf::Keyboard::R: // если клавиша R.
			if (player != nullptr && player->getCurrentAmmo() < 30 && player->getIsReload() == false)
			{
				player->setIsReload(true);
				player->getReloadClock().restart();
				player->setReloadTime(0);
			}
			break; // выходим.
		}
		break;

	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // проверка по клавише.
		{
		case sf::Keyboard::Escape: // если клавиша Esc.
			sf::Vector2f oldViewSize(gv->view.getSize());
			sf::Vector2f oldViewCenter(gv->view.getCenter());

			gv->view.setSize(gv->window.getSize().x, gv->window.getSize().y);
			gv->view.setCenter(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f);
			gv->window.setView(gv->view);

			menuEventHandler(gv, player);

			gv->view.setSize(oldViewSize);
			gv->view.setCenter(oldViewCenter);
			gv->window.setView(gv->view);

			gv->clock.restart(); // перезагружает время.
			break; // выходим.
		}
		break;
		//case sf::Event::MouseWheelScrolled:
		//{
		//	if (gv->event.mouseWheelScroll.delta < 0)
		//	{
		//		gv->view.zoom(1.1f); // увеличиваем зум.
		//	}
		//	else if (gv->event.mouseWheelScroll.delta > 0)
		//	{
		//		gv->view.zoom(0.9f); // уменьшаем зум.
		//	}
		//	break;
		//}
	}
}

int main() // главная функция программы.
{
	consoleSettings(); // вызов функции установки настроек для консоли.
	//startNetwork();
	GameVariables* gv = new GameVariables(); // создаётся переменная gv, для передачи в параметры функций значений игровых переменных.
	setVariables(gv);
	authorization(gv);
	gv->window.setKeyRepeatEnabled(false); // отключаем повторное нажатие клавиш.
	menuEventHandler(gv, player);
	gv->clock.restart(); // перезагружает время.
	while (gv->window.isOpen()) // пока открыто окно.
	{
		if (gv->isGameStarted == false)
		{
			restartGame(gv, entities, player);
			gv->isGameStarted = true;
		}
		updateTime(gv); // вызов функции обновления времени.
		setGameInfo(gv, player, entities); // вызов функции установки игровой информации.
		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			eventHandler(gv->event, gv); // вызов функции обработки событий.
		}
		gv->window.setView(gv->view);
		updateEntities(gv, entities, it, it2, player); // вызов функции обновления сущностей.
		gv->window.clear(gv->backgroundColor); // очистка окна.
		drawEntities(gv, entities, it); // вызов функции рисовки сущностей.
		drawGameInfo(gv); // вызов функции рисовки игровой информации.
		gv->window.display(); // отображает кадр.
		updateFPS(gv); // вызов функции обновления FPS.
	}
	delete gv; // удаляем переменную gv.
	std::cout << "Memory cleared!\n"; // отправляем сообщение в консоль.
	return 0; // завершение работы функции.
}