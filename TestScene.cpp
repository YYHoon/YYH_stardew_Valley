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


	_store = new Store;
	_store->init();


	_Bar = new HpStaminaBar;
	_Bar->init();

	_Mouse = IMAGEMANAGER->findImage("mouse");

	/// <summary>
	_Inv = new Inventory;
	_Inv->init();

	_env = new Environment;
	_env->init();

	_CloseButton = IMAGEMANAGER->findImage("CloseButton");
	_CloseRc = RectMake(1400, 30, _CloseButton->getWidth(), _CloseButton->getHeight());

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

	_mouseIndex = 0;

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
	_store->update();
	_Bar->update();


	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_StoreOpen && !_Talking)
	{
		_TestP.top -= 5;
		_TestP.bottom -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_StoreOpen && !_Talking)
	{
		_TestP.top += 5;
		_TestP.bottom += 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_StoreOpen && !_Talking)
	{
		_TestP.left -= 5;
		_TestP.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_StoreOpen && !_Talking)
	{
		_TestP.left += 5;
		_TestP.right += 5;
	}



	if(KEYMANAGER->isOnceKeyDown(VK_F1))
	{ 
		_Bar->setPlayerHP(-5);
		_Bar->setPlayerStamina(-5);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_Bar->setPlayerHP(+5);
		_Bar->setPlayerStamina(+5);
	}


	RECT temp;
	if (IntersectRect(&temp, &_TestP, &_store->getStoreNpcOpen()) && !_StoreOpen)
	{
		if (PtInRect(&_store->getStoreNpcRect(), _ptMouse))
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

	_store->render();
	Rectangle(getMemDC(), _TalkingNpc);
	Rectangle(getMemDC(), _TalkingNpcImageRc);

	Rectangle(getMemDC(), _TestP);
	_TalkingNpcImage->frameRender(getMemDC(), _TalkingNpcImageRc.left, _TalkingNpcImageRc.top, 0, 0);

	/// <summary>
	_env->render();
	_inv->render();
	/// </summary>

	_Bar->staminaBarRender();
	_Bar->hpBarRender();

	if (_StoreOpen && !_Talking)
	{
		_BlackWindow->alphaRender(getMemDC(), 0, 0, 200);
		_store->OpenStoreRender();
		_CloseButton->render(getMemDC(), _CloseRc.left, _CloseRc.top);
	}
	
//---------------------다이얼로그_연습-------yo---------------------------------

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
	SelectObject(getMemDC(), OldFont2);
	DeleteObject(OldFont2);

	_Inv->render();
	//좌표값보기용~
	/*char mo[200];
	char mo2[200];
	sprintf_s(mo, "마우스의 X좌표:%d", _ptMouse.x);
	sprintf_s(mo2, "마우스의 Y좌표:%d", _ptMouse.y);
	TextOut(getMemDC(), 50, 90, mo, strlen(mo));
	TextOut(getMemDC(), 50, 120, mo2, strlen(mo2));*/

//------------------------------------------------------------------------------


	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mouseIndex, 0);
}