#include "stdafx.h"
#include "Dialog.h"

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

HRESULT Dialog::init()
{
    return S_OK;
}

void Dialog::release()
{
}

void Dialog::update(string itemName)
{
	ifstream readFlie;
	readFlie.open("Dialogue/ItemInfo.txt");

	if (readFlie.is_open())
	{
		while (!readFlie.eof())
		{
			string str;
			int findName;

			getline(readFlie, str);
			findName = str.find(itemName, 0);

			string setString(str.substr(findName, str.length()));
		}
	}
	readFlie.close();




}

void Dialog::render()
{
	HFONT TalkingOnlyFont, OldFont2;

	TalkingOnlyFont = CreateFont(50, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldFont2 = (HFONT)SelectObject(getMemDC(), TalkingOnlyFont);

	_TxtBoxRC = RectMake(427, 605, 500, 300);
	DrawText(getMemDC(), TEXT(_txtOutTest.c_str()), _stringNum, &_TxtBoxRC, DT_LEFT | DT_WORDBREAK | DT_VCENTER); //대사입출력한거

	SelectObject(getMemDC(), OldFont2);
	DeleteObject(OldFont2);
}
