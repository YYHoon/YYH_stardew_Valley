#pragma once
#include "gameNode.h"
#include "MapToolScene.h"
class MapMain : public gameNode
{
protected:
	MapToolScene* _map;
	SynInheritance(vector<tagTile>, _tiles, Tiles)
	SynInheritance(int, _vertical, Vertical)
	SynInheritance(int, _horizon, Horizon)
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual tagTile GetTiles(int index) { return _tiles[index]; };
	virtual void SetTiles(int index, tagTile tile) { _tiles[index] = tile; }
	virtual int GetMapSize() { return _tiles.size(); }
};

