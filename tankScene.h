#pragma once
#include "gameNode.h"
#include "tank.h"
#include "tileMap.h"


class tankScene : public gameNode
{
private:
	tileMap* _tankMap;
	tank* _tank;


public:
	tankScene();
	~tankScene();

	HRESULT init();
	void release();
	void update();
	void render();

	tank* GetPlayer() { return _tank; }
};

