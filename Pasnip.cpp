#include "stdafx.h"
#include "Pasnip.h"

void Pasnip::Init()
{
	_name = "Pasnip";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("Pasnip(64x64)");
	_imageC = IMAGEMANAGER->findImage("Pasnip");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void Pasnip::Action()
{
	if (_number > 0)
	{

	}
}

void Pasnip::ReAction()
{
}
