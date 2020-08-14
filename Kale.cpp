#include "stdafx.h"
#include "Kale.h"

void Kale::Init()
{
	_name = "Kale";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("Kale(64x64)");
	_imageC = IMAGEMANAGER->findImage("Kale");
	_number = 0;
}

void Kale::Action()
{
	if (_number > 0)
	{

		_number--;
	}
}

void Kale::ReAction()
{
}
