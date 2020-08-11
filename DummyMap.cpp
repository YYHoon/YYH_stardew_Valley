#include "stdafx.h"
#include "DummyMap.h"
#include "Player.h"

HRESULT DummyMap::init()
{
	_tiles = new MapToolScene;
	_tiles->init();
	_tiles->Load();

	_player = new Player;
	_player->init();
	_player->SetMapMemoryAddressLink(this);

	_mouseImg = IMAGEMANAGER->findImage("mouse");

	return S_OK;
}
//Point _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT()
void DummyMap::update()
{
	_player->update();
}

void DummyMap::render()
{
	for (int i = 0; i < _tiles->GetTile().size(); ++i)
	{
		IMAGEMANAGER->findImage("Terrain")->frameRender(getMemDC(), _tiles->GetTile()[i].rc.left,
			_tiles->GetTile()[i].rc.top, _tiles->GetTile()[i].terrainframeX, _tiles->GetTile()[i].terrainframeY);
	}
	_player->render();
	_mouseImg->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
}

tagTile DummyMap::GetTiles(int index)
{
	return _tiles->GetTile()[index];
}

int DummyMap::GetVertical()
{
	return _tiles->GetVertical();
}

int DummyMap::GetHorizon()
{
	return _tiles->GetHorizontal();
}

