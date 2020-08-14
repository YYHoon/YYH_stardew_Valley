#include "stdafx.h"
#include "Parsnip.h"

void Parsnip::Init()
{
	//Synthesize(string, _name, Name)
	//	Synthesize(string, _type, Type)
	//	Synthesize(Vector2, _position, Position)
	//	Synthesize(Vector2, _size, Size)
	//	Synthesize(TTYONE_UTIL::MYRECT, _rect, Rect)
	//	Synthesize(RECT, _rc, Rc)
	//	Synthesize(bool, _active, Active)
	IMAGEMANAGER->addFrameImage("Parsnip", "image/plants/ParsnipFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	_name = "Parsnip";
	_img = IMAGEMANAGER->findImage("Parsnip");
	_size = Vector2(_img->getFrameWidth(), _img->getFrameHeight());
	_position = Vector2(0, 0);
	_rect.centerSet(_position.x, _position.y, _size.x, _size.y);
	_active = true;
	_isCanHarvest = false;
	_isWet = false;
	_growCount = 0;
}

void Parsnip::Release()
{
}

void Parsnip::Update()
{
	if (_isWet)
	{
		_growCount++;
		_isWet = false;
	}
	switch (_growCount)
	{
	case 0:
		_img->setFrameX(0);
		_img->setFrameY(0);
		break;
	case 1:
		_img->setFrameX(1);
		_img->setFrameY(1);
		break;
	case 2:
		_img->setFrameX(2);
		_img->setFrameY(2);
		break;
	case 3:
		_img->setFrameX(3);
		_img->setFrameY(3);
		break;
	case 4:
		_img->setFrameX(4);
		_img->setFrameY(4);
		break;
	default:
		break;
	}
	ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _img, _position.x, _position.y, _img->getFrameX(), _img->getFrameY(), _rc.bottom);
}
