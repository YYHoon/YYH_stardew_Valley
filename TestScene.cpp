#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

HRESULT TestScene::init()
{
	_Mouse = IMAGEMANAGER->findImage("mouse");

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
}

void TestScene::render()
{
	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);

	char mo[200];
	char mo2[200];
	sprintf_s(mo, "마우스의 X좌표:%d", _ptMouse.x);
	sprintf_s(mo2, "마우스의 Y좌표:%d", _ptMouse.y);
	TextOut(getMemDC(), 50, 90, mo, strlen(mo));
	TextOut(getMemDC(), 50, 120, mo2, strlen(mo2));
}
