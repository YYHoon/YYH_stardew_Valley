#include "stdafx.h"
#include "MapCave.h"

HRESULT MapCave::init()
{
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);
	_vertical = _horizon = 50;
	_tiles = _map->Load("mapCave.map",_horizon, _vertical);
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();	
	_player->LoadPlayerInfo("playerSave");
	_store = new Store;
	_store->setLinkPlayer(_player);	//소지금 참조용
	_store->setLinkInventory(_player->GetPlayerInver()); //가방내용물 참고용 상점F5키입니다.
	_store->init(1025, 100);

	_player->GetPlayerInver()->SetStoreLink(_store);
	//_player->GetPlayerInver()->setPlayer(_player);
	_slime = new Slime;
	_slime->SetAddressLinkMap(this);
	_slime->Init();
	_slime->SetAddressLinkPlayer(_player);
	_slime->SetAstarStartNode(Vector2(800 / 64, 500 / 64));

	_mouse = IMAGEMANAGER->findImage("mouse");


	_count = 0;
	return S_OK;
}

void MapCave::release()
{
	_map->Save("mapCave.map", _horizon, _vertical, _tiles);
}

void MapCave::update()
{
	_mouseFrame = 0;

	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());
	if (_tiles[_player->GetPlayerOnTileIndex()].pos == POS::CAVE_TO_PARM)
	{
		_player->SetPosition(Vector2(2400, 680));
		_player->SavePlayerInfo("playerSave");
		_player->GetPlayerInver()->Save();
		SCENEMANAGER->changeScene("FARM");
	}

	if (isCollision(_store->getStoreNpcOpen(), _player->GetPlayercollision()))
	{
		if (PtInRect(&_store->getStoreNpcRect(), _CameraMouse))
		{
			_mouseFrame = 1;
			if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _store->setStoreOpen(true);
		}
	}
	
	ENVIRONMENT->update();
	_store->update();
	_player->update();

	_count++;
	if (_store->getStoreOpen())
	{
		_player->SetOpenStore(true);
	}
	else 
	{
		_player->SetOpenStore(false);
	}
	CAMERAMANAGER->setX(_player->GetInfo().position.x);
	CAMERAMANAGER->setY(_player->GetInfo().position.y);
	//_slime->Update();

	_slime->SetAstarEndNode(Vector2(_player->GetPlayerOnTileIndex() % _vertical,
		_player->GetPlayerOnTileIndex() / _vertical));
	
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

	
	_store->render();
	ZORDER->ZOrderRender();
	ENVIRONMENT->render(getMemDC());
	if (_store->getStoreOpen())
	{
		_store->OpenStoreRender();
	}
	_player->render();
	_slime->Render();
	_mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseFrame, 0);
}
