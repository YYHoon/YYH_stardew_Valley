#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "MapToolScene.h"
#include "DummyMap.h"
#include <iostream>

#include "Inventory.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

class playGround : public gameNode
{
private:

	TitleScene* _TitleScene;
	TestScene* _Tset;
	MapToolScene* _MaptoolScene;
	Inventory* _Inv;
	DummyMap* _dummy;

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

