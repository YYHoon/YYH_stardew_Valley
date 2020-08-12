#include "stdafx.h"
#include "DummyMap.h"
#include "Player.h"

HRESULT DummyMap::init()
{
	tagTile saveTile[10001];
	HANDLE file;
	DWORD read;

	file = CreateFile("map.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(tagTile) * 10000, &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < 10000; i++)
	{
		map.push_back(saveTile[i]);
	}

	return S_OK;
}
//Point _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT()
	//_player->SetMapMemoryAddressLink(this);



void DummyMap::update()
{
	for (int i = 0; i < map.size(); i++)
		if (PtInRect(&map[i].rc, _ptMouse))
		{
			//cout << (int)map[i].terrain << endl;
			//cout << (int)map[i].object << endl;
		}
}

void DummyMap::render()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (i < map.size() && j < map.size())
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * 100 + (j + cullX);
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					map[index].rc.left, map[index].rc.top,
					map[index].terrainframeX, map[index].terrainframeY);
			}
		}
	}
	for (int i = 0; i < map.size(); ++i)
	{
		if (map[i].object == MAPOBJECT::NONE)continue;

		int cullyX = map[i].rc.left / TILESIZE;
		int cullyY = map[i].rc.top / TILESIZE;

		if (map[i].object != MAPOBJECT::BUILDING)
		{
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"), map[i].rc.left - TILESIZE, map[i].rc.top - TILESIZE * 5, map[i].objectframeX, map[i].objectframeY, map[i].rc.bottom);
		}
	}
	ZORDER->ZOrderRender();

}

tagTile DummyMap::GetTiles(int index)
{
	return _load->GetTile()[index];
}

int DummyMap::GetVertical()
{
	return _load->GetVertical();
}

int DummyMap::GetHorizon()
{
	return _load->GetHorizontal();
}

