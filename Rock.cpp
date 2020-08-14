#include "stdafx.h"
#include "Rock.h"

void Rock::Init()
{
	_name = "Rock";
	_tag = "ResoureceItem";
	_imageI = IMAGEMANAGER->findImage("Rock(64x64)");
	_imageC = IMAGEMANAGER->findImage("Rock");
	_number = 0;
}

void Rock::Action()
{
}

void Rock::ReAction()
{
}
