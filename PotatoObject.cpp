#include "stdafx.h"
#include "PotatoObject.h"

void PotatoObject::Init()
{
	IMAGEMANAGER->addFrameImage("potatoObject", "image/plants/PotatoFrame.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
	_name = "potatoObject";
	_img = IMAGEMANAGER->findImage("potatoObject");
	_size = Vector2(_img->getFrameWidth(), _img->getFrameHeight());
	_position = Vector2(0, 0);
	_rect.centerSet(_position.x, _position.y, _size.x, _size.y);
	_active = true;
	_isCanHarvest = false;
	_isWet = false;
	_growCount = 0;
}

void PotatoObject::Release()
{
}

void PotatoObject::Update()
{
	
	switch (_growCount)
	{
	case 0:
		_img->setFrameX(0);
		_img->setFrameY(0);
		break;
	case 1:
		_img->setFrameX(1);
		_img->setFrameY(0);
		break;
	case 2:
		_img->setFrameX(2);
		_img->setFrameY(0);
		break;
	case 3:
		_img->setFrameX(3);
		_img->setFrameY(0);
		break;
	case 4:
		_img->setFrameX(4);
		_img->setFrameY(0);
		break;
	case 5:
		_img->setFrameX(5);
		_img->setFrameY(0);
	default:
		break;
	}
	if (_img->getFrameX() >= 5)_isCanHarvest = true;
	ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _img, _position.x, _position.y, _img->getFrameX(), _img->getFrameY(), _rc.bottom);
}
