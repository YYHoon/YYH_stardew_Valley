#pragma once
#include "gameNode.h"
#include "tileNode.h"


class tileMap : public gameNode
{
private:
	tagTile	_tiles[TILEX * TILEY];
	//굳이 비트필드를 사용하기 때문에 호환성으로
	//더블워드로 선언함.
	DWORD _attribute[TILEX * TILEY];

	int _pos[2];

public:
	tileMap();
	~tileMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	tagTile* getTile() { return _tiles; }
	int getTileCenterX(int i) { return ((_tiles[0].rc.left + _tiles[0].rc.right) * 0.5) * i; }
	int getTileCenterY(int i) { return ((_tiles[0].rc.top + _tiles[0].rc.bottom) * 0.5) * i; }
	//2. 속성에 대한 접근자도 필요하다
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

