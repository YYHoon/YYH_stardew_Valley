#pragma once





class MiniGame

{
private:
	bool _fishFloatMove = false; //낚시찌움직이는지
	bool _isPlay = false;	//낚시중인지
	Vector2 _gauge;			//물고기얼마나잡아가는지 게이지
	Vector2 _fishingUI;		//낚시중UI표기할좌표(left,top)
	Vector2 _fishingHitBox;	//물고기히트박스
	Vector2 _playerCenter;	//플레이어 센터 받을 변수
	PLAYER_DIRECTION _dir;	//플레이어 상태받을 변수
	int _clickTime=0;			//파워차지용 클릭시간받는변수
	int _power=0;				//이 변수만큼 찌가 날아감
	Vector2 _fishfloat;		//낚시찌좌표

public:

	void InitKeyDown(PLAYER_DIRECTION dir, Vector2 center);
	void InitKeyUp();
	void FishFloatUpdate();
	void Update();
	void Render();


};

