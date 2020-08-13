#include "stdafx.h"
#include "MapFarm.h"

HRESULT MapFarm::init()
{
	_tiles = _map->Load("map.map", 100, 100);


	return S_OK;
}

void MapFarm::release()
{
}

void MapFarm::update()
{
}

void MapFarm::render()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (i < _tiles.size() && j < _tiles.size())
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * 100 + (j + cullX);
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].terrainframeX, _tiles[index].terrainframeY);
			}
		}
	}

	for (int i = 0; i < _tiles.size(); ++i)
	{
		if (_tiles[i].object == MAPOBJECT::NONE)continue;

		int cullyX = _tiles[i].rc.left / TILESIZE;
		int cullyY = _tiles[i].rc.top / TILESIZE;

		if (_tiles[i].object != MAPOBJECT::BUILDING)
		{
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"), _tiles[i].rc.left - TILESIZE, _tiles[i].rc.top - TILESIZE * 5, _tiles[i].objectframeX, _tiles[i].objectframeY, _tiles[i].rc.bottom);
		}
	}
	ZORDER->ZOrderRender();
}
