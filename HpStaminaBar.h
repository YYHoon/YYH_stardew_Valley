#pragma once
#include "gameNode.h"
#include "Player.h"

class HpStaminaBar : public gameNode
{
private:
	struct tagBar
	{
		image* topImg;		 //�Ӹ� ����
		image* midImg;		 //���� ����
		image* bottomImg;	 //�ݴ� ����
		image* frontBarImg;  //ü�¹� ���׹̳� �̹���
		image* BottomBarImg; //ü�¹� ���׹̳� �̹���
		RECT frontBarRc;     //ü�¹� ���׹̳� �� ��Ʈ
		RECT bottomBarRc;    //ü�¹� ���׹̳� �� ��Ʈ
		RECT midRc;			 //���� ���� ��ǥ�� ��Ʈ
		int x;				 //ü�¹� ���׹̳��� �ʱ� ��ǥ������ x��
		int y;				 //ü�¹� ���׹̳��� �ʱ� ��ǥ������ y��
		int hit;
	};

	Player* _pl;

	tagBar _StaminaBar;
	tagBar _HpBar;


	HFONT Font, OldFont; //��Ʈ�����

	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());// ���콺 ī�޶� ��ġ

public:
	HpStaminaBar() {};
	~HpStaminaBar() {};

	HRESULT init();
	void release();
	void update();
	void staminaBarRender();
	void hpBarRender();

	void setPlayerHP(int hp);
	void setPlayerStamina(int stamina);
};