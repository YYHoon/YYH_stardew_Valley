#pragma once
#include "gameNode.h"

class Player;

class HpStaminaBar : public gameNode
{
private:
	struct tagBar
	{
		image* topImg;		 //머리 파츠
		image* midImg;		 //몸통 파츠
		image* bottomImg;	 //닫는 파츠
		image* frontBarImg;  //체력및 스테미나 이미지
		image* BottomBarImg; //체력및 스테미나 이미지
		RECT frontBarRc;     //체력및 스테미나 바 렉트
		RECT bottomBarRc;    //체력및 스테미나 바 렉트
		RECT midRc;			 //몸통 파츠 좌표용 렉트
		int x;				 //체력및 스테미나바 초기 좌표지정용 x값
		int y;				 //체력및 스테미나바 초기 좌표지정용 y값
		int hit;
	};

	Player* _pl;

	tagBar _StaminaBar;
	tagBar _HpBar;

public:
	HpStaminaBar() {};
	~HpStaminaBar() {};

	HRESULT init();
	void release();
	void update();
	void staminaBarRender();
	void hpBarRender();

	tagBar GetStaminaBar() { return _StaminaBar; }
	tagBar GetHpBar() { return _HpBar; }



	void setPlayerLink(Player* pp) { _pl = pp; }
	void setPlayerHP(int hp) { _HpBar.hit -= hp; }
	void setPlayerStamina(int stamina) { _StaminaBar.hit -= stamina; }
};