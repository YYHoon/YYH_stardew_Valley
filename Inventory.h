#pragma once
#include "gameNode.h"
#include <vector>

class Inventory : public gameNode
{
private:
	typedef vector<RECT>	vInvenStaticRC;				//인벤토리가 열렸을 때 상시 켜져 있는 (정적)렉트 벡터
	typedef vector<RECT>	vInvenDynamicRC;			//인벤토리가 열렸을 때 상황에 따라 켜지는 (동적)렉트 벡터 
	typedef vector<RECT>	vInvenIndexRC;				//각 인벤토리 칸 벡터

	typedef vector<RECT>::iterator	viInvenStaticRC;
	typedef vector<RECT>::iterator	viInvenDynamicRC;
	typedef vector<RECT>::iterator	viInvenIndexRC;

	vInvenStaticRC		_vInvenStaticRC;
	vInvenDynamicRC		_vInvenDynamicRC;
	vInvenIndexRC		_vInvenIndexRC;

	viInvenStaticRC		_viInvenStaticRC;
	viInvenDynamicRC	_viInvenDynamicRC;
	viInvenIndexRC		_viInvenIndexRC;

	//////////////////////////////////////////
	RECT _inventoryCloseRC;	// Static RC    //
	RECT _invenTabRC[5];	// Static RC    //
	//////////////////////////////////////////
	RECT _titleRC;			// Dynamic RC   //
	RECT _closeRC;			// Dynamic RC   //
	RECT _menuDownRC;		// Dynamic RC   //
	RECT _menuUpRC;			// Dynamic RC   //
	//////////////////////////////////////////
	RECT _indexRC[12];	    // Index RC     //
//	RECT _inventoryRC[12];  // Inventory RC //
	//////////////////////////////////////////

	int  _tabNum;			//인벤토리 탭의 번호
	int  _craftTabNum;		//제작 페이지 번호
	bool _isInventoryOpen;	//인벤토리가 열려있는가?

public:
	Inventory()  {};
	~Inventory() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<RECT>	getVInvenIndexRC() { return _vInvenIndexRC; }

};

