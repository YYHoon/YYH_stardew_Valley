#pragma once
#include "gameNode.h"

struct tagFish
{
	image* img;
	Vector2 pos;
	MYRECT rc;
	bool Setting;
};


class MiniGame : public gameNode

{
private:
	bool _nowFishing;				 //테스트용

	FISHING _fishingState;			 //낚시 상태
	
	bool _rareFish;					 //레어물고기인지 판별

	Vector2 _gauge;				 	 //물고기얼마나잡아가는지 게이지
	Vector2 _fishingUI;				 //낚시중UI표기할좌표(left,top)말풍선
	Vector2 _minigame;				 //미니게임
	Vector2 _bar;					 //낚시 바 좌표
	MYRECT _barRect;				 //낚시바 렉트
	Vector2 _fishingHitBox;		 	 //물고기히트박스좌표
	MYRECT _fishingHitRect;			 //물고기 히트렉트
	Vector2 _playerCenter;			 //플레이어 센터 받을 변수
	MYRECT _chageFrontBox;			 //차지게이지 렉트 앞면
	MYRECT _chageBackBox;			 //차지게이지 렉트 뒷면
	Vector2 _fishfloat;				 //낚시찌좌표
	int _clickTime=0;				 //파워차지용 클릭시간받는변수
	int _power=0;					 //이 변수만큼 찌가 날아감
	PLAYER_DIRECTION _dir;			 //플레이어 상태받을 변수

	tagFish _Fish;	//물고기 이미지와 좌표담은 구조체
	MYRECT _test;
	MYRECT	_playTest;

	image* _backimg;					 //낚시 말풍선
	image* _minigameimg;				 //낚시 미니게임
	MYRECT _gaugeimg;					 //낚시 게이지
	image* _barimg;						 //낚시 바
	image* _hitimg;						 //낚시 시작
	image* _maximg;						 //낚시최대파워던짐
	image* _fishimg;					 //물고기
	image* _rareFishimg;				 //레어물고기

	int _hitcount;
	int _missCount;						 //입질시간 카운팅 타이머
	int _maximgAlpha;					 //맥스 이미지 알파값
	int _randomFish;					 //랜덤한 물고기 낚을확률
	int _fish;							 //물고기종류 정해질변수
	int _fishingTime;					 //물고기낚이는데 걸릴시간
	int _fishTime;						 //물고기확률
	bool up = false;							 //물고기무빙

public:
	MiniGame() { _nowFishing = false; }
	virtual ~MiniGame() {};

	void Init(Vector2 center, PLAYER_DIRECTION dir);	//낚시시작전에 원래있던 정보 초기화용
	void ChargeOne();									//낚시찌던질때 기모으기
	void ChargeTwo();									//찌날라가는중
	void Wait();										//물고기낚일때까지 기다리는중
	void MiniGameOn();									//차지2에서 물고기가물었을때 클릭해서 미니게임 들어왔을때
	void Miss();										//물고기 낚는데 실패했을때
	void DoingFishing();								//낚시하는도중
	void Success();										//낚시 성공했을때

	FISHING GetDoingFishing() { return _fishingState; }
	void SetDoingFishing(FISHING fish) { _fishingState = fish; }

	

	void Update();
	void Render();

	void SetNowFishing(bool i) { _nowFishing = i; }
	bool GetNowFishing() { return _nowFishing; }

};

