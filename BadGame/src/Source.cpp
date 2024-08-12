#include "pch.h"
#include "Source.h"

//void logsFunc(std::unique_ptr<SingleplayerManager>& sm)
//{
//	while (gw->window.isOpen())
//	{
//		DEBUG_MSG(L"function name: " + gv->getFuncName());
//		sf::sleep(sf::milliseconds(1));
//	}
//}

void initObjects(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm)
{
	boxesPool.init(gv, gw, sm, nm, boxesVec, 24);
	bulletsPool.init(gv, gw, sm, nm, bulletsVec, 1000);
	enemiesPool.init(gv, gw, sm, nm, enemiesVec, 1000);
	wallsPool.init(gv, gw, sm, nm, wallsVec, 4);
	itemsPool.init(gv, gw, sm, nm, itemsVec, 2000);
	clientsPool.init(gv, gw, sm, nm, clientsVec, 500);

	for (size_t i = 0; i < 4; ++i) { wallsPool.getFromPool(wallsVec); }

	wallsVec[0]->init(gv, sf::Vector2f(0.f, 0.f), WallType::LeftWall);
	wallsVec[1]->init(gv, sf::Vector2f(5000.f, 0.f), WallType::RightWall);
	wallsVec[2]->init(gv, sf::Vector2f(0.f, 0.f), WallType::TopWall);
	wallsVec[3]->init(gv, sf::Vector2f(0.f, 4936.f), WallType::BottomWall);

	playerPtr = std::make_unique<Player>(gv, gw, sm, nm);

	std::cout << "\n";
}

void resetObjects(std::unique_ptr<SingleplayerManager>& sm)
{
	boxesVec.clear();
	bulletsVec.clear();
	enemiesVec.clear();
	wallsVec.clear();
	itemsVec.clear();
	clientsVec.clear();

	boxesPool.clear();
	bulletsPool.clear();
	enemiesPool.clear();
	wallsPool.clear();
	itemsPool.clear();
	clientsPool.clear();

	playerPtr.reset();
}

int main()
{
	auto gw = std::make_unique<GameWindow>();
	auto gv = std::make_unique<GameVariable>();
	auto sm = std::make_unique<SingleplayerManager>(gv->consolasFont);
	auto nm = std::make_unique<NetworkManager>();
	auto cw = std::make_unique<CustomWidget>(gw);

	Minimap minimap;

	initObjects(gv, gw, sm, nm);

	//#ifdef _DEBUG
		//std::thread logsThread(logsFunc, std::ref(sm));
		//logsThread.detach();
	//#endif

	std::thread recvThread(receiveData, std::ref(gv), std::ref(gw), std::ref(sm), std::ref(nm), std::ref(cw));
	std::thread sendThread(sendData, std::ref(gv), std::ref(gw), std::ref(sm), std::ref(nm), std::ref(cw));
	std::thread connectionThread(startNetwork, std::ref(gv), std::ref(nm));

	recvThread.detach();
	sendThread.detach();
	connectionThread.detach();

	menuEventHandler(gv, gw, sm, nm, cw, minimap, MenuType::MainMenu);

	while (gw->window.isOpen())
	{
		sf::Event event;
		while (gw->window.pollEvent(event)) { if (event.type == sf::Event::Closed) { gw->window.close(); } }

		if (gv->getGameState() == GameState::StartGame)
		{
			if (gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { singleplayerGame(gv, gw, sm, nm, cw, minimap); }
			if (!gv->getIsSingleplayer() && gv->getIsMultiplayer() && !nm->getConnectsToServer()) { multiplayerGame(gv, gw, sm, nm, cw, minimap); }
		}
		else
		{
			if (!gv->getIsSingleplayer() && !gv->getIsMultiplayer()) { menuEventHandler(gv, gw, sm, nm, cw, minimap, MenuType::MainMenu); }
		}
	}

	resetObjects(sm);

	return 1;
}