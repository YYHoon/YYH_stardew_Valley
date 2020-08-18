#include "stdafx.h"
#include "TileRender.h"

HRESULT TileRender::init()
{
	return S_OK;
}

void TileRender::release()
{
}

void TileRender::update(int horizontal, int vertical, INOUT inout, vector<tagTile> tile)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * horizontal + (j + cullX);

			if (tile[index].object == MAPOBJECT::HOETILE)
			{
				/////////////////  좌
				if (tile[index].rc.left / TILESIZE > 0)
				{
					if (tile[index - 1].object == MAPOBJECT::HOETILE)
					{
						tile[index].autoIndex += 8;
					}
				}
				/////////////////  우
				if (tile[index].rc.left / TILESIZE < vertical - 1)
				{
					if (tile[index + 1].object == MAPOBJECT::HOETILE)
					{
						tile[index].autoIndex += 2;
					}
				}
				/////////////////  위
				if (tile[index].rc.top / TILESIZE > 0)
				{
					if (tile[index - vertical].object == MAPOBJECT::HOETILE)
					{
						tile[index].autoIndex += 1;
					}
				}
				/////////////////  아래
				if (tile[index].rc.top / TILESIZE < vertical - 1)
				{
					if (tile[index + vertical].object == MAPOBJECT::HOETILE)
					{
						tile[index].autoIndex += 4;
					}
				}

				switch (tile[index].autoIndex)
				{
				case 0:
					tile[index].objectframeX = 0;
					tile[index].objectframeY = 0;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
				case 15:
					tile[index].objectframeX = 5;
					tile[index].objectframeY = 3;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////아래
				case 1:
					tile[index].objectframeX = 4;
					tile[index].objectframeY = 0;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////위
				case 4:
					tile[index].objectframeX = 3;
					tile[index].objectframeY = 0;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////오른
				case 2:
					tile[index].objectframeX = 1;
					tile[index].objectframeY = 0;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////왼
				case 8:
					tile[index].objectframeX = 2;
					tile[index].objectframeY = 0;
					tile[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////

					////////////////////세로
				case 5:
					tile[index].objectframeX = 4;
					tile[index].objectframeY = 2;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////가로
				case 10:
					tile[index].objectframeX = 3;
					tile[index].objectframeY = 2;
					tile[index].object = MAPOBJECT::HOETILE;
					break;

					/////////////////////////////////////////////////////////////////

					////////////////////// ㄱ 0,1
				case 6:
					tile[index].objectframeX = 0;
					tile[index].objectframeY = 1;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,1
				case 12:
					tile[index].objectframeX = 1;
					tile[index].objectframeY = 1;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 0,2
				case 3:
					tile[index].objectframeX = 0;
					tile[index].objectframeY = 2;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,2
				case 9:
					tile[index].objectframeX = 1;
					tile[index].objectframeY = 2;
					tile[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////////////

					///////////////////////가로 위쪽
				case 14:
					tile[index].objectframeX = 2;
					tile[index].objectframeY = 1;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////가로 아래쪽
				case 11:
					tile[index].objectframeX = 2;
					tile[index].objectframeY = 2;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 오른쪽
				case 7:
					tile[index].objectframeX = 3;
					tile[index].objectframeY = 1;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 왼쪽
				case 13:
					tile[index].objectframeX = 4;
					tile[index].objectframeY = 1;
					tile[index].object = MAPOBJECT::HOETILE;
					break;
				}
			}
		}
	}

}

void TileRender::render(int horizontal,int vertical,INOUT inout, vector<tagTile> tile)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;
	
			int index = (i + cullY) * horizontal + (j + cullX);
	
			if (inout == INOUT::OUTDOOR)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					tile[index].rc.left, tile[index].rc.top,
					tile[index].terrainframeX, tile[index].terrainframeY);
			}
			else
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain_InDoor"),
					tile[index].rc.left, tile[index].rc.top,
					tile[index].terrainframeX, tile[index].terrainframeY);
			}
			//if (_count % 20 == 0)
			{
				if (inout == INOUT::OUTDOOR)
				{
					if ((tile[index].terrainframeX == 6 || tile[index].terrainframeX == 5) && tile[index].terrainframeY == 2 &&
						tile[index].terrain == TERRAIN::GRASS)
					{
						if (tile[index].terrainframeX > 5)tile[index].terrainframeX = 4;
						tile[index].terrainframeX++;
					}
					if (tile[index].terrain == TERRAIN::WATER)
					{
						if (tile[index].terrainframeX == 3)tile[index].terrainframeX = -1;
						tile[index].terrainframeX++;
					}
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

			int index = (i + cullY) * horizontal + (j + cullX);
			if (tile[index].object == MAPOBJECT::NONE)continue;

			if (tile[index].object == MAPOBJECT::BUILDING)
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"),
					tile[index].rc.left - TILESIZE * 8, tile[index].rc.top - TILESIZE * 8,
					tile[index].objectframeX, tile[index].objectframeY, tile[index].rc.bottom - 128);
			}
			if ((tile[index].object == MAPOBJECT::TREE1) ||
				(tile[index].object == MAPOBJECT::TREE2) ||
				(tile[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					tile[index].rc.left - TILESIZE, tile[index].rc.top - TILESIZE * 5,
					tile[index].objectframeX, tile[index].objectframeY, tile[index].rc.bottom);
			}
			if (tile[index].object == MAPOBJECT::HOETILE ||
				tile[index].object == MAPOBJECT::WEED ||
				tile[index].object == MAPOBJECT::ROCK||
				tile[index].object == MAPOBJECT::BRANCH)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					tile[index].rc.left, tile[index].rc.top,
					tile[index].objectframeX, tile[index].objectframeY);
			}
			if (tile[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall"),
					tile[index].rc.left, tile[index].rc.top,
					tile[index].objectframeX, tile[index].objectframeY);
			}
			if (tile[index].wet)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					tile[index].rc.left, tile[index].rc.top,
					0, 3);
			}
		}
	}
}

void TileRender::AutoHoe(int horizontal, int vertical, INOUT inout, vector<tagTile> tile)
{
	
}
