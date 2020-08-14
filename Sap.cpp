#include "stdafx.h"
#include "Sap.h"

void Sap::Init()
{
	_name = "Sap";
	_tag = "EatItem";
	_imageI = IMAGEMANAGER->findImage("Sap(64x64)");
	_imageC = IMAGEMANAGER->findImage("Sap");
	_number = 0;
	_enumName = TOOLS::EATITEM;
}

void Sap::Action()
{
	if (_number > 0)
	{

		_number--;
	}

}

void Sap::ReAction()
{
}
