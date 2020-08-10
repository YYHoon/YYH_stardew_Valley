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

	////////////////////////////////////////
	RECT _inventoryCloseRC;	// Static RC  //
	RECT _invenTabRC[5];	// Static RC  //
	////////////////////////////////////////
	RECT _titleRC;			// Dynamic RC //
	RECT _closeRC;			// Dynamic RC //
	RECT _menuDownRC;		// Dynamic RC //
	RECT _menuUpRC;			// Dynamic RC //
	////////////////////////////////////////
	RECT _inventoryRC[12];	// Index RC   //
	////////////////////////////////////////

	int _tabNum;
	int _craftTabNum;
	bool _isInventoryOpen;

public:
	Inventory()		{};
	~Inventory()	{};

	HRESULT init();
	void release();
	void update();
	void render();

	void InventoryImageInit();

	vector<RECT>	getVInvenIndexRC()			{ return _vInvenIndexRC; }
	vector<RECT>::iterator	getViInvenIndexRC() { return _viInvenIndexRC; }

};

