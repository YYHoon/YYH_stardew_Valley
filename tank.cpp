#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init()
{

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));
	_speed = 100.0f;
	_direction = TANKDIRECTION_RIGHT;
	_image->setFrameX(0);
	_image->setFrameY(2);
	setTankPosition();
	return S_OK;
}

void tank::release()
{
}

void tank::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}
	

}

void tank::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankMove()
{
	RECT rcCollision;	//임의의 충돌판정용 렉트
	int tileIndex[2];	//이동방향에 따라 타일속성 검출계산용(타일 인덱스가 몇 번인지)
	int tileX, tileY;	//실제 탱크가 어디 타일에 있는지 좌표 계산용 (left, top)
	int totalTile;
	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;


	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		_image->setFrameX(0);
		_image->setFrameY(3);

		_x -= moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION_UP:
		_image->setFrameX(0);
		_image->setFrameY(0);

		_y -= moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION_RIGHT:
		_image->setFrameX(0);
		_image->setFrameY(2);

		_x += moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case TANKDIRECTION_DOWN:
		_image->setFrameX(0);
		_image->setFrameY(1);

		_y += moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

	}

	//3. 여러분이 처음 해야할 일은 충돌용 렉트를 살짝 깍아줘야합니다
	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 2, _image->getFrameHeight() - 2);
	//4. 내가 몇 번 타일에 있는지 타일 인덱스 계산을 또 해줘야합니다.
	tileX = ((rcCollision.left + rcCollision.right) * 0.5f) / TILESIZE;
	tileY = ((rcCollision.top + rcCollision.bottom) * 0.5f) / TILESIZE;
	_tileIndex.x = tileX;
	_tileIndex.y = tileY;
	totalTile = tileX + (tileY * 20);
	//5. 여길 계산 하시오.
	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		tileIndex[0] = totalTile - 1;
		//ex) tileIndex[0] = 내 앞 타일
		//ex) tileIndex[1] = 내 앞 타일의 옆 타일
		break;
	case TANKDIRECTION_UP:
		tileIndex[0] = totalTile - 20;
		//ex) tileIndex[0] = 내 앞 타일
		//ex) tileIndex[1] = 내 앞 타일의 옆 타일
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = totalTile + 1;
		//ex) tileIndex[0] = 내 앞 타일
		//ex) tileIndex[1] = 내 앞 타일의 옆 타일
		break;
	case TANKDIRECTION_DOWN:
		tileIndex[0] = totalTile + 20;
		//ex) tileIndex[0] = 내 앞 타일
		//ex) tileIndex[1] = 내 앞 타일의 옆 타일
		break;

	}
	tileIndex[1] = totalTile;


	//6. 갈지 못갈지 예외처리한다.
	if (_tileMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
	{
		int tileCenterX = ((_tileMap->getTile()[tileIndex[0]].rc.left + _tileMap->getTile()[tileIndex[0]].rc.right) * 0.5f);
		int tileCenterY = ((_tileMap->getTile()[tileIndex[0]].rc.top + _tileMap->getTile()[tileIndex[0]].rc.bottom) * 0.5f);


		switch (_direction)
		{
		case TANKDIRECTION_LEFT:
			rcCollision.left -= 16;
			if (tileCenterX >= rcCollision.left)
			{
				_speed = 0;
				_x += moveSpeed;
			}
			break;
		case TANKDIRECTION_UP:
			rcCollision.top -= 16;
			if (tileCenterY >= rcCollision.top)
			{
				_speed = 0;
				_y += moveSpeed;
			}
			break;
		case TANKDIRECTION_RIGHT:
			rcCollision.right += 16;
			if (tileCenterX <= rcCollision.right)
			{
				_speed = 0;
				_x -= moveSpeed;
			}
			break;
		case TANKDIRECTION_DOWN:
			rcCollision.bottom += 16;
			if (tileCenterY <= rcCollision.bottom)
			{
				_speed = 0;
				_y -= moveSpeed;
			}
			break;

		}
	}
	else _speed = 100.0f;

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_rc = rcCollision;
}

void tank::setTankPosition()
{
	_rc = _tileMap->getTile()[_tileMap->getPosFirst()].rc;

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.bottom + _rc.top) / 2;


}
