#include"stdafx.h"
#include "Pickax.h"
//#include"tank.h"

Pickax::Pickax()
{

	_name = "Pickax";
	_tag = "ToolItem";
	_dmage = 1;

}

void Pickax::Action()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		Vector2 mouse(_ptMouse);
		mouse = mouse / TILESIZE;
		cout << mouse.x << endl;
		cout << mouse.y << endl;
	}
}
