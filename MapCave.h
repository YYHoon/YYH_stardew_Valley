#pragma once
#include "MapMain.h"
#include "AllEnemy.h"
class MapCave : public MapMain
{
private:
	Slime* _slime;
	Slime* _slime1;
	image* _mouse;
	int _mouseFrame;

	int idx;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

