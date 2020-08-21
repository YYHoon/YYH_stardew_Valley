#pragma once
#include "gameNode.h"
#include "CraftingDialog.h"

class Inventory;
class ToolItem;
class ToolItemManager;

struct tagCrafting
{
	image* imageAfter;
	image* imageBefore;
	RECT rc;
	int x, y;
	bool isPossible;
};

class Crafting : public gameNode
{
private:
	tagCrafting _grilledFish;			//구운 생선
	tagCrafting _rawFish;				//생선회
	tagCrafting _salad;					//샐러드

	vector<ToolItem*> _toolList;		// 정보

	vector<int*> _itemNum;				//아이템 개수

	Inventory* _inventory;
	ToolItem* _toolItem;
	CraftingDialog* _craftingDiaTree;

public:
	Crafting() {};
	~Crafting() {};

	HRESULT init();
	void release();
	void update();
	void render();
};
