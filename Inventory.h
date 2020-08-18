#pragma once
#include "gameNode.h"
#include "Environment.h"

#include <vector>

class Player;
class ToolItemManager;
class ToolItem;
class Store;

struct tagInventory
{
	string keyname;
	RECT rc;
	image* image;
	int invenTabNum;
	int craftPageNum;
	int x, y;
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
	typedef vector<RECT>			vInvenRC;		//�κ��丮�� ������ �� ��� ���� �ִ� (����)��Ʈ ����
	typedef vector<RECT>::iterator	viInvenRC;

	vInvenRC		_vInvenStaticRC;			//�κ��丮 ����� �׻� �� �ִ� ���� ��Ʈ
	vInvenRC		_vInvenDynamicRC;			//�κ��丮 ����� Ư�� �ǿ����� ������ ���� ��Ʈ
	vInvenRC		_vInvenIndexRC;				//�κ��丮 ĭ�� �ε��� ��Ʈ

	viInvenRC		_viInvenStaticRC;
	viInvenRC		_viInvenDynamicRC;
	viInvenRC		_viInvenIndexRC;

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
	Store* _store;

/////////////////////////<Inventory>////////////////////////////

	tagInventory _inventory;
	Environment* _environment;
	ToolItemManager* _toolItemManager;

	vector<ToolItem*> _toolList;	 // ����
	vector<ToolItem*> _toolInven;	 // �� ������ �ִ°͵� 
	
	RECT _trashCanRC;
	int _trashCanFrameX;
	int _frameCount;
	int _itemIndexNum;
	bool _test;

/////////////////////////</Inventory>///////////////////////////

/////////////////////////<QuickSlot>////////////////////////////
			
	tagQuickSlot _quickSlot;							//������
	tagQuickSlot _quickSlotSelect;						//�����Լ��� �簢��

/////////////////////////</QuickSlot>///////////////////////////

	bool _quickSlotUp;

	int _quickSlotSelectYUP;

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
	vector<ToolItem*> GetInven() { return _toolInven; }
	ToolItem* GetInvenItem(int index) { return _toolInven[index]; }

	
	virtual void setPlayerBuyItme(ToolItem* buyItme);

	void SetMemoryLinkedTool(ToolItemManager* tool) { _toolItemManager = tool; }
	void SetStoreLink(Store* store) { _store = store; }
	void setPlayer(Player* pp) { _player = pp; }
};