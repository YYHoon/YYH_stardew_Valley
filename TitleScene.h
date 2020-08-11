#pragma once
#include "gameNode.h"
#include "AllDefine.h"
#include "AllEnum.h"

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

	image* _Brid;
	image* _Brid2;
	image* _Brid3;

	animation* _BridAni;
	RECT _BridRc;
	RECT _BridRc2;
	RECT _BridRc3;

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