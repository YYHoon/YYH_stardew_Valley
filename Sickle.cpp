#include "stdafx.h"
#include "Sickle.h"

void Sickle::Init()
{
	_name = "Sickle";
	_tag = "name";
	_dmage = 1;
	_enumName = TOOLS::SICKLE;
	/// <summary>
	_image = IMAGEMANAGER->findImage("Item_Sickle");
	/// </summary>
}

void Sickle::Action()
{
	
}

void Sickle::ReAction()
{
}
