#pragma once
#include "gameNode.h"
#include "Environment.h"
#include "Dialog.h"
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
	bool isInvenOpen;
};

struct tagQuickSlot
{
	image* image;
	int x, y, uY;
};

class Inventory : public gameNode
{
private:
	typedef vector<RECT>			vInvenRC;	//�κ��丮�� ������ �� ��� ���� �ִ� (����)��Ʈ ����
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
	RECT _trashCanRC;		// Dynamic RC   //		
	RECT _sortRC;			// Dynamic RC   //	
	//////////////////////////////////////////
	RECT _indexRC[12];	    // Index RC     //
	//////////////////////////////////////////

	Player* _player;
	Store* _store;

	/////////////////////////<Inventory>////////////////////////////

	tagInventory _inventory;

	ToolItemManager* _toolItemManager;

	vector<ToolItem*> _toolList;	 // ����
	vector<ToolItem*> _toolInven;	 // �� ������ �ִ°͵� 
	int _trashCanFrameX;			//�������� �̹��� ������
	int _frameCount;				//�̹��� ������ ī��Ʈ
	int _itemIndexNum;				//������ �ε��� ��ȣ �����

	int _sorted[12];
	int _test[12];
/////////////////////////</Inventory>///////////////////////////

	int _index;
/////////////////////////<QuickSlot>////////////////////////////

	tagQuickSlot _quickSlot;		//������
	tagQuickSlot _quickSlotSelect;	//�����Լ��� �簢��

/////////////////////////</QuickSlot>///////////////////////////

	bool _quickSlotUp;

	int _quickSlotSelectYUP;

	Dialog* _Dialog;

	/////////////////////////</SAVE LOAD>///////////////////////////	
	int size;
public:
	Inventory() {};
	~Inventory() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void quickSlotMove();

	void Merge(vector<ToolItem*> &vIndex, int left, int mid, int right);
	void MergeSort(vector<ToolItem*> &vIndex, int left, int right);


	void Decrease();

	vector<RECT>	 GetVInvenIndexRC() { return _vInvenIndexRC; }
	vector<ToolItem*> GetInven() { return _toolInven; }
	ToolItem* GetInvenItem(int index) { return _toolInven[index]; }

	void PlayerLootItem(string itemName);
	void setPlayerBuyItme(ToolItem* buyItme);
	void SetStoreLink(Store* store) { _store = store; }
	void setPlayer(Player* pp) { _player = pp; }


	/////////////////////////<SAVE LOAD>///////////////////////////
	void Save();
	void SaveSize();
	void Load();
	void LoadSize();
	/////////////////////////</SAVE LOAD>//////////////////////////
};