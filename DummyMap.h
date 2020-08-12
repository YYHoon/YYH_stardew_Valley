#pragma once
#include "gameNode.h"
#include "MapToolScene.h"

class Player;

class DummyMap : public gameNode
{
private:
	Player* _player;
	image* _mouseImg;
	vector<tagTile> map;
	MapToolScene* _load;

public:
	HRESULT init();
	void update();
	void render();

	tagTile GetTiles(int index);
	int GetVertical();
	int GetHorizon();
	MapToolScene* GetTiles() { return _load; }

};

