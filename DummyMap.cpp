#include "stdafx.h"
#include "DummyMap.h"
#include "Player.h"

HRESULT DummyMap::init()
{
	_tiles = new MapToolScene;
	_tiles->init();
	_tiles->Load();

	_player = new Player;
	_player->init();
	//_player->SetMapMemoryAddressLink(this);

	return S_OK;
}

void DummyMap::update()
{
	_player->update();
}

void DummyMap::render()
{
	for (int i = 0; i < 50; ++i)
	{
		IMAGEMANAGER->findImage("Terrain")->frameRender(getMemDC(), _tiles->GetTile()[i].rc.left,
			_tiles->GetTile()[i].rc.top, _tiles->GetTile()[i].terrainframeX, _tiles->GetTile()[i].terrainframeY);
	}
	_player->render();
}

