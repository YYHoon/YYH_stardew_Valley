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
	vector<tagTile> test;
public:
	HRESULT init();
	void update();
	void render();

	tagTile GetTiles(int index);
	void SetMapObject(int tileIndex, MAPOBJECT obj);//0812�߰����Լ�
	int GetVertical();
	int GetHorizon();
	MapToolScene* GetTiles() { return _tiles; }

};

