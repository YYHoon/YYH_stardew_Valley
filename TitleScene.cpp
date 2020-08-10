#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

HRESULT TitleScene::init()
{
	_TitleBackGround = IMAGEMANAGER->findImage("TitleBackground"); 
					   
	_Title = IMAGEMANAGER->findImage("Title");
	_StartButton = IMAGEMANAGER->findImage("StartButton"); 
	_LoadButton = IMAGEMANAGER->findImage("LoadButton");
	_MaptoolButton = IMAGEMANAGER->findImage("MaptoolButton");
	_ExitButton = IMAGEMANAGER->findImage("ExitButton");


	_StartButtonRc = RectMake(520, 600, _StartButton->getFrameWidth(), _StartButton->getFrameHeight());
	_LoadButtonRC = RectMake(743, 600, _LoadButton->getFrameWidth(), _LoadButton->getFrameHeight());
	_MaptoolButtonRc = RectMake(1266, 600, _MaptoolButton->getFrameWidth(), _MaptoolButton->getFrameHeight());
	_ExitButtonRc = RectMake(966, 600, _ExitButton->getFrameWidth(), _ExitButton->getFrameHeight());


	ShowCursor(false);
	_Mouse = IMAGEMANAGER->findImage("mouse");

	_startButtonIndex = _exitButtonIndex = _mouseIndex = _LoadButtonIndex = 0;
	return S_OK;
}

void TitleScene::release()
{
	//SAFE_DELETE(_TitleBackGround); SAFE_DELETE(_Title);  
	//SAFE_DELETE(_StartButton);     SAFE_DELETE(_ExitButton);
	//SAFE_DELETE(_LoadButton); 
}

void TitleScene::update()
{
	if (PtInRect(&_StartButtonRc, _ptMouse))
	{
		_startButtonIndex = 1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("테스트");
		}
	}
	else
	{
		_startButtonIndex = 0;
	}

	if (PtInRect(&_LoadButtonRC, _ptMouse))
	{
		_LoadButtonIndex = 1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//이어하기로화면전환!
		}
	}
	else
	{
		_LoadButtonIndex = 0;
	}

	if (PtInRect(&_ExitButtonRc, _ptMouse))
	{
		_exitButtonIndex = 1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}
	else
	{
		_exitButtonIndex = 0;
	}

	if (PtInRect(&_MaptoolButtonRc, _ptMouse))
	{
		_MaptoolButtonIndex = 1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("맵툴");
		}
	}
	else
	{
		_MaptoolButtonIndex = 0;
	}
}

void TitleScene::render()
{
	_TitleBackGround->render(getMemDC(), 0, 0);
	_Title->render(getMemDC(), 500, 107);

	_StartButton->frameRender(getMemDC(), _StartButtonRc.left, _StartButtonRc.top,0, _startButtonIndex);
	_LoadButton->frameRender(getMemDC(), _LoadButtonRC.left, _LoadButtonRC.top, 0, _LoadButtonIndex);
	_MaptoolButton->frameRender(getMemDC(), _MaptoolButtonRc.left, _MaptoolButtonRc.top,0,_MaptoolButtonIndex);
	_ExitButton->frameRender(getMemDC(), _ExitButtonRc.left, _ExitButtonRc.top,0, _exitButtonIndex);


	//char mo[200];
	//char mo2[200];
	//sprintf_s(mo, "마우스의 X좌표:%d", _ptMouse.x);
	//sprintf_s(mo2, "마우스의 Y좌표:%d", _ptMouse.y);
	//TextOut(getMemDC(), 50, 90, mo, strlen(mo));
	//TextOut(getMemDC(), 50, 120, mo2, strlen(mo2));

	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseIndex, 0);
}