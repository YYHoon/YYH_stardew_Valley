#pragma once
#include "gameNode.h"
#include <vector>

class Inventory : public gameNode
{
private:
	typedef vector<RECT>	vInvenStaticRC;				//�κ��丮�� ������ �� ��� ���� �ִ� (����)��Ʈ ����
	typedef vector<RECT>	vInvenDynamicRC;			//�κ��丮�� ������ �� ��Ȳ�� ���� ������ (����)��Ʈ ���� 
	typedef vector<RECT>	vInvenIndexRC;				//�� �κ��丮 ĭ ����

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

	int  _tabNum;			//�κ��丮 ���� ��ȣ
	int  _craftTabNum;		//���� ������ ��ȣ
	bool _isInventoryOpen;	//�κ��丮�� �����ִ°�?

public:
	Inventory()  {};
	~Inventory() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<RECT>	getVInvenIndexRC() { return _vInvenIndexRC; }

};

