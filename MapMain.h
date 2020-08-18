#pragma once
#include "gameNode.h"
#include "MapToolScene.h"
#include "Player.h"
#include "Environment.h"
#include "Store.h"
#include "PlantsManager.h"

class MapMain : public gameNode
{
protected:
	TileRender* _tileRender;
	MapToolScene* _map;
	Player* _player;
	Environment* _environment;
	Store* _store;
	PlantsManager* _pm;

	SynInheritance(vector<tagTile>, _tiles, Tiles)
	SynInheritance(int, _vertical, Vertical)
	SynInheritance(int, _horizon, Horizon)
	SynInheritance(int, _count, Count)

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual PlantsManager* GetPM() { return _pm; }
	virtual Environment* GetEnvironMent() { return _environment; }
	virtual tagTile GetTiles(int index) { return _tiles[index]; };
	virtual void SetTiles(int index, tagTile tile) { _tiles[index] = tile; }
	virtual void SetMapObject(int index, MAPOBJECT object) { _tiles[index].object = object; }
	virtual void SetColl(int index, bool Coll) { _tiles[index].collision = Coll; }
	virtual void SetWet(int index, bool Coll) { _tiles[index].wet = Coll; }
	virtual void SetPlayerAdressLink(Player* player) { _player = player; }
	virtual int GetMapSize() { return _tiles.size(); }
};

