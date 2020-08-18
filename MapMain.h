#pragma once
#include "gameNode.h"
#include "MapToolScene.h"
#include "Player.h"
#include "Store.h"
#include "PlantsManager.h"

class MapMain : public gameNode
{
protected:
	TileRender* _tileRender;
	MapToolScene* _map;
	Player* _player;
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
	virtual tagTile GetTiles(int index) { return _tiles[index]; };
	virtual void SetTiles(int index, tagTile tile) { _tiles[index] = tile; }
	virtual void SetFrameX(int index, int frameX) { _tiles[index].objectframeX = frameX; }
	virtual void SetFrameY(int index, int frameY) { _tiles[index].objectframeY = frameY; }

	virtual void SetMapObject(int index, MAPOBJECT object) { _tiles[index].object = object; }
	virtual void SetColl(int index, bool Coll) { _tiles[index].collision = Coll; }
	virtual void SetWet(int index, bool Coll) { _tiles[index].wet = Coll; }
	virtual void SetHp(int index, int Hp) { _tiles[index].hp += Hp; }
	virtual void SetAutoIndex(int index, int Auto) { _tiles[index].autoIndex = Auto; }
	virtual void SetPlayerAdressLink(Player* player) { _player = player; }
	virtual int GetMapSize() { return _tiles.size(); }
};

