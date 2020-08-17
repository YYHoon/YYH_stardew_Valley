#include "stdafx.h"
#include "MapTest.h"


HRESULT MapTest::init()
{
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	_tiles = _map->Load("mapTest.map", _vertical, _horizon);
	_player->SavePlayerInfo("Player.info");
	
	_environment = new Environment;
	_environment->init();
	
	_store = new Store;
	_store->setLinkPlayer(_player);	//소지금 참조용
	_store->setLinkInventory(_player->GetPlayerInver()); //가방내용물 참고용 상점F5키입니다.
	_store->init(400,400);

	_player->GetPlayerInver()->SetStoreLink(_store);
	_player->GetPlayerInver()->setPlayer(_player);

	_HpStaminaBar = new HpStaminaBar;
	_HpStaminaBar->setPlayerLink(_player);
	_HpStaminaBar->init();


	_pm = new PlantsManager;
	_pm->SetMapMemoryAddressLinked(this);
	_pm->Init();

	_count = 0;
    _vertical = _horizon = 75;
    
	

	//_pm->Planting(4, "parsnipObject");
	//_pm->Planting(3, "parsnipObject");
	//_pm->LoadSize();
	
	_vertical = _horizon = 75;
	_tiles = _map->Load("mapTest.map", _horizon, _vertical);

	//_astar = new astar;
	//_astar->SetMapMemoryLink(this);
	//_astar->SetMap();
	//_astar->SetStartNode(Vector2(10, 10));
	////_astar->SetEndNode(_player->GetInfo().position / TILESIZE);
	//test = Vector2(9,9);
	//_astar->SetEndNode(test);
	//_astar->PathFind();


	ShowCursor(true);

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
	/*if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		test += Vector2(-1, 0);
		_astar->SetEndNode(test);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		test += Vector2(1, 0);
		_astar->SetEndNode(test);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		test += Vector2(0,-1);
		_astar->SetEndNode(test);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		test += Vector2(0,1);
		_astar->SetEndNode(test);
	}
	if (_count % 20 == 0) {
		_astar->PathFind();
	}*/

	_store->update();
	_HpStaminaBar->update();
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
				_count = 0;
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
	_store->render();
	_environment->render();
	if (_store->getStoreOpen())
	{
		_store->OpenStoreRender();
	}
	_HpStaminaBar->staminaBarRender();
	_HpStaminaBar->hpBarRender();
	_player->render();
	//_astar->render();
}
