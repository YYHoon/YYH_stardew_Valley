#pragma once
#include "gameNode.h"
#include "Environment.h"

#include <vector>

class Player;
class ToolItemManager;
class ToolItem;

struct tagInventory
{
	string keyname;
	RECT rc;
	image* image;
	int invenTabNum;
	int craftPageNum;
	int x, y;
	bool isInvenOpen;
};

struct tagQuickSlot
{
	image* image;
	int x, y;
	int uY;
};

class Inventory : public gameNode
{
private:
	typedef vector<RECT>			vInvenStaticRC;		//인벤토리가 열렸을 때 상시 켜져 있는 (정적)렉트 벡터
	typedef vector<RECT>			vInvenDynamicRC;	//인벤토리가 열렸을 때 상황에 따라 켜지는 (동적)렉트 벡터 
	typedef vector<RECT>			vInvenIndexRC;		//각 인벤토리 칸 벡터

	typedef vector<RECT>::iterator	viInvenStaticRC;
	typedef vector<RECT>::iterator	viInvenDynamicRC;
	typedef vector<RECT>::iterator	viInvenIndexRC;

	vector<tagInventory>	_vAllInventory;				//어디에 쓰려고 만들었더라.............

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
	//////////////////////////////////////////

	Player* _player;

/////////////////////////<Inventory>////////////////////////////

	tagInventory _inventory;
	Environment* _environment;
	ToolItemManager* _toolItemManager;

	vector<ToolItem*> _toolList; // 정보
	vector <ToolItem*> _toolInven; // 값 가지고 있는것들 
	//ToolItem* _getItem;
	
	RECT _trashCanRC;
	int _trashCanFrameX;
	int _frameCount;

/////////////////////////</Inventory>///////////////////////////

/////////////////////////<QuickSlot>////////////////////////////
			
	tagQuickSlot _quickSlot;							//퀵슬롯
	tagQuickSlot _quickSlotSelect;						//퀵슬롯선택 사각형

/////////////////////////</QuickSlot>///////////////////////////

public:
	Inventory()  {};
	~Inventory() {}; 

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void quickSlotMove();

	void PlayerLootItem(ToolItem* item);
	
	vector<RECT>	 GetVInvenIndexRC() { return _vInvenIndexRC; }
	vector<tagInventory> GetInventory() { return _vAllInventory; }
	vector<ToolItem*> GetInven() { return _toolInven; }
	void SetInven(vector<ToolItem*> inven) {_toolInven = inven; }
	ToolItem* GetInvenItem(int index) { return _toolInven[index]; }

	void SetMemoryLinkedTool(ToolItemManager* tool) { _toolItemManager = tool; }
};