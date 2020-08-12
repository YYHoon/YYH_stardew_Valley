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
	_inv = new Inventory;
	_inv->init();

	_Mouse = IMAGEMANAGER->findImage("mouse");

	_StoreWindow = IMAGEMANAGER->findImage("StoreWindow");
	_StorePortrait = IMAGEMANAGER->findImage("StoreOwnerPortrait");

	for (int i = 0; i < 4; i++)
	{
		_StoreItem[i] = IMAGEMANAGER->findImage("StoreItme");
	}

	/// <summary>
	_Inv = new Inventory;
	_Inv->init();

	_env = new Environment;
	_env->init();
	/// </summary>
	_StoreInfo = IMAGEMANAGER->findImage("StoreInfo");
	_StoreNPC = IMAGEMANAGER->findImage("StoreOwnerDot");
	_CloseButton = IMAGEMANAGER->findImage("CloseButton");

	_CloseRc = RectMake(1400, 30, _CloseButton->getWidth(), _CloseButton->getHeight());

	_StoreNpcRect = RectMake(WINSIZEX / 2, WINSIZEY / 2 - 100, _StoreNPC->getFrameWidth(), _StoreNPC->getFrameHeight());
	_StoreNpcOpen = RectMakeCenter(_StoreNpcRect.left + 25, _StoreNpcRect.top + 50, 200, 200);

	for (int i = 0; i < 20; i++) 
	{
		_Item.push_back(RectMake(378, 68 + i * 104, 1041, 104));
	}
	_StoreOpen = false; //상점열었누~


//-------------------------다이얼로그 실험하는 용도인거--------------------
	_ChatWindow = IMAGEMANAGER->findImage("ChatBox");
	_TalkingXBox = IMAGEMANAGER->findImage("RightButton");
	_TalkingNpcImage = IMAGEMANAGER->findImage("말랑카우");
	_TalkingNpcPortrait = IMAGEMANAGER->findImage("초상화");

	_TalkingNpcImageRc = RectMake(300, 500, _TalkingNpcImage->getFrameWidth(), _TalkingNpcImage->getFrameHeight());
	_TalkingNpc = RectMakeCenter(_TalkingNpcImageRc.left + 25, _TalkingNpcImageRc.top + 25, 200, 200);

	_BlackWindow = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");

	_TestP = RectMake(WINSIZEX / 2, WINSIZEY / 2, 50, 100); //더미

	_mouseIndex = _StoreItmeFrameY = 0;

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	_inv->update();
	_mouseIndex = 0;
	/// <summary>
	_Inv->update();
	_env->update();
	/// </summary>

	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_StoreOpen && !_Talking)
	{
		_TestP.top -= 3;
		_TestP.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_StoreOpen && !_Talking)
	{
		_TestP.top += 3;
		_TestP.bottom += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_StoreOpen && !_Talking)
	{
		_TestP.left -= 3;
		_TestP.right -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_StoreOpen && !_Talking)
	{
		_TestP.left += 3;
		_TestP.right += 3;
	}


	RECT temp;
	if (IntersectRect(&temp, &_TestP, &_StoreNpcOpen) && !_StoreOpen)
	{
		if (PtInRect(&_StoreNpcRect, _ptMouse))
		{
			_mouseIndex = 1;
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
		_Talking = false;
	}

//-------------------------------------------------------------------
	_StoreItmeFrameY = 0;
	_StoreItmeFrameY2 = 0;
	_StoreItmeFrameY3 = 0;
	_StoreItmeFrameY4 = 0;

	if (PtInRect(&_Item[0], _ptMouse)) _StoreItmeFrameY = 1;
	if (PtInRect(&_Item[1], _ptMouse)) _StoreItmeFrameY2 = 1;
	if (PtInRect(&_Item[2], _ptMouse)) _StoreItmeFrameY3 = 1;
	if (PtInRect(&_Item[3], _ptMouse)) _StoreItmeFrameY4 = 1;
//-------------------------------------------------------------------	

	if (IntersectRect(&temp, &_TestP, &_TalkingNpc) && !_Talking)
	{
		if (PtInRect(&_TalkingNpcImageRc, _ptMouse))
		{
			_mouseIndex = 2;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _Talking = true;
		}
	}

///////////////////////파일입출력이용_다이얼로그_기본틀?////////////////////////
	ifstream readFlie;
	readFlie.open("Dialogue/TEST.txt");

	if (readFlie.is_open())
	{
		while (!readFlie.eof())
		{
			string str;
			int findChar;

			getline(readFlie, str);
			findChar = str.find('@', 0);

			string outString(str.substr(findChar + 1, str.length()));

			_txtInTest.push_back(outString);
		}
	}
	readFlie.close();

	if (_Talking)
	{
		if (_stringNum < _txtInTest.front().length())
		{
			if (_txtInTest.front().at(_stringNum) < 0)
			{
				for (int i = 0; i < 2; i++)
				{
					_txtOutTest.push_back(_txtInTest.front().at(_stringNum++));
				}
			}
			else
			{
				_txtOutTest.push_back(_txtInTest.front().at(_stringNum++));
			}
		}
		else
		{
			_stringNum = _txtInTest.front().length();
		}
	}
	else
	{
		_stringNum = 0;
		_txtOutTest.clear();
	}
///////////////////////////////////////////////////////////////////////////

}

void TestScene::render()
{
	SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), BLACK);

	Rectangle(getMemDC(), _StoreNpcOpen);
	Rectangle(getMemDC(), _TalkingNpc);
	Rectangle(getMemDC(), _TalkingNpcImageRc);

	Rectangle(getMemDC(), _TestP);
	_StoreNPC->frameRender(getMemDC(), _StoreNpcRect.left, _StoreNpcRect.top,0,0);
	_TalkingNpcImage->frameRender(getMemDC(), _TalkingNpcImageRc.left, _TalkingNpcImageRc.top, 0, 0);


	/// <summary>
	_env->render();
	_inv->render();
	/// </summary>



	HFONT font1, oldFont1;
	font1 = CreateFont(40, 0, 0, 0, 300, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("Sandoll 미생"));
		oldFont1 = (HFONT)SelectObject(getMemDC(), font1);
	if (_StoreOpen && !_Talking)
	{
		_BlackWindow->alphaRender(getMemDC(), 0, 0, 200);
		_StoreWindow->render(getMemDC(), 350, 50);
		_StorePortrait->frameRender(getMemDC(), 140, 50, 0, 0);
		_StoreInfo->render(getMemDC(), 100, 260);
		RECT rcText = RectMake(110, 270, 230, 200);
		DrawText(getMemDC(), TEXT("어서와, 여기는 상점이야 물건은없지만!"), 38, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
		Draw();
		_CloseButton->render(getMemDC(), _CloseRc.left, _CloseRc.top);
	}
		DeleteObject(oldFont1);
	
//---------------------다이얼로그_연습----------------------------------------

	HFONT TalkingOnlyFont, OldFont2;

	TalkingOnlyFont = CreateFont(50,0,0,0,300, false, false,false,  DEFAULT_CHARSET, OUT_STRING_PRECIS, 
					  CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldFont2 = (HFONT)SelectObject(getMemDC(), TalkingOnlyFont);

	if (_Talking && !_StoreOpen)
	{
		_TxtBoxRC = RectMake(427, 605, 500, 300);

		_ChatWindow->render(getMemDC(), 400, 580);
		_TalkingNpcPortrait->render(getMemDC(), 1010, 611);
		DrawText(getMemDC(), TEXT(_txtOutTest.c_str()), _stringNum, &_TxtBoxRC, DT_LEFT | DT_WORDBREAK | DT_VCENTER); //대사입출력한거
		TextOut(getMemDC(), 1035, 820, "대화시험소", strlen("대화시험소"));
	}

	DeleteObject(OldFont2);

//------------------------------------------------------------------------------


	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseIndex, 0);
}

void TestScene::Draw()
{	
	
	_StoreItem[0]->frameRender(getMemDC(), _Item[0].left, _Item[0].top, 0, _StoreItmeFrameY);
	_StoreItem[1]->frameRender(getMemDC(), _Item[1].left, _Item[1].top, 0, _StoreItmeFrameY2);
	_StoreItem[2]->frameRender(getMemDC(), _Item[2].left, _Item[2].top, 0, _StoreItmeFrameY3);
	_StoreItem[3]->frameRender(getMemDC(), _Item[3].left, _Item[3].top, 0, _StoreItmeFrameY4);

	/// <summary>
	_Inv->render();
	/// </summary>
}