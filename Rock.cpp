#include "stdafx.h"
#include "Rock.h"

void Rock::Init()
{
	_name = "Rock";
	_tag = "ResoureceItem";
	_imageI = IMAGEMANAGER->findImage("Stone(64x64)");
	_imageC = IMAGEMANAGER->findImage("Stone");
	_number = 0;
	_enumName = TOOLS::RESOURCEITEM;
}

void Rock::Action()
{
}

void Rock::ReAction()
{
}
