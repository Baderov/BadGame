#include "Source.h" // main header file.

std::list<std::unique_ptr<Entity>> entities; // list of entities.
std::list<std::unique_ptr<Entity>>::iterator it; // first iterator for passing through the list of entities.
std::list<std::unique_ptr<Entity>>::iterator it2; // second iterator for passing through the list of entities.

Entity* player = nullptr; // create a pointer to the player.

void updateTime(GameVariables* gv) // time update function.
{
	gv->dt = gv->clock.getElapsedTime().asMicroseconds(); // gv->dt is set to the elapsed microseconds since gv->clock was created.
	gv->clock.restart();
	gv->dt = gv->dt / gv->divisor; // game speed, the larger the divisor, the slower and vice versa.
}

void updateFPS(GameVariables* gv) // FPS update function.
{
	gv->fpsCurrentTime = gv->fpsClock.getElapsedTime(); // assign the variable gv->fpsPreviousTime variable to elapsed time.
	gv->fps = floor(1.0f / (gv->fpsCurrentTime.asSeconds() - gv->fpsPreviousTime.asSeconds())); // calculate fps.
	gv->fpsPreviousTime = gv->fpsCurrentTime; // assign the variable gv->fpsPreviousTime to the current time.
}

void eventHandler(sf::Event& event, GameVariables* gv) // event handling function.
{
	switch (gv->event.type) // check by event type.
	{
	case sf::Event::Closed:
		gv->window.close();
		break;
	case sf::Event::MouseButtonPressed:
		switch (gv->event.mouseButton.button) // check by mouse button.
		{
		case sf::Mouse::Left:
			if (player != nullptr) // if the player is alive.
			{
				player->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
				player->setIsMove(true);
				gv->playerDestination.setPosition(player->getMoveTargetPos()); // set the label position to the mouse click location.
				gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			}
			break;
		case sf::Mouse::Right:
			if (player != nullptr) { player->setIsShoot(true); }
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Z:
			if (gv->showLogs == false) { gv->showLogs = true; } // if the logs were not shown - show.
			else { gv->showLogs = false; } // if the logs were shown - don't show them.
			break;

		case sf::Keyboard::X:
			if (gv->showHitbox == false) { gv->showHitbox = true; } // if hitboxes weren't shown - show them.
			else { gv->showHitbox = false; } // if hitboxes were shown, don't show them.
			break;

		case sf::Keyboard::C:
			if (gv->showAimLaser == false) { gv->showAimLaser = true; } // if the aiming laser was not shown - show.
			else { gv->showAimLaser = false; } // if the aiming laser was shown - don't show it.
			break;

		case sf::Keyboard::R:
			if (player != nullptr && player->getCurrentAmmo() < 30 && player->getIsReload() == false)
			{
				player->setIsReload(true);
				player->getReloadClock().restart();
				player->setReloadTime(0);
				player->setMenuTime(0);
			}
			break;
		}
		break;

	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Escape:
			sf::Vector2f oldViewSize(gv->view.getSize());
			sf::Vector2f oldViewCenter(gv->view.getCenter());

			gv->view.setSize(static_cast<float>(gv->window.getSize().x), static_cast<float>(gv->window.getSize().y));
			gv->view.setCenter(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f);
			gv->window.setView(gv->view);

			gv->menuClock.restart();
			menuEventHandler(gv, player);
			gv->menuTimer = gv->menuClock.getElapsedTime().asMilliseconds();

			for (it = entities.begin(); it != entities.end(); it++) // iterate through the list from beginning to end.
			{
				Entity* entity = (*it).get();
				if (player != nullptr && (dynamic_cast<Enemy*>(entity) || dynamic_cast<Player*>(entity)))
				{
					entity->setMenuTime(gv->menuTimer + entity->getMenuTime());
				}
			}

			gv->clock.restart();
			if (gv->singlePlayerGame == false) { return; }

			gv->view.setSize(oldViewSize);
			gv->view.setCenter(oldViewCenter);
			gv->window.setView(gv->view);

			break;
		}
		break;
		//case sf::Event::MouseWheelScrolled:
		//{
		//	if (gv->event.mouseWheelScroll.delta < 0)
		//	{
		//		gv->view.zoom(1.1f);
		//	}
		//	else if (gv->event.mouseWheelScroll.delta > 0)
		//	{
		//		gv->view.zoom(0.9f);
		//	}
		//	break;
		//}
	}
}

void singleplayerGame(GameVariables* gv) // single player launch function.
{
	gv->clock.restart();
	while (gv->window.isOpen())
	{
		if (gv->restartGame == true)
		{
			restartGame(gv, entities, player);
			gv->restartGame = false;
		}
		updateTime(gv); // call the time update function.
		setGameInfo(gv, player, entities); // call the function for setting game information.
		while (gv->window.pollEvent(gv->event))
		{
			eventHandler(gv->event, gv); // call the event handling function.
			if (gv->singlePlayerGame == false) { return; }
		}
		gv->window.setView(gv->view);
		updateEntities(gv, entities, it, it2, player); // calling the entity update function.
		gv->window.clear(gv->backgroundColor);
		drawEntities(gv, entities, it); // calling the entity drawing function.
		drawGameInfo(gv); // calling the function for drawing game information.
		gv->window.display();
		updateFPS(gv); // call the FPS update function.
	}
}

int main() // the main function of the program.
{
	setlocale(LC_ALL, "RUS"); // for Cyrillic in the console.
	consoleSettings(); // call the function for setting settings for the console.
	GameVariables* gv = new GameVariables(); // initialized "gv" object to hold global variables.
	setVariables(gv); // setting values of global variables.
	menuEventHandler(gv, player); // calling the menu event handling function.
	while (gv->window.isOpen())
	{
		while (gv->window.pollEvent(gv->event))
		{
			if (gv->event.type == sf::Event::Closed)
			{
				gv->window.close();
			}
		}
		if (gv->singlePlayerGame == true && gv->multiPlayerGame == false)
		{
			singleplayerGame(gv);
		}

		if (gv->singlePlayerGame == false && gv->multiPlayerGame == true)
		{
			multiplayerGame(gv, player);
		}

		if (gv->singlePlayerGame == false && gv->multiPlayerGame == false)
		{
			menuEventHandler(gv, player);
		}
	}
	delete gv; // clear memory.
	std::cout << "Memory cleared!\n"; // send message in console.
	return 0; // function termination.
}