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
	sprintf_s(mo, "���콺�� X��ǥ:%d", _ptMouse.x);
	sprintf_s(mo2, "���콺�� Y��ǥ:%d", _ptMouse.y);
	TextOut(getMemDC(), 50, 90, mo, strlen(mo));
	TextOut(getMemDC(), 50, 120, mo2, strlen(mo2));
}
