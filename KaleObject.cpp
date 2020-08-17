#include "stdafx.h"
#include "KaleObject.h"

void KaleObject::Init()
{
	IMAGEMANAGER->addFrameImage("kaleObject", "image/plants/KaleFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	_name = "kaleObject";
	_img = IMAGEMANAGER->findImage("kaleObject");
	_size = Vector2(_img->getFrameWidth(), _img->getFrameHeight());
	_position = Vector2(0, 0);
	_rect.centerSet(_position.x, _position.y, _size.x, _size.y);
	_active = true;
	_isCanHarvest = false;
	_isWet = false;
	_growCount = 0;
}

void KaleObject::Release()
{
}

void KaleObject::Update()
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
	default:
		break;
	}
	if (_img->getFrameX() >= 4)_isCanHarvest = true;
	ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _img, _position.x, _position.y, _img->getFrameX(), _img->getFrameY(), _rc.bottom);
}
