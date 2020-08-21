#pragma once
#include "MapMain.h"
#include"IsSleep.h"
class MapHome : public MapMain
{
private:

	IsSleep* _sleep;
	bool _test;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

