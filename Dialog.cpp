#include "stdafx.h"
#include "Dialog.h"

HRESULT Dialog::init()
{
	_infoBox = IMAGEMANAGER->findImage("ItemInfoWindow");
	_stringClear = false;

    return S_OK;
}

void Dialog::release()
{
}

void Dialog::update(string itemName)
{
	//---------------파일넣는부분-----------------//
	ifstream readFlie;
	readFlie.open("Dialogue/ItemInfo(Kor).txt");

	if (readFlie.is_open())
	{
		while (!readFlie.eof())
		{
			string str;
			int findName;

			getline(readFlie, str);
			string setString(str.substr(0, str.length()));

			_vInfoTxtInPut.push_back(setString);
		}
	}
	readFlie.close();

	//----------------------------탐색-----------------------------//

	if (_stringClear)
	{
		if (itemName == "Axe")
		{
			if (_stringNum < _vInfoTxtInPut[0].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[0].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[0].length();
			}
		}

		if (itemName == "Pickax")
		{
			if (_stringNum < _vInfoTxtInPut[1].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[1].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[1].length();
			}
		}

		if (itemName == "FishingRod")
		{
			if (_stringNum < _vInfoTxtInPut[2].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[2].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[2].length();
			}
		}

		if (itemName == "Homi")
		{
			if (_stringNum < _vInfoTxtInPut[3].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[3].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[3].length();
			}
		}

		if (itemName == "WaterSpray")
		{
			if (_stringNum < _vInfoTxtInPut[4].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[4].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[4].length();
			}
		}

		if (itemName == "Sickle")
		{
			if (_stringNum < _vInfoTxtInPut[5].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[5].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[5].length();
			}
		}

		if (itemName == "Sword")
		{
			if (_stringNum < _vInfoTxtInPut[6].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[6].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[6].length();
			}
		}

		if (itemName == "Pasnip")
		{
			if (_stringNum < _vInfoTxtInPut[7].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[7].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[7].length();
			}
		}

		if (itemName == "Potato")
		{
			if (_stringNum < _vInfoTxtInPut[8].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[8].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[8].length();
			}
		}

		if (itemName == "Kale")
		{
			if (_stringNum < _vInfoTxtInPut[9].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[9].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[9].length();
			}
		}

		if (itemName == "NormalFish")
		{
			if (_stringNum < _vInfoTxtInPut[10].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[10].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[10].length();
			}
		}

		if (itemName == "RareFish")
		{
			if (_stringNum < _vInfoTxtInPut[11].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[11].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[11].length();
			}
		}

		if (itemName == "Sap")
		{
			if (_stringNum < _vInfoTxtInPut[12].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[12].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[12].length();
			}
		}

		if (itemName == "PasnipSeed")
		{
			if (_stringNum < _vInfoTxtInPut[13].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[13].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[13].length();
			}
		}

		if (itemName == "PotatoSeed")
		{
			if (_stringNum < _vInfoTxtInPut[14].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[14].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[14].length();
			}
		}

		if (itemName == "KaleSeed")
		{
			if (_stringNum < _vInfoTxtInPut[15].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[15].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[15].length();
			}
		}

		if (itemName == "Rock")
		{
			if (_stringNum < _vInfoTxtInPut[16].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[16].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[16].length();
			}
		}

		if (itemName == "Weed")
		{
			if (_stringNum < _vInfoTxtInPut[17].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[17].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[17].length();
			}
		}

		if (itemName == "Wood")
		{
			if (_stringNum < _vInfoTxtInPut[18].length())
			{
				_infoTxtOutPut.push_back(_vInfoTxtInPut[18].at(_stringNum++));
			}
			else
			{
				_stringNum = _vInfoTxtInPut[18].length();
			}
		}
	}
	else
	{
		_stringNum = 0;
		_infoTxtOutPut.clear();
	}
	
}


void Dialog::render()
{
	SetTextColor(getMemDC(), BLACK);
	HFONT TalkingOnlyFont, OldFont2;

	TalkingOnlyFont = CreateFont(27, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldFont2 = (HFONT)SelectObject(getMemDC(), TalkingOnlyFont);

	if (_stringClear)
	{
		_TxtBoxRC = RectMake(_ptMouse.x + 5, _ptMouse.y + 15, 180, 130);
		_infoBox->render(getMemDC(), _TxtBoxRC.left - 5, _TxtBoxRC.top - 15);
		DrawText(getMemDC(), TEXT(_infoTxtOutPut.c_str()), _stringNum, &_TxtBoxRC, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	}

	SelectObject(getMemDC(), OldFont2);
	DeleteObject(OldFont2);
}