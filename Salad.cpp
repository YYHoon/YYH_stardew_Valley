#include "stdafx.h"
#include "Salad.h"

void Salad::Init()
{
	_name = "Salad";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("Salad");
	_imageC = IMAGEMANAGER->findImage("Salad");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void Salad::Action()
{
	if (_number > 0)
	{

	}
}

void Salad::ReAction()
{
}
