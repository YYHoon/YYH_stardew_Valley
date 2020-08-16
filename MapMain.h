#pragma once
#include "gameNode.h"
#include "MapToolScene.h"
#include "Player.h"
#include "Environment.h"
#include "Store.h"

class MapMain : public gameNode
{
protected:
	MapToolScene* _map;
	Player* _player;
	Environment* _environment;
	Store* _store;

	SynInheritance(vector<tagTile>, _tiles, Tiles)
	SynInheritance(int, _vertical, Vertical)
	SynInheritance(int, _horizon, Horizon)
	SynInheritance(int, _count, Count)

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual tagTile GetTiles(int index) { return _tiles[index]; };
	virtual void SetTiles(int index, tagTile tile) { _tiles[index] = tile; }
	virtual void SetMapObject(int index, MAPOBJECT object) { _tiles[index].object = object; }
	virtual void SetColl(int index, bool Coll) { _tiles[index].collision = Coll; }
	virtual void SetPlayerAdressLink(Player* player) { _player = player; }
	virtual int GetMapSize() { return _tiles.size(); }
};

