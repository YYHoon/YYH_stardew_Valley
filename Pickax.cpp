#include"stdafx.h"
#include "Pickax.h"

Pickax::Pickax()
{

}

void Pickax::Init()
{
	_name = "Pickax";
	_tag = "ToolItem";
	_dmage = 1;
	_impactIndex;
}

void Pickax::Action()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		Vector2 mouse(_ptMouse);
		mouse.x = mouse.x / TILESIZE;
		mouse.y = mouse.y / TILESIZE;
		cout << (int)mouse.x << endl;
		cout << (int)mouse.y << endl;
	}
}

void Pickax::ReAction()
{
}
