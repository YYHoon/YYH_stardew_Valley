#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	//player = new Player;
	//player->Init();
	//OBJECTMANAGER->AddGameObject("PLAYER", player);

	_Inv = new Inventory;
	_Inv->init();

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//연산
void playGround::update()
{
	gameNode::update();

	_Inv->update();

	OBJECTMANAGER->Update();
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	OBJECTMANAGER->Render();

	_Inv->render();

	ZORDER->ZOrderRender();
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imginit()
{
	
}

void playGround::soundinit()
{
	
}
