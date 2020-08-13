#include "stdafx.h"
#include "MapManager.h"
void MapManager::Init()
{
	MapFarm* _farm;
	MapHome* _home;
	MapTest* _test;
	SCENEMANAGER->addScene("FARM",_farm = new MapFarm);
	SCENEMANAGER->addScene("HOME", _home = new MapHome);
	SCENEMANAGER->addScene("Test", _test = new MapTest);
	
}