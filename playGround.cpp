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
	SCENEMANAGER->addScene("탱크씬", new tankScene);
	SCENEMANAGER->changeScene("탱크씬");
	_toolItem = new ToolItemManager;

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	
	_toolItem->Action("Pickax");


}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	SCENEMANAGER->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imginit()
{
	
}

void playGround::soundinit()
{
	
}
