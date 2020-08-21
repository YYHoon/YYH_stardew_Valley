#include "stdafx.h"
#include "Slime.h"

void Slime::Init()
{
	_name = "Slime";
	_type = "ENEMY";
	_active = true;
	_size = Vector2(64, 64);
	_rect = { 0,0,64,64 };
	_hp = 50;
	_damage = 5;
	_speed = 5;
	_img = IMAGEMANAGER->findImage("SLIME");
	_astar = new astar;
	_astar->SetMapMemoryLink(_map);
	_astar->SetMap();
}

void Slime::Release()
{
}

void Slime::Update()
{
	if (count % 30 == 0) {
		_astar->PathFind();
	}
	count++;
	ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _img, 800, 500,0,0, _rect.bottom);
}

void Slime::Render()
{
	_astar->render();
}
