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
	typedef vector<RECT>			vInvenRC;	//인벤토리가 열렸을 때 상시 켜져 있는 (정적)렉트 벡터
	typedef vector<RECT>::iterator	viInvenRC;

	vInvenRC		_vInvenStaticRC;			//인벤토리 실행시 항상 떠 있는 정적 렉트
	vInvenRC		_vInvenDynamicRC;			//인벤토리 실행시 특정 탭에서만 켜지는 동적 렉트
	vInvenRC		_vInvenIndexRC;				//인벤토리 칸의 인덱스 렉트

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

	vector<ToolItem*> _toolList;	 // 정보
	vector<ToolItem*> _toolInven;	 // 값 가지고 있는것들 
	int _trashCanFrameX;			//쓰레기통 이미지 프레임
	int _frameCount;				//이미지 프레임 카운트
	int _itemIndexNum;				//아이템 인덱스 번호 저장용

	int _sorted[12];
	int _test[12];
/////////////////////////</Inventory>///////////////////////////

	int _index;
/////////////////////////<QuickSlot>////////////////////////////

	tagQuickSlot _quickSlot;		//퀵슬롯
	tagQuickSlot _quickSlotSelect;	//퀵슬롯선택 사각형

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