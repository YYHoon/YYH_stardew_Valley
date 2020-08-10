#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

HRESULT TestScene::init()
{
	_Mouse = IMAGEMANAGER->findImage("mouse");

	_StoreWindow = IMAGEMANAGER->findImage("StoreWindow");
	_StorePortrait = IMAGEMANAGER->findImage("StoreOwnerPortrait");
	_StoreItem = IMAGEMANAGER->findImage("StoreItme");
	_StoreInfo = IMAGEMANAGER->findImage("StoreInfo");
	_StoreNPC = IMAGEMANAGER->findImage("StoreOwnerDot");
	_CloseButton = IMAGEMANAGER->findImage("CloseButton");

	_CloseRc = RectMake(1400, 30, _CloseButton->getWidth(), _CloseButton->getHeight());

	_StoreNpcRect = RectMake(WINSIZEX / 2, WINSIZEY / 2 - 100, _StoreNPC->getFrameWidth(), _StoreNPC->getFrameHeight());
	_StoreNpcOpen = RectMakeCenter(_StoreNpcRect.left + 25, _StoreNpcRect.top + 50, 200, 200);

	for(int i=0; i < 20; i++)
	{
		_StoreItemRc[i] = RectMake(378, 68, 1041, 104);
	}
	_StoreOpen = false; //상점열었누~


	//다이얼로그 실험하는 용도인거
	_ChatWindow = IMAGEMANAGER->findImage("ChatWindow");
	_TalkingXBox = IMAGEMANAGER->findImage("RightButton");
	_TalkingNpcImage = IMAGEMANAGER->findImage("말랑카우");
	_TalkingNpcPortrait = IMAGEMANAGER->findImage("와츄고너두");

	_BlackWindow = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");

	_TestP = RectMake(WINSIZEX / 2, WINSIZEY / 2, 50, 100); //The미

	_mouseIndex = _StoreItmeFrameY = 0;

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	_mouseIndex = 0;
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_StoreOpen && !_Toking)
	{
		_TestP.top -= 3;
		_TestP.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_StoreOpen && !_Toking)
	{
		_TestP.top += 3;
		_TestP.bottom += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_StoreOpen && !_Toking)
	{
		_TestP.left -= 3;
		_TestP.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_StoreOpen && !_Toking)
	{
		_TestP.left += 3;
		_TestP.right += 3;
	}

	RECT temp;
	if (IntersectRect(&temp, &_TestP, &_StoreNpcOpen) && !_StoreOpen)
	{
		if (PtInRect(&_StoreNpcRect, _ptMouse))
		{
			_mouseIndex = 2;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _StoreOpen = true;
		}
	}

	if (PtInRect(&_CloseRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _StoreOpen = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
	{
		_StoreOpen = false;
		_Toking = false;
	}

	//if (PtInRect(&_StoreItemRc, _ptMouse)) _StoreItmeFrameY = 1; //상점의 아이템칸!
	//else _StoreItmeFrameY = 0; 포문돌리는걸로 만들어야됨~


}

void TestScene::render()
{
	SetBkMode(getMemDC(), 1);

	Rectangle(getMemDC(), _StoreNpcOpen);
	Rectangle(getMemDC(), _TestP);
	_StoreNPC->frameRender(getMemDC(), _StoreNpcRect.left, _StoreNpcRect.top,0,0);
	HFONT font1, oldFont1;
	
	font1 = CreateFont(20, 0, 0, 0, 300, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("HY견고딕"));
		oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	if (_StoreOpen)
	{
		_BlackWindow->alphaRender(getMemDC(), 0, 0, 200);
		_StoreWindow->render(getMemDC(), 350, 50);
		_StorePortrait->frameRender(getMemDC(), 140, 50, 0, 0);
		_StoreInfo->render(getMemDC(), 100, 260);
		_CloseButton->render(getMemDC(), _CloseRc.left, _CloseRc.top);

		RECT rcText = RectMake(110, 270, 230, 200);
		DrawText(getMemDC(), TEXT("어서와, 일단은 상점이야 물건은없지만!"), 44, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	}
		DeleteObject(oldFont1);

	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseIndex, 0);
}