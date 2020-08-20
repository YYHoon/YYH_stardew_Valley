#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"

class Player;

class progressBar;

class LoadingScene : public gameNode
{
private:
	progressBar* _LoadingBar;
	Player* _player;
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