#include "stdafx.h"
#include "ScareCrowObject.h"

void ScareCrowObject::Init()
{
	_name = "ScareCrowObject";
	_img = IMAGEMANAGER->findImage("ScareCrow");
	_position = Vector2(0, 0);
	_rect.centerSet(_position.x, _position.y,TILESIZE,TILESIZE);
	_active = true;
}

void ScareCrowObject::Update()
{
}

void ScareCrowObject::Release()
{
}
