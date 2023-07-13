#include "pch.h"
#include "Source.h" // main header file.

//void logsFunc(std::unique_ptr<GameVariable>& gv)
//{
//	while (gv->window.isOpen())
//	{
//		DEBUG_MSG("function name: " << gv->getFuncName());
//		sf::sleep(sf::milliseconds(1));
//	}
//}

sf::Time fpsPreviousTime, fpsCurrentTime;
sf::Clock fpsClock;

float fps = 0.f;

void updateFPS(sf::Time& fpsPreviousTime, sf::Time& fpsCurrentTime, sf::Clock& fpsClock, float& fps) // FPS update function.
{
	fpsCurrentTime = fpsClock.getElapsedTime(); // assign the variable gv->fpsPreviousTime variable to elapsed time.
	fps = floor(1.0f / (fpsCurrentTime.asSeconds() - fpsPreviousTime.asSeconds())); // calculate fps.
	fpsPreviousTime = fpsCurrentTime; // assign the variable gv->fpsPreviousTime to the current time.
}

void initObjects(std::unique_ptr<GameVariable>& gv)
{
	boxPool.init(gv, boxVec, 24);
	bulletPool.init(gv, bulletVec, 1000);
	enemyPool.init(gv, enemyVec, 1000);
	wallPool.init(gv, wallVec, 4);
	itemPool.init(gv, itemVec, 2000);
	clientPool.init(gv, clientVec, 500);
	playerPtr = std::make_unique<Player>(gv);

	for (int i = 0; i < 4; i++) { wallPool.getFromPool(wallVec); }
	wallVec[0]->init(gv, sf::Vector2f(0.f, 0.f), L"LeftWall");
	wallVec[1]->init(gv, sf::Vector2f(5000.f, 0.f), L"RightWall");
	wallVec[2]->init(gv, sf::Vector2f(0.f, 0.f), L"TopWall");
	wallVec[3]->init(gv, sf::Vector2f(0.f, 4936.f), L"BottomWall");
}

void singleplayerGame(std::unique_ptr<GameVariable>& gv, Minimap& minimap, PlayersList& playersList, Chat& chat) // singleplayer launch function.
{
	resetVariables(gv, chat, playersList);
	setGameResult(gv);
	fpsClock.restart();
	playerPtr->init(gv, gv->getPlayerStartPos(), gv->getNickname());

	while (gv->getIsSingleplayer())
	{
		DEBUG_SET_FUNC_NAME;
		updateGame(gv, minimap, playersList, chat, fps); // calling the entity update function.
		drawGame(gv, minimap); // calling the entity drawing function.
		updateFPS(fpsPreviousTime, fpsCurrentTime, fpsClock, fps); // call the FPS update function.
	}
}

int main() // the main function of the program.
{
	consoleSettings(); // call the function for setting settings for the console.
	Minimap minimap(sf::Vector2f(1920.f, 1080.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(5000.f, 5000.f), sf::Vector2f(0.8f, 0.f), sf::Vector2f(0.2f, 0.355f));
	Chat chat;
	PlayersList playersList;
	auto gv = std::make_unique<GameVariable>();
	setVariables(gv); // setting values of global variables.
	initObjects(gv);

	//#ifdef _DEBUG
		//std::thread logsThread(logsFunc, std::ref(gv));
		//logsThread.detach();
	//#endif

	std::thread recvThread(receiveData, std::ref(gv), std::ref(minimap), std::ref(playersList), std::ref(chat));
	std::thread sendThread(sendData, std::ref(gv), std::ref(chat));
	std::thread connectionThread(startNetwork, std::ref(gv));
	recvThread.detach();
	sendThread.detach();
	connectionThread.detach();

	menuEventHandler(gv, minimap, playersList, chat); // calling the menu event handling function.

	while (gv->window.isOpen())
	{
		DEBUG_SET_FUNC_NAME;
		while (gv->window.pollEvent(gv->event)) { if (gv->event.type == sf::Event::Closed) { gv->window.close(); } }
		if (gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { singleplayerGame(gv, minimap, playersList, chat); }
		if (!gv->getIsSingleplayer() && gv->getIsMultiplayer() && !gv->getConnectsToServer()) { multiplayerGame(gv, minimap, playersList, chat); }
		if (!gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { menuEventHandler(gv, minimap, playersList, chat); }
	}
	return 1; // function termination.
}