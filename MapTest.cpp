#include "stdafx.h"
#include "MapTest.h"

HRESULT MapTest::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	
	_environment = new Environment;
	_environment->init();
	_count = 0;
	_vertical = _horizon = 75;
	_tiles = _map->Load("mapTest.map", _horizon, _vertical);

	_astar = new astar;
	_astar->SetMapMemoryLink(this);
	_astar->SetMap();
	_astar->SetStartNode(Vector2(10, 10));
	//_astar->SetEndNode(_player->GetInfo().position / TILESIZE);
	_astar->SetEndNode(Vector2(15,5));
	_astar->PathFind();
	
    return S_OK;
}

void MapTest::release()
{
}

void MapTest::update()
{
	_count++;
	_player->update();
	_environment->update();
}

void MapTest::render()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _vertical + (j + cullX);

			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
				_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainframeX, _tiles[index].terrainframeY);

			if (_count % 20 == 0)
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

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
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
			if ((_tiles[index].object == MAPOBJECT::TREE1) ||
				(_tiles[index].object == MAPOBJECT::TREE2) ||
				(_tiles[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 5,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom + 1);
			}

			if (j > 14 || i > 14) continue;

			if ((_tiles[index].object == MAPOBJECT::HOETILE) ||
				(_tiles[index].object == MAPOBJECT::HOETILE_WET) ||
				(_tiles[index].object == MAPOBJECT::WEED) ||
				(_tiles[index].object == MAPOBJECT::BRANCH) ||
				(_tiles[index].object == MAPOBJECT::ROCK))
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
		}
	}
	
	OBJECTMANAGER->Render();
	ZORDER->ZOrderRender();
	_environment->render();
	_player->render();
	_astar->render();
}
