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

	_StartButtonRc = RectMake(420, 600, _StartButton->getFrameWidth(), _StartButton->getFrameHeight());
	_LoadButtonRC = RectMake(643, 600, _LoadButton->getFrameWidth(), _LoadButton->getFrameHeight());
	_MaptoolButtonRc = RectMake(866, 600, _MaptoolButton->getFrameWidth(), _MaptoolButton->getFrameHeight());
	_ExitButtonRc = RectMake(1086, 600, _ExitButton->getFrameWidth(), _ExitButton->getFrameHeight());

	_Brid = IMAGEMANAGER->findImage("TitleBrid");
	_BridRc = RectMake(1600, 500, _Brid->getFrameWidth(), _Brid->getFrameHeight());

	_Brid2 = IMAGEMANAGER->findImage("TitleBrid");
	_BridRc2 = RectMake(1650, 200, _Brid2->getFrameWidth(), _Brid2->getFrameHeight());

	_Brid3 = IMAGEMANAGER->findImage("TitleBrid");
	_BridRc3 = RectMake(1700, 650, _Brid3->getFrameWidth(), _Brid3->getFrameHeight());

	int bridArrAni[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("aBrid", "TitleBrid", bridArrAni, 4, 10, true);
	_BridAni = KEYANIMANAGER->findAnimation("aBrid");
	_BridAni->start();


	_startButtonIndex = _exitButtonIndex = _mouseIndex = _LoadButtonIndex = 0;

	ShowCursor(false);
	_Mouse = IMAGEMANAGER->findImage("mouse");
	return S_OK;
}

void TitleScene::release()
{
	//SAFE_DELETE(_TitleBackGround); SAFE_DELETE(_Title);  
	//SAFE_DELETE(_StartButton);     SAFE_DELETE(_ExitButton);
	//SAFE_DELETE(_LoadButton);		 SAFE_DELETE(_MaptoolButton);
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

	_BridRc.left -= 5;
	_BridRc.right -= 5;
	_BridRc2.left -= 5;
	_BridRc2.right -= 5;
	_BridRc3.left -= 5;
	_BridRc3.right -= 5;

	if (_BridRc.right < 0)
	{
		_BridRc = RectMake(1600, RND->getInt(600) + 200, _Brid->getFrameWidth(), _Brid->getFrameHeight());
	}
	if (_BridRc2.right < 0)
	{
		_BridRc2 = RectMake(1650, RND->getInt(600) + 200, _Brid2->getFrameWidth(), _Brid2->getFrameHeight());
	}
	if (_BridRc3.right < 0)
	{		
		_BridRc3 = RectMake(1700, RND->getInt(600) + 200, _Brid3->getFrameWidth(), _Brid3->getFrameHeight());
	}

	KEYANIMANAGER->update();
}

void TitleScene::render()
{
	_TitleBackGround->render(getMemDC(), 0, 0);

	_Brid->aniRender(getMemDC(), _BridRc.left, _BridRc.top,_BridAni);
	_Brid2->aniRender(getMemDC(), _BridRc2.left, _BridRc2.top, _BridAni);
	_Brid3->aniRender(getMemDC(), _BridRc3.left, _BridRc3.top, _BridAni);

	_Title->render(getMemDC(), 500, 107);

	_StartButton->frameRender(getMemDC(), _StartButtonRc.left, _StartButtonRc.top,0, _startButtonIndex);
	_LoadButton->frameRender(getMemDC(), _LoadButtonRC.left, _LoadButtonRC.top, 0, _LoadButtonIndex);
	_MaptoolButton->frameRender(getMemDC(), _MaptoolButtonRc.left, _MaptoolButtonRc.top,0,_MaptoolButtonIndex);
	_ExitButton->frameRender(getMemDC(), _ExitButtonRc.left, _ExitButtonRc.top,0, _exitButtonIndex);

	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseIndex, 0);
}