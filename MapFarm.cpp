#include "stdafx.h"
#include "MapFarm.h"

HRESULT MapFarm::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();

	_count = 0;
	_vertical = _horizon = 100;
	_tiles = _map->Load("map.map", _vertical, _horizon);
	return S_OK;
}

void MapFarm::release()
{
}

void MapFarm::update()
{
	_count++;
	_player->update();
}

void MapFarm::render()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
				_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainframeX, _tiles[index].terrainframeY);

		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);

			if (_count % 20 == 0)
			{
				if ((_tiles[index].terrainframeX == 6 || _tiles[index].terrainframeX == 5) && _tiles[index].terrainframeY == 2)
				{
					if (_tiles[index].terrainframeX > 5)_tiles[index].terrainframeX = 4;
					_tiles[index].terrainframeX++;
				}

				if (_tiles[index].terrain == TERRAIN::WATER)
				{
					if (_tiles[index].terrainframeX == 3)_tiles[index].terrainframeX = -1;
					_tiles[index].terrainframeX++;
				}


			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			if (_tiles[index].object == MAPOBJECT::NONE)continue;
			if (_tiles[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			if (_tiles[index].object == MAPOBJECT::NONE)continue;

			if ((_tiles[index].object == MAPOBJECT::HOETILE) ||
				(_tiles[index].object == MAPOBJECT::WEED) ||
				(_tiles[index].object == MAPOBJECT::BRANCH) ||
				(_tiles[index].object == MAPOBJECT::ROCK))
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
			}

		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			if (_tiles[index].object == MAPOBJECT::NONE)continue;

			if (_tiles[index].object == MAPOBJECT::HOETILE_WET)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].wetframeX, _tiles[index].wetframeY);
			}
		}
	}
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			if (_tiles[index].object == MAPOBJECT::NONE)continue;
			if (_tiles[index].object == MAPOBJECT::BUILDING)
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"),
					_tiles[index].rc.left - TILESIZE * 8, _tiles[index].rc.top - TILESIZE * 8,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom);
			}
		}
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);
			if (_tiles[index].object == MAPOBJECT::NONE)continue;

			if ((_tiles[index].object == MAPOBJECT::TREE1) ||
				(_tiles[index].object == MAPOBJECT::TREE2) ||
				(_tiles[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 5,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom + 1);
			}

		}
	}
	ZORDER->ZOrderRender();
	_player->render();
}
