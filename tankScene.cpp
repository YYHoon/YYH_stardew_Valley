#include "stdafx.h"
#include "tankScene.h"


tankScene::tankScene()
{
}


tankScene::~tankScene()
{
}

HRESULT tankScene::init()
{

	_tankMap = new tileMap;
	_tank = new tank;
	_tank->setTankMapMemoryAddressLink(_tankMap);
	_tankMap->init();
	_tank->init();


	return S_OK;
}

void tankScene::release()
{
}

void tankScene::update()
{
	_tank->update();
}

void tankScene::render()
{
	_tankMap->render();
	_tank->render();
}
