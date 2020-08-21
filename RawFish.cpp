#include "stdafx.h"
#include "RawFish.h"

void RawFish::Init()
{
	_name = "RawFish";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("RawFish");
	_imageC = IMAGEMANAGER->findImage("RawFish");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void RawFish::Action()
{
	if (_number > 0)
	{

	}
}

void RawFish::ReAction()
{
}
