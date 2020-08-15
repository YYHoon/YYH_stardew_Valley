#include "stdafx.h"
#include "MapHome.h"

HRESULT MapHome::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();

	_count = 0;
	_vertical = _horizon = 30;
	_tiles = _map->Load("mapHome.map", _horizon, _vertical);
	return S_OK;
}

void MapHome::release()
{
}

void MapHome::update()
{
	_count++;
	_player->update();
}

void MapHome::render()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);

			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain_InDoor"),
				_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainframeX, _tiles[index].terrainframeY);
		}
	}
	ZORDER->ZOrderRender();
	_player->render();
}
