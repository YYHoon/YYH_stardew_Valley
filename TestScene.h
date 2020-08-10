#pragma once
#include "gameNode.h"
class TestScene : public gameNode
{
private:
	image* _Mouse;


public:
	TestScene();
	~TestScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};