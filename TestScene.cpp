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
}
