#pragma once
#include "MapMain.h"
class MapHome : public MapMain
{
private:

	bool _test;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

