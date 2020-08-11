#pragma once
#include "gameNode.h"
#include "Inventory.h"
#include <fstream>
#include <string>
#include <vector>

class TestScene : public gameNode
{
private:
	image* _Mouse; //마우스 이미지 ->씬마다 한번씩만 이미지 물려주시고 랜더에 좌표는 _ptmouseX, _ptmouseY  써주새요
	Inventory* _inv;

	image* _StoreWindow;	 //상점창
	image* _StorePortrait;	//상점주인초상화
	image* _StoreItem[20];		//상점 아이템
	image* _StoreInfo;		//상점소개문창
	image* _StoreNPC;      //상점npc도트이미지

	image* _CloseButton;     //닫기버튼
	image* _BlackWindow;     //알파먹일거

	RECT _StoreItemRc[20];   //상점 아이템진열좌표 및 충돌처리용
	RECT _CloseRc;			 //닫기버튼
	RECT _StoreNpcRect;		 //npc이미지사용전용
	RECT _StoreNpcOpen;		 //이영역 내에서만 기능을 활성화시킬수있음(상점)
	vector<RECT> _Item;

	int _StoreItmeFrameY; //상점물품선택시전용
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;
	int _StoreItmeFrameY5;

	bool _StoreOpen;  //상점

//-------------------------다이얼로그_더미--------------------------------
	image* _ChatWindow;      	 //대화창 이미지
	image* _TalkingNpcImage;     //대화전용NPC 도트이미지
	image* _TalkingNpcPortrait;  //대화전용NPC 초상화
	image* _TalkingXBox;		 //대화창 우측하단에 있는거 별다른 효과없음
	//animation* _TalkingXBoxAni;

	RECT _TalkingNpcImageRc; //대화용NPC 이미지용
	RECT _TalkingNpc;	     //대화용NPC 대화가능영역

	vector<string> _txtInTest;    //txt파일만을 담는다
	string _txtOutTest;		 //위에서 1글자씩 받아와서 보여주는 아이
	RECT _TxtBoxRC;	     //문자가 뿌려질 위치

	bool _Talking;			 //대화를 하는중인가
	int _stringNum;			 //strin.~.at()에서 사용~

//-------------------------------------------------------------------------

	RECT _TestP;	  //테스트용더미
	int _mouseIndex;  //마우스 이미지 프레임

public:
	TestScene();
	~TestScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Draw();
};