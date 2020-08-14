#include "stdafx.h"
#include "NormalFish.h"

void NormalFish::Init()
{
	_name = "NormalFish";
	_tag = "ActItem";
	_imageI = IMAGEMANAGER->findImage("NormalFish(64x64)");
	_imageC = IMAGEMANAGER->findImage("NormalFish");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void NormalFish::Action()
{
	if (_number > 0)
	{

		_number--;
	}

}

void NormalFish::ReAction()
{
}
