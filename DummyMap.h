#pragma once
#include "gameNode.h"
#include "MapToolScene.h"

class Player;


class DummyMap : public gameNode
{
private:
	MapToolScene* _tiles;
	Player* _player;
	
public:
	HRESULT init();
	void update();
	void render();

	MapToolScene* GetTiles() { return _tiles; }

};

