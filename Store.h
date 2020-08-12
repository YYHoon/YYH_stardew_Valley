#pragma once
#include "gameNode.h"
#include <string>
#include <vector>

struct tagStoreTsetItem //테스트용입니다.
{
	image* img;				//아이템 이미지
	RECT rc;				//아이템 렉트
	string name;			//아이템 이름
	string description;		//아이템 설명
	int price;				//아이템 가격
};

class Store : public gameNode
{
private:
	vector<tagStoreTsetItem>			_vStoreItem;	//상점상자?
	vector<tagStoreTsetItem>::iterator	_viStoreItem;

	image* _StoreWindow;	  //상점창
	image* _StorePortrait;	  //상점주인초상화
	image* _StoreItem[20];	  //상점 아이템
	image* _StoreInfo;		  //상점소개문창
	image* _StoreNPC;		  //상점npc도트이미지

	image* _CloseButton;      //닫기버튼
	image* _BlackWindow;      //알파먹일거
	
	vector<RECT> _Item;	     //상점상자
	RECT _CloseRc;			 //닫기버튼
	RECT _StoreNpcRect;		 //npc이미지사용전용
	RECT _StoreNpcOpen;		 //이영역 내에서만 기능을 활성화시킬수있음(상점)


	int _StoreItmeFrameY; //상점물품선택시전용
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;

public:
	Store();
	~Store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};