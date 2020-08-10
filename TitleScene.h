#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"
#include "TestScene.h"

class TitleScene : public gameNode
{
private:

	image* _TitleBackGround;
	image* _Title;
	image* _StartButton;
	image* _LoadButton;
	image* _MaptoolButton;
	image* _ExitButton;


	RECT _StartButtonRc;
	RECT _LoadButtonRC;
	RECT _MaptoolButtonRc;
	RECT _ExitButtonRc;

	image* _Mouse;

	int _startButtonIndex;
	int _exitButtonIndex;
	int _MaptoolButtonIndex;
	int _LoadButtonIndex;
	int _mouseIndex;

public:
	TitleScene();
	~TitleScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};