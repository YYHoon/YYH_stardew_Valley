#include "stdafx.h"
#include "MapHome.h"

HRESULT MapHome::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();

	_count = 0;
	_vertical = _horizon = 30;

	_player->GetPlayerInver()->setPlayer(_player);
	_tiles = _map->Load("mapHome.map", _vertical, _horizon);	

	for (int i = 0; i < _tiles.size(); i++)
	{
		if (_tiles[i].pos == POS::BED)
		{
			_player->SetPosition(Vector2(_tiles[i].rc.left, _tiles[i].rc.bottom));
		}
		if (_tiles[i].pos == POS::HOME_TO_PARM)
		{
			_player->SetPosition(Vector2(_tiles[i].rc.left + 32, _tiles[i].rc.top - 100));
		}
	}

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
	return S_OK;
}

void MapHome::release()
{
	_player->SavePlayerInfo("playerSave");
}

void MapHome::update()
{

	if (_player->GetIsNext())
	{
		SCENEMANAGER->changeScene("FARM");
	}

	_count++;
	_player->update();
	CAMERAMANAGER->setX(_player->GetInfo().position.x);
	CAMERAMANAGER->setY(_player->GetInfo().position.y);
	ENVIRONMENT->update();
}

void MapHome::render()
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

			if ((_tiles[index].terrainframeX == 1) && (_tiles[index].terrainframeY == 1))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Terrain_InDoor"),
					_tiles[index].rc.left, _tiles[index].rc.top,
					2, 7, _tiles[index].rc.bottom + 64);
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

			if (_tiles[index].object == MAPOBJECT::BED)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Bed"),
					_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 2 + 32,
					_tiles[index].objectframeX, _tiles[index].objectframeY);
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Blanket"),
					_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 2 + 32,
					_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom + 64);
			}
		}
	}
	ZORDER->ZOrderRender();
	_player->render();
	ENVIRONMENT->render(getMemDC());
}
