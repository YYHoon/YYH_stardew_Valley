#pragma once
#include "gameNode.h"

class MapToolScene : public gameNode
{
private:
	image* _Mouse;


public:
	MapToolScene();
	~MapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};