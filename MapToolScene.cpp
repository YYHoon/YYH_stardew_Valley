#include "stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
}

MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init()
{
    _Mouse = IMAGEMANAGER->findImage("mouse");

    return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
}

void MapToolScene::render()
{
    _Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
    TextOut(getMemDC(), 50, 50, "¸ÊÅø", strlen("¸ÊÅø"));
}
