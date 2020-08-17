#include "stdafx.h"
#include "MiniGame.h"


void MiniGame::Update()
{
	if(KEYMANAGER->isStayKeyDown(VK_UP))cout << (int)_fishingState << endl;
	
	if (_fishingState == FISHING::FIRST|| _fishingState == FISHING::CHARGE)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_fishingState = FISHING::CHARGE;
			_fishfloat = _playerCenter;
			_fishfloat.y -= 200;
			_chageFrontBox.right ++;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_power = _clickTime;
			_fishingState = FISHING::SHOT;
		}
	}
	//cout << _power << endl;
	if (_fishingState == FISHING::NONE)_nowFishing = false;//�׽�Ʈ��

	ChargeOne();
	ChargeTwo();				//1.� �Ŀ���ŭ ���󰡴� �Լ�
	Wait();						//2.����ⳬ�϶� ���� ��ٸ��� �Լ�
	MiniGameOn();				//3.���� �̴ϰ��� ����
	DoingFishing();				//4.���� ���� �������϶� �۵�
	Miss();						//����� ��������
	Success();					//������������
}

void MiniGame::Render()
{
	switch (_fishingState)
	{
	case FISHING::FIRST:
		break;
	case FISHING::CHARGE:
		CAMERAMANAGER->rectangle(getMemDC(), _chageBackBox);
		CAMERAMANAGER->rectangle(getMemDC(), _chageFrontBox);
		break;
	case FISHING::SHOT:
		if (_power > 90)
		{
			CAMERAMANAGER->alpharender(getMemDC(), _maximg, _playerCenter.x - 50, _playerCenter.y - 100, _maximgAlpha);
		}
		break;
	case FISHING::WAIT:
		break;
	case FISHING::MINiGAMEON:
		CAMERAMANAGER->render(getMemDC(), _hitimg, _playerCenter.x - 50, _playerCenter.y - 100);
		
		CAMERAMANAGER->render(getMemDC(), _backimg, _fishingUI.x, _fishingUI.y);
		CAMERAMANAGER->render(getMemDC(), _minigameimg, _minigame.x, _minigame.y);
		CAMERAMANAGER->render(getMemDC(), _barimg, _bar.x, _bar.y);

		if (_rareFish)CAMERAMANAGER->render(getMemDC(),_rareFishimg, _fishingHitBox.x, _fishingHitBox.y);
		else CAMERAMANAGER->render(getMemDC(), _fishimg, _fishingHitBox.x, _fishingHitBox.y);
		
		CAMERAMANAGER->rectangle(getMemDC(), _gaugeimg);
		break;
	case FISHING::DOINGMINIGAME:

		CAMERAMANAGER->render(getMemDC(), _backimg, _fishingUI.x, _fishingUI.y);
		CAMERAMANAGER->render(getMemDC(), _minigameimg, _minigame.x, _minigame.y);
		CAMERAMANAGER->render(getMemDC(), _barimg, _bar.x, _bar.y);

		if (_rareFish)CAMERAMANAGER->render(getMemDC(), _rareFishimg, _fishingHitBox.x, _fishingHitBox.y);
		else CAMERAMANAGER->render(getMemDC(), _fishimg, _fishingHitBox.x, _fishingHitBox.y);

		CAMERAMANAGER->rectangle(getMemDC(), _gaugeimg);
		break;
	case FISHING::MISS:
		break;
	case FISHING::SUCCESS:
		break;
	case FISHING::NONE:
		break;
	default:
		break;
	}
}

void MiniGame::Init(Vector2 center, PLAYER_DIRECTION dir)
{
	_fishingState = FISHING::FIRST;

	_missCount = 0;					//���� ī��Ʈ

	_gauge.x = 0;					//���� ����� �󸶳���ư����� ������
	_gauge.y = 0;					

	_fishingUI.x = 0;				//�������� UI
	_fishingUI.y = 0;

	_minigame.x = 0;				//���� �̴ϰ��� ǥ��� ��ǥ
	_minigame.y = 0;

	_fishingHitBox.x = 0;			//������� ��Ʈ�ڽ� �̹���ǥ��� ��ǥ
	_fishingHitBox.y = 0;
	
	_dir = dir;	//�÷��̾��� ���Ⱚ���� �̿����� UI�ߴ� ��ġ�� �޶���
	
	_clickTime = 0;					//�Ŀ� ���� �ð��� ����ϴ� ����
	
	_power = 0;						//�Ŀ���ġ Ÿ�ӿ� ����ؼ� � ���ư��� ����

	_bar.x = 0;						//���ù� ��ǥ �ʱ�ȭ
	_bar.y = 0;

	_playerCenter = center;			//�÷��̾� ���Ͱ� �޾ƿ��� ����
	
	_fishfloat.x = _playerCenter.x;	//���� � ǥ��� ��ǥ
	_fishfloat.y = _playerCenter.y - 50;

	_chageBackBox.set(_playerCenter.x - 50, _playerCenter.y,
		_playerCenter.x + 50, _playerCenter.y + 30);
	_chageFrontBox.set(_chageBackBox.left + 1, _chageBackBox.top + 1,
		_chageBackBox.left + 1, _chageBackBox.bottom - 1);
					//���� �����ʱ�ȭ ������ ���������� ��Ʈ ����
	_maximgAlpha = 255;

	_backimg = IMAGEMANAGER->findImage("FishingBack");			//���� ��ǳ��
	_minigameimg = IMAGEMANAGER->findImage("FishingMiniGame");	//���� �̴ϰ���
	_gaugeimg.set(-500, -500, -500, -500);						//���� ������
	_fishingHitRect.set(-500, -500, -500, -500);				//����� ��Ʈ�ڽ�
	_barRect.set(-500, -500, -500, -500);						//���ù� ��Ʈ
	_barimg = IMAGEMANAGER->findImage("FishingBar");			//���� ��
	_hitimg = IMAGEMANAGER->findImage("FishingStart");			//���� ����
	_maximg = IMAGEMANAGER->findImage("FishingPower");			//�����ִ��Ŀ�����
	_fishimg = IMAGEMANAGER->findImage("FishingFish");			//�����
	_rareFishimg = IMAGEMANAGER->findImage("FishingRareFish");	//������
	_fish = 0;
	_fishTime = 0;

	_nowFishing = true;	//�׽�Ʈ��
}

void MiniGame::ChargeOne()
{
	if (_fishingState == FISHING::CHARGE)
	{
		_chageFrontBox.right++;
		_clickTime++;
	}
}

void MiniGame::ChargeTwo()
{
	
	if (_fishingState==FISHING::SHOT)
	{
		if(_power>90)
		{
			_maximgAlpha -= 1;
		}
		
		if (_power > 100)
		{
			_power = 100;
		}

		if (_dir == PLAYER_DIRECTION::DOWN)
		{
			_fishfloat.y++;

			_power--;
		}

		if (_dir == PLAYER_DIRECTION::LEFT || _dir == PLAYER_DIRECTION::DOWN_LEFT
			|| _dir == PLAYER_DIRECTION::UP_LEFT)
		{
			_fishfloat.x--;
			_fishfloat.y++;

			_power--;
		}

		if (_dir == PLAYER_DIRECTION::RIGHT || _dir == PLAYER_DIRECTION::DOWN_RIGHT
			|| _dir == PLAYER_DIRECTION::UP_RIGHT)
		{
			_fishfloat.x++;
			_fishfloat.y++;

			_power--;
		}

		if (_dir == PLAYER_DIRECTION::UP)
		{
			_fishfloat.y--;

			_power--;
		}
		if (_power <= 0)
		{
			_randomFish = RND->getInt(11);
			_fishingTime = RND->getFromIntTo(0, 150);
			_fishingState = FISHING::WAIT;
		}
	}
}

void MiniGame::Wait()
{
	cout << _missCount << endl;
	if (_fishingState == FISHING::WAIT)
	{
		if (_fish < _randomFish)_fish++;
		if (_fishTime < _fishingTime)_fishTime++;

		if (_fish == _randomFish && _fishTime == _fishingTime)
		{
			_missCount++;

			if (_fish > 3)
			{
				_rareFish = false;
			}

			else if (_fish <= 3)
			{
				_rareFish = true;
			}

			if (_missCount < 500 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_fishingState = FISHING::MINiGAMEON;
			}
			else if (_missCount > 500 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_fishingState = FISHING::MISS;
			}
		}
	}
}


void MiniGame::MiniGameOn()
{
	if (_fishingState == FISHING::MINiGAMEON)
	{
		if (_dir == PLAYER_DIRECTION::LEFT ||
			_dir == PLAYER_DIRECTION::DOWN_LEFT ||
			_dir == PLAYER_DIRECTION::UP_LEFT)
		{
			_fishingUI.x = _playerCenter.x + 200;
			_fishingUI.y = _playerCenter.y - 200;

			_minigame.x = _fishingUI.x + 12;
			_minigame.y = _fishingUI.y;

			_gauge.x = _fishingUI.x + 122;
			_gauge.y = _fishingUI.y + 587;
			_gaugeimg.set(_gauge.x, _gauge.y-400, _gauge.x + 15, _gauge.y);

			_bar.x = _fishingUI.x + 67;
			_bar.y = _fishingUI.y + 425;
			_barRect.set(_bar.x, _bar.y, _bar.x + 34, _bar.y - 96);

			_fishingHitBox.x = _fishingUI.x + 70;
			_fishingHitBox.y = _fishingUI.y + 300;
			_fishingHitRect.set(_fishingHitBox.x, _fishingHitBox.y,
				_fishingHitBox.x + 28, _fishingHitBox.y - 28);

		}
		else
		{
			_fishingUI.x = _playerCenter.x + 200;
			_fishingUI.y = _playerCenter.y - 200;

			_minigame.x = _fishingUI.x + 12;
			_minigame.y = _fishingUI.y;

			_gauge.x = _fishingUI.x + 122;
			_gauge.y = _fishingUI.y + 587;
			_gaugeimg.set(_gauge.x, _gauge.y-400, _gauge.x + 15, _gauge.y);

			_bar.x = _fishingUI.x + 67;
			_bar.y = _fishingUI.y + 425;
			_barRect.set(_bar.x, _bar.y, _bar.x + 34, _bar.y - 96);

			_fishingHitBox.x = _fishingUI.x + 70;
			_fishingHitBox.y = _fishingUI.y + 300;
			_fishingHitRect.set(_fishingHitBox.x, _fishingHitBox.y,
				_fishingHitBox.x + 28, _fishingHitBox.y - 28);


		}
		_fishingState = FISHING::DOINGMINIGAME;
	}

}


void MiniGame::DoingFishing()
{
	if (_fishingState == FISHING::DOINGMINIGAME)
	{
		//cout << (int)_rareFish << endl;
		//�浹������ ��Ʈ������Ʈ=============================================
		_gaugeimg.set(_gauge.x, _gaugeimg.top, _gauge.x + 15, _gauge.y);//�󸶳���ư�����
		_fishingHitRect.set(_fishingHitBox.x, _fishingHitBox.y,//������ǰݷ�Ʈ
			_fishingHitBox.x + 28, _fishingHitBox.y + 28);
		_barRect.set(_bar.x, _bar.y, _bar.x + 34, _bar.y + 96);//�÷��̾��� ����� ��ȹ��Ʈ

		//===================================================================

		//����� ������ ������Ʈ================================================
		if (_rareFish)			//������ ������
		{
		
		if (isCollision(_barRect, _fishingHitRect))
		{
			if (up)_fishingHitBox.y -= 4;

			else _fishingHitBox.y += 4;
		}
			if (up)
			{
				if (_fishingHitBox.y < _fishingUI.y + 20)
				{
					_fishingHitBox.y = _fishingUI.y + 20;
					up = false;
				}
				_fishingHitBox.y--;
			}
			else if (!up)
			{
				if (_fishingHitBox.y > _fishingUI.y + 530)
				{
					_fishingHitBox.y = _fishingUI.y + 530;
					up = true;
				}
				_fishingHitBox.y++;
			}
		}

		if (!_rareFish)			//�Ϲݹ���������
		{
			
			if (up)
			{
				if (_fishingHitBox.y < _fishingUI.y + 20)
				{
					_fishingHitBox.y = _fishingUI.y + 20;
					up = false;
				}
				_fishingHitBox.y-=5;
			}
			if(!up)
			{
				if (_fishingHitBox.y > _fishingUI.y + 530)
				{
					_fishingHitBox.y = _fishingUI.y + 530;
					up = true;
				}
				_fishingHitBox.y+=5;
			}
		}
		//===============================================================

		//�÷��̾� ���� ��Ʈ�ѷ�=============================
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (_bar.y < _fishingUI.y + 15)
			{
				_bar.y = _fishingUI.y + 15;
			}
			_bar.y-=5;
		}
		else
		{
			if (_bar.y > _fishingUI.y + 480)
			{
				_bar.y = _fishingUI.y + 480;
			}
			_bar.y+=6;
		}
		//=================================================
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			cout << _barRect.left << endl;
			cout << _fishingHitRect.left << endl;
			cout << _barRect.top << endl;
			cout << _fishingHitRect.top << endl;
		}

		//��ȹ������ ��� ������Ʈ=============================
		if (isCollision(_barRect, _fishingHitRect))
		{
			_gaugeimg.top -= 3;
		}
		else
		{
			_gaugeimg.top += 3;
		}

		if (_gaugeimg.top < _fishingUI.y + 15)_fishingState = FISHING::SUCCESS;
		if (_gaugeimg.top > _gaugeimg.bottom)_fishingState = FISHING::MISS;
		//===================================================
	}

}

void MiniGame::Miss()
{
	if (_fishingState == FISHING::MISS)
	{
		_fishingState = FISHING::NONE;
	}
}



void MiniGame::Success()
{
	if (_fishingState == FISHING::SUCCESS)
	{
		_fishingState = FISHING::NONE;
	}
}
