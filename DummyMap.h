#pragma once
#include "gameNode.h"
#include "MapToolScene.h"

class Player;

class DummyMap : public gameNode
{
private:
	MapToolScene* _tiles;
	Player* _player;

	image* _mouseImg;

public:
	HRESULT init();
	void update();
	void render();

	tagTile GetTiles(int index);
	int GetVertical();
	int GetHorizon();
};

