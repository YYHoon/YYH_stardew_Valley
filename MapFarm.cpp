#include "stdafx.h"
#include "MapFarm.h"

HRESULT MapFarm::init()
{
	_vertical = _horizon = 50;
	_tiles = _map->Load("mapFarm.map", _horizon, _vertical);
	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	_player->LoadPlayerInfo("playerSave");
	

	_pm = new PlantsManager;
    /////////////////////////////////
	_pm->SetPlantsList( _pm->Load());
	//////////////////////////////////
	_pm->Init();
	_pm->SetMapMemoryAddressLinked(this);
	
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);
	_count = 0;
	return S_OK;
}

void MapFarm::release()
{
	_map->Save("mapFarm.map", _horizon, _vertical,_tiles);
	_pm->Save();
}

void MapFarm::update()
{

	if (_tiles[_player->GetPlayerOnTileIndex()].pos == POS::PARM_TO_HOME)
	{
		_player->SetPosition(Vector2(670, 848));
		_player->SavePlayerInfo("playerSave");
		SCENEMANAGER->changeScene("HOME");
	}
	if (_tiles[_player->GetPlayerOnTileIndex()].pos == POS::PARM_TO_CAVE)
	{
		_player->SetPosition(Vector2(1054, 900));
		_player->SavePlayerInfo("playerSave");
		SCENEMANAGER->changeScene("CAVE");
	}

	_count++;
	_player->update();
	_pm->Update();
	if (ENVIRONMENT->GetIsDayIncrease())
	{
		for (int i = 0; i < _tiles.size(); i++)
		{
			_tiles[i].wet = false;
		}

	}
	CAMERAMANAGER->setX(_player->GetInfo().position.x);
	CAMERAMANAGER->setY(_player->GetInfo().position.y);
	ENVIRONMENT->update();
	EFFECTMANAGER->update();
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
				if (_tiles[index].hp > 2)
				{
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
						_tiles[index].rc.left - TILESIZE, _tiles[index].rc.top - TILESIZE * 5,
						_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom);
				}
				else
				{
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Stump"),
						_tiles[index].rc.left, _tiles[index].rc.top-20,
						_tiles[index].objectframeX, _tiles[index].objectframeY, _tiles[index].rc.bottom);
				}
			}
			if (_tiles[index].object == MAPOBJECT::ROCK ||
				_tiles[index].object == MAPOBJECT::WEED ||
				_tiles[index].object == MAPOBJECT::BRANCH ||
				_tiles[index].object == MAPOBJECT::HOETILE ||
				_tiles[index].object == MAPOBJECT::HOETILE_WET)
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
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;
			int index = (i + cullY) * 50 + (j + cullX);

			_tiles[index].autoIndex = 0;
			_tiles[index].autoIndex_2 = 0;

			if (_tiles[index].object == MAPOBJECT::HOETILE)
			{
				/////////////////  좌
				if (_tiles[index].rc.left / TILESIZE > 0)
				{
					if (_tiles[index - 1].object == MAPOBJECT::HOETILE)
					{
						_tiles[index].autoIndex += 8;
					}
				}
				/////////////////  우
				if (_tiles[index].rc.left / TILESIZE < 50 - 1)
				{
					if (_tiles[index + 1].object == MAPOBJECT::HOETILE)
					{
						_tiles[index].autoIndex += 2;
					}
				}
				/////////////////  위
				if (_tiles[index].rc.top / TILESIZE > 0)
				{
					if (_tiles[index - _vertical].object == MAPOBJECT::HOETILE)
					{
						_tiles[index].autoIndex += 1;
					}
				}
				/////////////////  아래
				if (_tiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_tiles[index + _vertical].object == MAPOBJECT::HOETILE)
					{
						_tiles[index].autoIndex += 4;
					}
				}

				switch (_tiles[index].autoIndex)
				{
				case 0:
					_tiles[index].objectframeX = 0;
					_tiles[index].objectframeY = 0;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
				case 15:
					_tiles[index].objectframeX = 5;
					_tiles[index].objectframeY = 3;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////아래
				case 1:
					_tiles[index].objectframeX = 4;
					_tiles[index].objectframeY = 0;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////위
				case 4:
					_tiles[index].objectframeX = 3;
					_tiles[index].objectframeY = 0;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////오른
				case 2:
					_tiles[index].objectframeX = 1;
					_tiles[index].objectframeY = 0;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////왼
				case 8:
					_tiles[index].objectframeX = 2;
					_tiles[index].objectframeY = 0;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////

					////////////////////세로
				case 5:
					_tiles[index].objectframeX = 4;
					_tiles[index].objectframeY = 2;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////가로
				case 10:
					_tiles[index].objectframeX = 3;
					_tiles[index].objectframeY = 2;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;

					/////////////////////////////////////////////////////////////////

					////////////////////// ㄱ 0,1
				case 6:
					_tiles[index].objectframeX = 0;
					_tiles[index].objectframeY = 1;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,1
				case 12:
					_tiles[index].objectframeX = 1;
					_tiles[index].objectframeY = 1;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 0,2
				case 3:
					_tiles[index].objectframeX = 0;
					_tiles[index].objectframeY = 2;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,2
				case 9:
					_tiles[index].objectframeX = 1;
					_tiles[index].objectframeY = 2;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////////////

					///////////////////////가로 위쪽
				case 14:
					_tiles[index].objectframeX = 2;
					_tiles[index].objectframeY = 1;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////가로 아래쪽
				case 11:
					_tiles[index].objectframeX = 2;
					_tiles[index].objectframeY = 2;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 오른쪽
				case 7:
					_tiles[index].objectframeX = 3;
					_tiles[index].objectframeY = 1;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 왼쪽
				case 13:
					_tiles[index].objectframeX = 4;
					_tiles[index].objectframeY = 1;
					_tiles[index].object = MAPOBJECT::HOETILE;
					break;
				}
			}
			if (_tiles[index].wet)
			{
				/////////////////  좌
				if (_tiles[index].rc.left / TILESIZE > 0)
				{
					if (_tiles[index - 1].wet)
					{
						_tiles[index].autoIndex_2 += 8;
					}
				}
				/////////////////  우
				if (_tiles[index].rc.left / TILESIZE < _vertical - 1)
				{
					if (_tiles[index + 1].wet)
					{
						_tiles[index].autoIndex_2 += 2;
					}
				}
				/////////////////  위
				if (_tiles[index].rc.top / TILESIZE > 0)
				{
					if (_tiles[index - _vertical].wet)
					{
						_tiles[index].autoIndex_2 += 1;
					}
				}
				/////////////////  아래
				if (_tiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_tiles[index + _vertical].wet)
					{
						_tiles[index].autoIndex_2 += 4;
					}
				}

				switch (_tiles[index].autoIndex_2)
				{
				case 0:
					_tiles[index].wetframeX = 0;
					_tiles[index].wetframeY = 3;
					break;
				case 15:
					_tiles[index].wetframeX = 5;
					_tiles[index].wetframeY = 4;
					break;
					///////////////////아래
				case 1:
					_tiles[index].wetframeX = 4;
					_tiles[index].wetframeY = 3;
					break;
					////////////////////위
				case 4:
					_tiles[index].wetframeX = 3;
					_tiles[index].wetframeY = 3;
					break;
					////////////////////오른
				case 2:
					_tiles[index].wetframeX = 1;
					_tiles[index].wetframeY = 3;
					break;
					////////////////////왼
				case 8:
					_tiles[index].wetframeX = 2;
					_tiles[index].wetframeY = 3;
					break;

					//////////////////////////////////////////////////////////////

					////////////////////세로
				case 5:
					_tiles[index].wetframeX = 4;
					_tiles[index].wetframeY = 5;
					break;
					////////////////////가로
				case 10:
					_tiles[index].wetframeX = 3;
					_tiles[index].wetframeY = 5;
					break;

					/////////////////////////////////////////////////////////////////

					////////////////////// ㄱ 0,1
				case 6:
					_tiles[index].wetframeX = 0;
					_tiles[index].wetframeY = 4;
					break;
					////////////////////// ㄱ 1,1
				case 12:
					_tiles[index].wetframeX = 1;
					_tiles[index].wetframeY = 4;
					break;
					////////////////////// ㄱ 0,2
				case 3:
					_tiles[index].wetframeX = 0;
					_tiles[index].wetframeY = 5;
					break;
					////////////////////// ㄱ 1,2
				case 9:
					_tiles[index].wetframeX = 1;
					_tiles[index].wetframeY = 5;
					break;

					//////////////////////////////////////////////////////////////////////

					///////////////////////가로 위쪽
				case 14:
					_tiles[index].wetframeX = 2;
					_tiles[index].wetframeY = 4;
					break;
					///////////////////////가로 아래쪽
				case 11:
					_tiles[index].wetframeX = 2;
					_tiles[index].wetframeY = 5;
					break;
					///////////////////////세로 오른쪽
				case 7:
					_tiles[index].wetframeX = 3;
					_tiles[index].wetframeY = 4;
					break;
					///////////////////////세로 왼쪽
				case 13:
					_tiles[index].wetframeX = 4;
					_tiles[index].wetframeY = 4;
					break;
				}
			}
		}
	}
	ZORDER->ZOrderRender();
	EFFECTMANAGER->render();
	ENVIRONMENT->render(getMemDC());
	_player->render();
}
