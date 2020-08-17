#include "stdafx.h"
#include "Weed.h"

void Weed::Init()
{
	_name = "Weed";
	_tag = "ResoureceItem";
	_imageI = IMAGEMANAGER->findImage("Weed(64x64)");
	_imageC = IMAGEMANAGER->findImage("Weed");
	_number = 0;
	_enumName = TOOLS::RESOURCEITEM;
}

void Weed::Action()
{
	if (_number > 0)
	{

		_number--;
	}

}

void Weed::ReAction()
{
}
