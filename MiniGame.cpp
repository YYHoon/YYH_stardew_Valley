#include "stdafx.h"
#include "MiniGame.h"


void MiniGame::Update()
{
	cout << "낚시에서의 상태" << (int)_fishingState << endl;
	if (_fishingState == FISHING::FIRST)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_fishingState = FISHING::CHARGE;
			//_chageFrontBox.right ++;
		}
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)&& _fishingState == FISHING::CHARGE)
	{
		_power = _clickTime;
		_fishingState = FISHING::SHOT;
	}
	
	switch (_fishingState)
	{
	case FISHING::FIRST://0
		break;
	case FISHING::CHARGE://1
		_chageFrontBox.right++;
		_clickTime++;
		if (_chageFrontBox.right >= _chageBackBox.right - 1)_chageFrontBox.right = _chageBackBox.right - 1;
		
		break;
	case FISHING::SHOT://2
		ChargeTwo();				//1.찌가 파워만큼 날라가는 함수
		break;
	case FISHING::WAIT://3
		Wait();						//2.물고기낚일때 까지 기다리는 함수
		break;
	case FISHING::MINiGAMEON://4
		MiniGameOn();				//3.낚시 미니게임 시작(UI좌표셋팅)
		break;
	case FISHING::DOINGMINIGAME://5
		DoingFishing();				//4.낚시 게임 진행중일때 작동
		break;
	case FISHING::MISS://6
		Miss();						//물고기 놓쳤을때
		break;
	case FISHING::SUCCESS://7
		Success();					//물고기잡았을때
		break;
	case FISHING::NONE://8
		_fishingState = FISHING::FIRST;
		break;
	default:
		break;
	}
	//ChargeTwo();				//1.찌가 파워만큼 날라가는 함수
	//Wait();						//2.물고기낚일때 까지 기다리는 함수
	//MiniGameOn();				//3.낚시 미니게임 시작
	//DoingFishing();				//4.낚시 게임 진행중일때 작동
	//Miss();						//물고기 놓쳤을때
	//Success();					//물고기잡았을때
}

void MiniGame::Render()
{
	
	_test.set(_fishfloat.x, _fishfloat.y, _fishfloat.x + 30, _fishfloat.y - 30);
	//_test.render(getMemDC());
	switch (_fishingState)
	{
	case FISHING::FIRST:
		break;
	case FISHING::CHARGE:
		CAMERAMANAGER->rectangle(getMemDC(), _chageBackBox);
		CAMERAMANAGER->rectangle(getMemDC(), _chageFrontBox);
		//_chageBackBox.render(getMemDC());
		//_chageFrontBox.render(getMemDC());
		
		break;
	case FISHING::SHOT:
		if (_power > 90)
		{
			CAMERAMANAGER->alpharender(getMemDC(), _maximg, _playerCenter.x, _playerCenter.y, _maximgAlpha);
			//_maximg->alphaRender(getMemDC(), _playerCenter.x, _playerCenter.y, _maximgAlpha);
		}
			CAMERAMANAGER->rectangle(getMemDC(), _test);
		break;
	case FISHING::WAIT:
		if (_fish == _randomFish && _fishTime == _fishingTime && _hitcount < 50)
		{
			CAMERAMANAGER->render(getMemDC(), _hitimg,_fishfloat.x, _fishfloat.y + 50);
			//_hitimg->render(getMemDC(), _fishfloat.x, _fishfloat.y+50);
		}
			CAMERAMANAGER->rectangle(getMemDC(), _test);
		break;
	case FISHING::MINiGAMEON:
		CAMERAMANAGER->render(getMemDC(), _hitimg, _playerCenter.x, _playerCenter.y);
		CAMERAMANAGER->render(getMemDC(), _backimg, _fishingUI.x, _fishingUI.y);
		CAMERAMANAGER->render(getMemDC(), _minigameimg, _minigame.x, _minigame.y);
		CAMERAMANAGER->render(getMemDC(), _barimg, _bar.x, _bar.y);
		if (_rareFish)CAMERAMANAGER->render(getMemDC(), _rareFishimg, _fishingHitBox.x, _fishingHitBox.y);
		else CAMERAMANAGER->render(getMemDC(), _fishimg, _fishingHitBox.x, _fishingHitBox.y);
		CAMERAMANAGER->rectangle(getMemDC(), _gaugeimg);
		CAMERAMANAGER->rectangle(getMemDC(), _test);

		
		//_hitimg->render(getMemDC(), _playerCenter.x , _playerCenter.y );

		//_backimg->render(getMemDC(),_fishingUI.x, _fishingUI.y);
		//_minigameimg->render(getMemDC(),_minigame.x, _minigame.y);
		//_barimg->render(getMemDC(), _bar.x, _bar.y);

		//if (_rareFish)_rareFishimg->render(getMemDC(), _fishingHitBox.x, _fishingHitBox.y); 
		//else _fishimg->render(getMemDC(), _fishingHitBox.x, _fishingHitBox.y);
		
		//_gaugeimg.render(getMemDC());

		break;
	case FISHING::DOINGMINIGAME:
		
		CAMERAMANAGER->render(getMemDC(), _backimg, _fishingUI.x, _fishingUI.y);
		CAMERAMANAGER->render(getMemDC(), _minigameimg, _minigame.x, _minigame.y);
		CAMERAMANAGER->render(getMemDC(), _barimg, _bar.x, _bar.y);
		if (_rareFish)CAMERAMANAGER->render(getMemDC(), _rareFishimg, _fishingHitBox.x, _fishingHitBox.y);
		else CAMERAMANAGER->render(getMemDC(), _fishimg, _fishingHitBox.x, _fishingHitBox.y);
		CAMERAMANAGER->rectangle(getMemDC(), _gaugeimg);
		CAMERAMANAGER->rectangle(getMemDC(), _test);
		//_backimg->render(getMemDC(), _fishingUI.x, _fishingUI.y);
		//_minigameimg->render(getMemDC(), _minigame.x, _minigame.y);
		//_barimg->render(getMemDC(), _bar.x, _bar.y);

		//if (_rareFish)_rareFishimg->render(getMemDC(), _fishingHitBox.x, _fishingHitBox.y);
		//else _fishimg->render(getMemDC(), _fishingHitBox.x, _fishingHitBox.y);

		//_gaugeimg.render(getMemDC());

		break;
	case FISHING::MISS:
		break;
	case FISHING::SUCCESS:
		CAMERAMANAGER->render(getMemDC(), _Fish.img, _Fish.pos.x, _Fish.pos.y);
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
	_Fish.img = NULL;
	_Fish.pos.x = -500;
	_Fish.pos.y = -500;
	_Fish.rc.set(_Fish.pos.x - 1, _Fish.pos.y - 1, _Fish.pos.x + 1, _Fish.pos.y + 1);
	_Fish.Setting = false;
	_missCount = 0;					//입질 카운트

	_gauge.x = 0;					//낚시 물고기 얼마나잡아가는지 게이지
	_gauge.y = 0;					

	_hitcount = 0;

	_fishingUI.x = 0;				//낚시중의 UI
	_fishingUI.y = 0;

	_minigame.x = 0;				//낚시 미니게임 표기될 좌표
	_minigame.y = 0;

	_fishingHitBox.x = 0;			//물고기의 히트박스 이미지표기될 자표
	_fishingHitBox.y = 0;
	
	_dir = dir;	//플레이어의 방향값저장 이에따라 UI뜨는 위치가 달라짐
	
	_clickTime = 0;					//파워 차지 시간을 기억하는 변수
	
	_power = 0;						//파워차치 타임에 비례해서 찌가 날아가는 변수

	_bar.x = 0;						//낚시바 좌표 초기화
	_bar.y = 0;

	_playerCenter.x = center.x;			//플레이어 센터값 받아오는 변수
	_playerCenter.y = center.y;			//플레이어 센터값 받아오는 변수
	cout << _playerCenter.x << endl;
	cout << _playerCenter.y << endl;

	_fishfloat.x = _playerCenter.x;	//낚시 찌가 표기될 좌표
	_fishfloat.y = _playerCenter.y-100;

	_chageBackBox.set(_fishfloat.x-50 , _fishfloat.y-50,
		_fishfloat.x + 50, _fishfloat.y - 80);
	_chageFrontBox.set(_chageBackBox.left + 1, _chageBackBox.top + 1,
		_chageBackBox.left + 1, _chageBackBox.bottom - 1);
					//낚시 시작초기화 했으니 차지게이지 렉트 생성
	_maximgAlpha = 255;

	_backimg = IMAGEMANAGER->findImage("FishingBack");			//낚시 말풍선
	_minigameimg = IMAGEMANAGER->findImage("FishingMiniGame");	//낚시 미니게임
	_gaugeimg.set(-500, -500, -500, -500);						//낚시 게이지
	_fishingHitRect.set(-500, -500, -500, -500);				//물고기 히트박스
	_barRect.set(-500, -500, -500, -500);						//낚시바 렉트
	_barimg = IMAGEMANAGER->findImage("FishingBar");			//낚시 바
	_hitimg = IMAGEMANAGER->findImage("FishingStart");			//낚시 시작
	_maximg = IMAGEMANAGER->findImage("FishingPower");			//낚시최대파워던짐
	_fishimg = IMAGEMANAGER->findImage("FishingFish");			//물고기
	_rareFishimg = IMAGEMANAGER->findImage("FishingRareFish");	//레어물고기
	_fish = 0;
	_fishTime = 0;

	_nowFishing = true;	//테스트용
}

void MiniGame::ChargeOne()
{
	if (_fishingState == FISHING::CHARGE)
	{
		_chageFrontBox.right++;
		_clickTime++;
		if (_chageFrontBox.right >= _chageBackBox.right - 1)_chageFrontBox.right = _chageBackBox.right - 1;
	
	}
}

void MiniGame::ChargeTwo()
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
		_fishfloat.y+=3;

		_power-=2;
	}

	if (_dir == PLAYER_DIRECTION::LEFT)
	{
		_fishfloat.x-=3;
		_fishfloat.y+=3;

		_power-=2;
	}

	if (_dir == PLAYER_DIRECTION::RIGHT )
	{
		_fishfloat.x += 3;
		_fishfloat.y+=3;

		_power-=2;
	}

	if (_dir == PLAYER_DIRECTION::UP)
	{
		_fishfloat.y-=3;

		_power-=2;
	}
	if (_power <= 0)
	{
		_fishingState = FISHING::WAIT;
		_randomFish = RND->getInt(11);//레어 일반 확률
		_fishingTime = RND->getFromIntTo(0, 150);//물고기잡힐타임확률
	}
	
}

void MiniGame::Wait()
{

	if (_fish == _randomFish && _fishTime == _fishingTime)
	{
		_missCount++;
		_hitcount++;
		if (_fish > 3)
		{
			_rareFish = false;
		}

		else if (_fish <= 3)
		{
			_rareFish = true;
		}

		if (_hitcount < 50 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hitcount = 0;
			_fishingState = FISHING::MINiGAMEON;
		}
		else if (_hitcount > 50 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hitcount = 0;
			_fishingState = FISHING::MISS;
		}
		
	}
	if (_fish < _randomFish)_fish++;
	if (_fishTime < _fishingTime)_fishTime++;
	
}


void MiniGame::MiniGameOn()
{

	if (_dir == PLAYER_DIRECTION::LEFT)
	{
		_fishingUI.x = _playerCenter.x + 300;
		_fishingUI.y = _playerCenter.y - 400;

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
		_fishingUI.x = _playerCenter.x - 300;
		_fishingUI.y = _playerCenter.y - 400;

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


void MiniGame::DoingFishing()
{
	
	//충돌판정용 렉트업데이트=============================================
	_gaugeimg.set(_gauge.x, _gaugeimg.top, _gauge.x + 15, _gauge.y);//얼마나잡아가는지
	_fishingHitRect.set(_fishingHitBox.x, _fishingHitBox.y,//물고기피격렉트
		_fishingHitBox.x + 28, _fishingHitBox.y + 28);
	_barRect.set(_bar.x, _bar.y, _bar.x + 34, _bar.y + 96);//플레이어의 물고기 포획렉트

	//===================================================================

	//물고기 움직임 업데이트================================================
	if (_rareFish)			//레어물고기 움직임
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

	if (!_rareFish)			//일반물고기움직임
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

	//플레이어 낚시 컨트롤러=============================
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
	
	//포획게이지 상승 업데이트=============================
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

void MiniGame::Miss()
{
	_fishingState = FISHING::FIRST;
}



void MiniGame::Success()
{
	if (_rareFish)_Fish.img = IMAGEMANAGER->findImage("RareFish(64x64)");
	else if (!_rareFish)_Fish.img = IMAGEMANAGER->findImage("NormalFish(64x64)");
	
	if (!_Fish.Setting)
	{
		_Fish.pos.x = _fishfloat.x;
		_Fish.pos.y = _fishfloat.y;
		_Fish.Setting = true;
	}

	//switch (_dir)
	//{
	//case PLAYER_DIRECTION::UP:
	//	if (_Fish.pos.y < _playerCenter.y)_Fish.pos.y += 2;
	//	break;
	//case PLAYER_DIRECTION::DOWN:
	//	if (_Fish.pos.y > _playerCenter.y)_Fish.pos.y -= 2;
	//	break;
	//case PLAYER_DIRECTION::RIGHT:
	//	if (_Fish.pos.x > _playerCenter.x)_Fish.pos.x += 2;
	//	if (_Fish.pos.y > _playerCenter.y)_Fish.pos.y += 2;
	//	break;
	//case PLAYER_DIRECTION::LEFT:
	//	if (_Fish.pos.x < _playerCenter.x)_Fish.pos.x -= 2;
	//	if (_Fish.pos.y > _playerCenter.y)_Fish.pos.y += 2;
	//	break;
	//default:
	//	break;
	//}
	if (_dir == PLAYER_DIRECTION::UP && _Fish.pos.y < _playerCenter.y)
	{
		_Fish.pos.y += 5;
	}
	else if (_dir == PLAYER_DIRECTION::DOWN && _Fish.pos.y > _playerCenter.y)
	{
		_Fish.pos.y -= 5;
	}
	else if (_dir == PLAYER_DIRECTION::RIGHT && _Fish.pos.x > _playerCenter.x || _Fish.pos.y > _playerCenter.y)
	{
		_Fish.pos.x -= 5;
		_Fish.pos.y -= 5;
	}
	else if (_dir == PLAYER_DIRECTION::LEFT && _Fish.pos.x < _playerCenter.x || _Fish.pos.y > _playerCenter.y)
	{
		_Fish.pos.x += 5;
		_Fish.pos.y -= 5;
	}
	else
	{
		_fishingState = FISHING::NONE;
	}

	_Fish.rc.set(_Fish.pos.x - 5, _Fish.pos.y - 5, _Fish.pos.x + 5, _Fish.pos.y + 5);
	
}
