#include "stdafx.h"
#include "MapFarm.h"

HRESULT MapFarm::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	_player->SetPosition(Vector2(500, 500));

	_count = 0;
	_vertical = _horizon = 50;
	_tiles = _map->Load("mapFarm.map", _vertical, _horizon);

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);

	return S_OK;
}

void MapFarm::release()
{
}

void MapFarm::update()
{
	if (_player->GetIsNext())
	{
		SCENEMANAGER->changeScene("HOME");
	}
	_count++;
	_player->update();
	CAMERAMANAGER->setX(_player->GetInfo().position.x);
	CAMERAMANAGER->setY(_player->GetInfo().position.y);
}

void MapFarm::render()
{
	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizon + (j + cullX);

			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
				_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainframeX, _tiles[index].terrainframeY);

			if (_count % 40 == 0)
			{
				if ((_tiles[index].terrainframeX == 6 || _tiles[index].terrainframeX == 5) && _tiles[index].terrainframeY == 2 &&
					_tiles[index].terrain == TERRAIN::GRASS)
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

	for (int i = 0; i < ClIPPINGY + 8; i++)
	{
		for (int j = 0; j < ClIPPINGX + 9; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizon + (j + cullX);
			if (index > 50 * 50)continue;
			if (i > 0) index = index - 1;
			if (_tiles[index].object == MAPOBJECT::NONE)continue;

			if (_tiles[index].object == MAPOBJECT::BUILDING)
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"),
					_tiles[index].rc.left - TILESIZE * 8, _tiles[index].rc.top - TILESIZE * 8,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom - 128);
			}
			if ((_tiles[index].object == MAPOBJECT::TREE1) ||
				(_tiles[index].object == MAPOBJECT::TREE2) ||
				(_tiles[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 5,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom);
			}
			if (_tiles[index].object == MAPOBJECT::ROCK ||
				_tiles[index].object == MAPOBJECT::WEED ||
				_tiles[index].object == MAPOBJECT::BRANCH ||
				_tiles[index].object == MAPOBJECT::HOETILE)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
			}
			if (_tiles[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
			}
			if (_tiles[index].wet && _tiles[index].object == MAPOBJECT::HOETILE)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].wetframeX, _tiles[index].wetframeY);
			}
		}
	}
	ZORDER->ZOrderRender();
	_player->render();
}
