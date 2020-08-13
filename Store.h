#pragma once
#include "gameNode.h"
#include <string>
#include <vector>
//상점은 인밴토리를 참고한다~


class Store : public gameNode
{
private:

	image* _StoreWindow;	  //상점창
	image* _StorePortrait;	  //상점주인초상화
	image* _StoreItem[4];	  //상점 아이템
	image* _StoreInfo;		  //상점소개문창
	image* _StoreNPC;		  //상점npc도트
	
	image* _StoreUpArrow;	  //상점열었을떄 물건고르는 위쪽화살표
	image* _StoreDownArrow;   //상점열었을떄 물건고르는 아래쪽화살표

	vector<RECT> _Item;	     //상점상자들(4개)
	RECT _CloseRc;			 //닫기버튼
	RECT _StoreNpcRect;		 //npc이미지사용전용
	RECT _StoreNpcOpen;		 //이영역 내에서만 기능을 활성화시킬수있음(상점)

	RECT _StoreUpArrowRc;	 //상점열었을떄 물건고르는 위쪽화살표 충돌처리용
	RECT _StoreDownArrowRc;	 //상점열었을떄 물건고르는 아래쪽화살표 충돌처리용

	int _StoreItmeFrameY;	//상점물품선택시전용
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;

	int _StoreSearchMin;
	int _StoreSearchMax;

public:
	Store();
	~Store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void OpenStoreRender();
	virtual void draw();

	RECT getStoreNpcRect() {return _StoreNpcRect; }
	RECT getStoreNpcOpen() {return _StoreNpcOpen; }
};