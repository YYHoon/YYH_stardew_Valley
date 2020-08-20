#include "stdafx.h"
#include "MapCave.h"

HRESULT MapCave::init()
{
	_vertical = _horizon = 50;
	_tiles = _map->Load("Cave.map", _vertical, _horizon);
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	_player->SetPosition(Vector2(100,500));

	_pm = new PlantsManager;
	/////////////////////////////////
	//_pm->SetPlantsList( _pm->Load()); < -- 이건 악마새끼인게 틀림없음
	//////////////////////////////////
	_pm->Init();
	_pm->SetMapMemoryAddressLinked(this);
	_count = 0;

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);

	return S_OK;
}

void MapCave::release()
{
}

void MapCave::update()
{
	if (_player->GetIsPrev())
	{
		SCENEMANAGER->changeScene("FARM");
	}
	_count++;
	_player->update();
	_pm->Update();
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
	_player->render();
}
