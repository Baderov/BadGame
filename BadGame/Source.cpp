#include "Source.h" // main header file.

#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

std::vector<std::unique_ptr<Entity>> s_entitiesVec; // entities vector for singleplayer.

void logsFunc(GameVariable * gv)
{
	while (gv->window.isOpen())
	{
		DEBUG_MSG("function name: " << gv->getFuncName());
	}
}

void updateFPS(GameVariable* gv) // FPS update function.
{
	gv->fpsCurrentTime = gv->fpsClock.getElapsedTime(); // assign the variable gv->fpsPreviousTime variable to elapsed time.
	gv->setFPS(floor(1.0f / (gv->fpsCurrentTime.asSeconds() - gv->fpsPreviousTime.asSeconds()))); // calculate fps.
	gv->fpsPreviousTime = gv->fpsCurrentTime; // assign the variable gv->fpsPreviousTime to the current time.
}

void s_eventHandler(GameVariable* gv, Minimap& minimap) // event handling function for singleplayer.
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
			if (getPlayerPtr() != nullptr)
			{
				getPlayerPtr()->setMoveTargetPos(gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window))); // write the coordinates of the mouse cursor to the moveTargetPos variable.
				getPlayerPtr()->setIsMove(true);
				gv->playerDestination.setPosition(getPlayerPtr()->getMoveTargetPos()); // set the label position to the mouse click location.
				gv->playerDestination.setOutlineColor(sf::Color::Yellow);
			}
			break;
		case sf::Mouse::Right:
			if (getPlayerPtr() != nullptr)
			{
				getPlayerPtr()->setIsShoot(true);
			}
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
		case sf::Keyboard::M:
			gv->setShowMinimap(!(gv->getShowMinimap()));
			break;
		case sf::Keyboard::R:
			if (getPlayerPtr() != nullptr && getPlayerPtr()->getCurrentAmmo() < 30 && getPlayerPtr()->getMaxAmmo() >= 1 && getPlayerPtr()->getIsReload() == false)
			{
				getPlayerPtr()->setIsReload(true);
				getPlayerPtr()->getReloadClock().restart();
				getPlayerPtr()->setReloadTime(0.f);
				getPlayerPtr()->setMenuTime(0.f);
			}
			break;
		case sf::Keyboard::Escape:
			if (s_enterMenu(gv, s_entitiesVec, minimap)) { return; }
			break;
		}
		break;
	}
}

void s_resetVariables(GameVariable* gv) // global variable reset function for singleplayer.
{
	gv->setNickname(L"");
	gv->gameClock.restart();
	gv->setGameViewSize(sf::Vector2f(1920.f, 1080.f));
	gv->setGameViewCenter(sf::Vector2f(0.f, 0.f));
	gv->setWindowView(gv->getGameView());
	gv->setShowMinimap(true);
}

void singleplayerGame(GameVariable* gv, Minimap& minimap) // singleplayer launch function.
{
	s_resetVariables(gv);
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		while (gv->window.pollEvent(gv->event))
		{
			s_eventHandler(gv, minimap); // call the event handling function.
			if (gv->getSinglePlayerGame() == false) { return; }
		}
		updateGame(gv, s_entitiesVec); // calling the entity update function.
		drawGame(gv, s_entitiesVec, minimap); // calling the entity drawing function.
		updateFPS(gv); // call the FPS update function.
	}
}

int main() // the main function of the program.
{
#ifdef _DEBUG
	//std::thread logsThread([&]() { logsFunc(gv); });
	//logsThread.detach();
#endif
	consoleSettings(); // call the function for setting settings for the console.
	GameVariable* gv = new GameVariable(); // initialized "gv" object to hold global variables.
	setVariables(gv); // setting values of global variables.
	Minimap minimap(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(5000.f, 5000.f), sf::Vector2f(0.8f, 0.f), sf::Vector2f(0.2f, 0.355f));
	menuEventHandler(gv, minimap); // calling the menu event handling function.
	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		while (gv->window.pollEvent(gv->event)) { if (gv->event.type == sf::Event::Closed) { gv->window.close(); } }
		if (gv->getSinglePlayerGame() == true && gv->getMultiPlayerGame() == false) { singleplayerGame(gv, minimap); }
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == true && gv->getConnectsToServer() == false) { multiplayerGame(gv, minimap); }
		if (gv->getSinglePlayerGame() == false && gv->getMultiPlayerGame() == false) { menuEventHandler(gv, minimap); }
	}
	delete gv; // clear memory.
	DEBUG_MSG("Memory cleared!"); // send message in console.
	return 1; // function termination.
}