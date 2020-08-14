#include "stdafx.h"
#include "RareFish.h"

void RareFish::Init()
{
	_name = "RareFish";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("RareFish(64x64)");
	_imageC = IMAGEMANAGER->findImage("RareFish");
	_number = 0;
}

void RareFish::Action()
{
	if (_number > 0)
	{

		_number--;
	}
}

void RareFish::ReAction()
{
}
