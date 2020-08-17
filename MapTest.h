#pragma once
#include "MapMain.h"
#include "astar.h"
class MapTest : public MapMain
{
private:
	astar* _astar;
	Vector2 test;
	int count = 0;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

