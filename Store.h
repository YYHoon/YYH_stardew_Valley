#pragma once
#include "gameNode.h"
#include <string>
#include <vector>
//상점은 인밴토리를 참고한다~

class Player;
class ToolItemManager;
class ToolItem;
class Inventory;

class Store : public gameNode
{
private:
	ToolItemManager* _ItemManager;
	Inventory* _inven;
	Player* _player;

	vector<ToolItem*> _itemInfo;
	vector<ToolItem*> _saleItem;

	string _saleKoName[7]; //아이템 한글진열
	int _saleMoney[7];     //돈

	image* _StoreWindow;	  //상점창
	image* _StorePortrait;	  //상점주인초상화
	image* _StoreItem[4];	  //상점 아이템
	image* _StoreInfo;		  //상점소개문창
	image* _StoreNPC;		  //상점npc도트

	image* _CloseButton;     //닫기버튼
	image* _BlackWindow;

	image* _StoreUpArrow;	  //상점열었을떄 물건고르는 위쪽화살표
	image* _StoreDownArrow;   //상점열었을떄 물건고르는 아래쪽화살표

	image* _noMoney;		//돈없누
	int _noMoneyAlpha;		//돈없누 이미지 Alpha

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

	int _bupp;
	int _StoreSearchMin;	//상점물품 탐색영역

	bool _storeOpen;		//상점 열었누!

	RECT _SellRect[12];

public:
	Store();
	~Store();

	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void OpenStoreRender();

	RECT getStoreNpcRect() { return _StoreNpcRect; }  //열기위해 눌러야 되는남자
	RECT getStoreNpcOpen() { return _StoreNpcOpen; }  //열수있는 영역내부~
	vector<ToolItem*> getStoreSaleItem() { return _saleItem; }
	bool getStoreOpen() { return _storeOpen; }

	void setStoreOpen(bool isOpen) { _storeOpen = isOpen; }

	void setLinkToolItemManager(ToolItemManager* TIM) { _ItemManager = TIM; }
	void setLinkInventory(Inventory* Inven) { _inven = Inven; }
	void setLinkPlayer(Player* player) { _player = player; }
};