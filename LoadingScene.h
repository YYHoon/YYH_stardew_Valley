#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"

class progressBar;

class LoadingScene : public gameNode
{
private:
	progressBar* _LoadingBar;

	image* _BackGround;
	image* _Loading;

	int _x, _y;
	int _count;

public:
	LoadingScene();
	~LoadingScene();

	int _currentCount;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

static DWORD CALLBACK threadfunction(LPVOID lpParameter);