#include "stdafx.h"
#include "GrilledFish.h"

void GrilledFish::Init()
{
	_name = "GrilledFish";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("GrilledFish");
	_imageC = IMAGEMANAGER->findImage("GrilledFish");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void GrilledFish::Action()
{
	if (_number > 0)
	{

	}
}

void GrilledFish::ReAction()
{
}
