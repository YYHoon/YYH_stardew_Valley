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
	RECT rcCollision;	//������ �浹������ ��Ʈ
	int tileIndex[2];	//�̵����⿡ ���� Ÿ�ϼӼ� �������(Ÿ�� �ε����� �� ������)
	int tileX, tileY;	//���� ��ũ�� ��� Ÿ�Ͽ� �ִ��� ��ǥ ���� (left, top)
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

	//3. �������� ó�� �ؾ��� ���� �浹�� ��Ʈ�� ��¦ �������մϴ�
	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 2, _image->getFrameHeight() - 2);
	//4. ���� �� �� Ÿ�Ͽ� �ִ��� Ÿ�� �ε��� ����� �� ������մϴ�.
	tileX = ((rcCollision.left + rcCollision.right) * 0.5f) / TILESIZE;
	tileY = ((rcCollision.top + rcCollision.bottom) * 0.5f) / TILESIZE;
	_tileIndex.x = tileX;
	_tileIndex.y = tileY;
	totalTile = tileX + (tileY * 20);
	//5. ���� ��� �Ͻÿ�.
	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		tileIndex[0] = totalTile - 1;
		//ex) tileIndex[0] = �� �� Ÿ��
		//ex) tileIndex[1] = �� �� Ÿ���� �� Ÿ��
		break;
	case TANKDIRECTION_UP:
		tileIndex[0] = totalTile - 20;
		//ex) tileIndex[0] = �� �� Ÿ��
		//ex) tileIndex[1] = �� �� Ÿ���� �� Ÿ��
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = totalTile + 1;
		//ex) tileIndex[0] = �� �� Ÿ��
		//ex) tileIndex[1] = �� �� Ÿ���� �� Ÿ��
		break;
	case TANKDIRECTION_DOWN:
		tileIndex[0] = totalTile + 20;
		//ex) tileIndex[0] = �� �� Ÿ��
		//ex) tileIndex[1] = �� �� Ÿ���� �� Ÿ��
		break;

	}
	tileIndex[1] = totalTile;


	//6. ���� ������ ����ó���Ѵ�.
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
