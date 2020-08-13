#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"
#include "AllUi.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "MapToolScene.h"
#include "DummyMap.h"
#include "MapManager.h"
#include <iostream>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

class playGround : public gameNode
{
private:
	TitleScene* _TitleScene;
	TestScene* _Tset;
	DummyMap* _dummy;
	MapToolScene* _MaptoolScene;
	MapTest* _test;
	LoadingScene* _LoadingScene;
	MapManager* _mapManager;
	Inventory* _Inv;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imginit();
	void soundinit();
};

