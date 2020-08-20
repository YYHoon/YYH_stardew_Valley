#include "stdafx.h"
#include "MapCave.h"

HRESULT MapCave::init()
{
	_vertical = _horizon = 50;
	_tiles = _map->Load("mapCave.map", _vertical, _horizon);
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();	
	_player->SetPosition(Vector2(800, 500));


	_player->SetMapName("CAVE");

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);
	_count = 0;
	return S_OK;
}

void MapCave::release()
{
	_player->SavePlayerInfo("playerSave");
	_map->Save("mapCave.map", _horizon, _vertical, _tiles);
}

void MapCave::update()
{
	if (_tiles[_player->GetPlayerOnTileIndex()].pos == POS::CAVE_TO_PARM)
	{
		SCENEMANAGER->changeScene("FARM");
	}
	_count++;
	_player->update();
	CAMERAMANAGER->setX(_player->GetInfo().position.x);
	CAMERAMANAGER->setY(_player->GetInfo().position.y);
	ENVIRONMENT->update();
}

void MapCave::render()
{
	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizon + (j + cullX);

			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain_InDoor"),
				_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainframeX, _tiles[index].terrainframeY);

			if (_tiles[index].object == MAPOBJECT::NONE)continue;
			if (_tiles[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall_Cave"),
					_tiles[index].rc.left, _tiles[index].rc.top - TILESIZE * 4,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
			}
		}
	}


	ZORDER->ZOrderRender();
	ENVIRONMENT->render(getMemDC());
	_player->render();
}
