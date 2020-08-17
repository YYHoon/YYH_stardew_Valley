#pragma once
#include "MapMain.h"

class MapFarm : public MapMain
{
private:
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

