#include "stdafx.h"
#include "Sword.h"

void Sword::Init()
{
	_name = "Sword";
	_tag = "ToolItem";
	_dmage = 3;
	_enumName = TOOLS::SWORD;
	/// <summary>
	_image = IMAGEMANAGER->findImage("Item_Knife");
	/// </summary>
}

void Sword::Action()
{
}

void Sword::ReAction()
{
}
