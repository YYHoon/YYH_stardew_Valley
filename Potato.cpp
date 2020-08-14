#include "stdafx.h"
#include "Potato.h"

void Potato::Init()
{
	_name = "Potato";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("Potato(64x64)");
	_imageC = IMAGEMANAGER->findImage("Potato");
	_number = 0;

}

void Potato::Action()
{
	if (_number > 0)
	{

	}
}

void Potato::ReAction()
{
}
