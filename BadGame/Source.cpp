#include "Source.h" // main header file.

std::list<std::unique_ptr<Entity>> entities; // list of entities.
std::list<std::unique_ptr<Entity>>::iterator it; // first iterator for passing through the list of entities.
std::list<std::unique_ptr<Entity>>::iterator it2; // second iterator for passing through the list of entities.

#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

void updateFPS(GameVariable* gv) // FPS update function.
{
	gv->fpsCurrentTime = gv->fpsClock.getElapsedTime(); // assign the variable gv->fpsPreviousTime variable to elapsed time.
	gv->setFPS(floor(1.0f / (gv->fpsCurrentTime.asSeconds() - gv->fpsPreviousTime.asSeconds()))); // calculate fps.
	gv->fpsPreviousTime = gv->fpsCurrentTime; // assign the variable gv->fpsPreviousTime to the current time.
}

void eventHandlerSingleplayer(GameVariable* gv) // event handling function.
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
			if (getPlayerPtr() != nullptr) // if the playerPtr is alive.
			{
				getPlayerPtr()->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
				getPlayerPtr()->setIsMove(true);
				gv->playerDestination.setPosition(getPlayerPtr()->getMoveTargetPos()); // set the label position to the mouse click location.
				gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			}
			break;
		case sf::Mouse::Right:
			if (getPlayerPtr() != nullptr) { getPlayerPtr()->setIsShoot(true); }
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Z:
			if (gv->getShowLogs() == false) { gv->setShowLogs(true); } // if the logs were not shown - show.
			else { gv->setShowLogs(false); } // if the logs were shown - don't show them.
			break;

		case sf::Keyboard::X:
			if (gv->getShowHitbox() == false) { gv->setShowHitbox(true); } // if hitboxes weren't shown - show them.
			else { gv->setShowHitbox(false); } // if hitboxes were shown, don't show them.
			break;

		case sf::Keyboard::C:
			if (gv->getShowAimLaser() == false) { gv->setShowAimLaser(true); } // if the aiming laser was not shown - show.
			else { gv->setShowAimLaser(false); } // if the aiming laser was shown - don't show it.
			break;

		case sf::Keyboard::R:
			if (getPlayerPtr() != nullptr && getPlayerPtr()->getCurrentAmmo() < 30 && getPlayerPtr()->getIsReload() == false)
			{
				getPlayerPtr()->setIsReload(true);
				getPlayerPtr()->getReloadClock().restart();
				getPlayerPtr()->setReloadTime(0.f);
				getPlayerPtr()->setMenuTime(0.f);
			}
			break;
		}
		break;
	case sf::Event::KeyPressed:
		switch (gv->event.key.code) // check by key code.
		{
		case sf::Keyboard::Escape:
			gv->menuClock.restart();
			menuEventHandler(gv);
			gv->setMenuTimer(gv->menuClock.getElapsedTime().asSeconds());

			for (it = entities.begin(); it != entities.end(); it++) // iterate through the list from beginning to end.
			{
				Entity* entity = (*it).get();
				if (getPlayerPtr() != nullptr && (dynamic_cast<Enemy*>(entity) || dynamic_cast<Player*>(entity)))
				{
					entity->setMenuTime(gv->getMenuTimer() + entity->getMenuTime());
				}
			}
			gv->gameClock.restart();
			if (gv->getSinglePlayerGame() == false) { return; }

			gv->window.setView(gv->getGameView());
			break;
		}
		break;
	}
}

void singleplayerGame(GameVariable* gv) // single playerPtr launch function.
{
	gv->setNickname(L"");
	gv->gameClock.restart();
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		if (gv->getRestartGame() == true)
		{
			restartGame(gv, entities);
			gv->setRestartGame(false);
		}
		gv->setDT(gv->gameClock.restart().asSeconds());
		setGameInfo(gv, getPlayerPtr(), entities); // call the function for setting game information.
		while (gv->window.pollEvent(gv->event))
		{
			eventHandlerSingleplayer(gv); // call the event handling function.
			if (gv->getSinglePlayerGame() == false) { return; }
		}
		gv->window.setView(gv->getGameView());
		updateEntities(gv, entities, it, it2); // calling the entity update function.
		gv->window.clear(gv->backgroundColor);
		drawEntities(gv, entities, it); // calling the entity drawing function.
		drawGameInfo(gv); // calling the function for drawing game information.
		gv->window.display();
		updateFPS(gv); // call the FPS update function.
	}
}

void logsFunc(GameVariable* gv)
{
	while (gv->window.isOpen())
	{
		DEBUG_MSG("function name: " << gv->getFuncName());
	}
}

int main() // the main function of the program.
{
	consoleSettings(); // call the function for setting settings for the console.
	GameVariable* gv = new GameVariable(); // initialized "gv" object to hold global variables.
	setVariables(gv); // setting values of global variables.
	std::thread recvThread([&]() { receiveData(gv); });
	std::thread sendThread([&]() { sendData(gv); });
	recvThread.detach();
	sendThread.detach();
#ifdef _DEBUG
	//std::thread logsThread([&]() { logsFunc(gv); });
	//logsThread.detach();
#endif
	menuEventHandler(gv); // calling the menu event handling function.
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		while (gv->window.pollEvent(gv->event)) { if (gv->event.type == sf::Event::Closed) { gv->window.close(); } }
		if (gv->getSinglePlayerGame() == true && gv->getMultiPlayerGame() == false) { singleplayerGame(gv); }
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == true && gv->getNetworkEnd() == true) { multiplayerGame(gv); }
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == false) { menuEventHandler(gv); }
	}
	delete gv; // clear memory.
	DEBUG_MSG("Memory cleared!"); // send message in console.
	return 1; // function termination.
}