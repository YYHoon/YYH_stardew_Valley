#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"
#include <iostream>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;



class playGround : public gameNode
{
private:
	
	

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imginit();
	void soundinit();
};

