#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"
#include "AllUi.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "MapToolScene.h"
#include "MapManager.h"
#include <iostream>

#include <algorithm>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

class playGround : public gameNode
{
private:
	TitleScene* _TitleScene;
	TestScene* _Tset;
	MapToolScene* _MaptoolScene;

	LoadingScene* _LoadingScene;
	MapFarm* map;
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

