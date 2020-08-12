#include "stdafx.h"
#include "DummyMap.h"
#include "Player.h"

HRESULT DummyMap::init()
{
	_tiles = new MapToolScene;
	_tiles->init();
	_tiles->Load();

	_player = new Player;
	_player->SetMapMemoryAddressLink(this);
	_player->init();
	

	_mouseImg = IMAGEMANAGER->findImage("mouse");
	test = _tiles->GetTile();
	return S_OK;
}
//Point _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT()
	//_player->SetMapMemoryAddressLink(this);



void DummyMap::update()
{
	_player->update();
}

void DummyMap::render()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (i < test.size() && j < test.size())
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * 100 + (j + cullX);
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					test[index].rc.left, test[index].rc.top,
					test[index].terrainframeX, test[index].terrainframeY);
			}
		}
	}
	
	for (int i = 0; i < test.size(); ++i)
	{
		if (test[i].object == MAPOBJECT::NONE)continue;
	
		int cullyX = test[i].rc.left / TILESIZE;
		int cullyY = test[i].rc.top / TILESIZE;
	
		if (test[i].object != MAPOBJECT::BUILDING)
		{
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"), test[i].rc.left - TILESIZE, test[i].rc.top - TILESIZE * 5, test[i].objectframeX, test[i].objectframeY, test[i].rc.bottom);
		}
	}
	ZORDER->ZOrderRender();
	_player->render();
}

tagTile DummyMap::GetTiles(int index)
{
	return test[index];
}

void DummyMap::SetMapObject(int tileIndex, MAPOBJECT obj)
{
	test[tileIndex].object = obj;
}

int DummyMap::GetVertical()
{
	return _tiles->GetVertical();
}

int DummyMap::GetHorizon()
{
	return _tiles->GetHorizontal();
}
