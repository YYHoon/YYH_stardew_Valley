#include "stdafx.h"
#include "Wood.h"

void Wood::Init()
{
	_name = "Wood";
	_tag = "ResoureceItem";
	_imageI = IMAGEMANAGER->findImage("Wood(64x64)");
	_imageC = IMAGEMANAGER->findImage("Wood");
	_number = 0;
	_enumName = TOOLS::RESOURCEITEM;
}

void Wood::Action()
{
	if (_number > 0)
	{

		_number--;
	}

}

void Wood::ReAction()
{
}
