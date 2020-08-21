#pragma once
#include "MapMain.h"
#include "AllEnemy.h"
class MapCave : public MapMain
{
private:
	Slime* _slime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

