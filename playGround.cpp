#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
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

//�޸� ����
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//����
void playGround::update()
{
	gameNode::update();

	_Inv->update();

	OBJECTMANAGER->Update();
}

//�׸��� ����
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
