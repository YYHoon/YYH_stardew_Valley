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
	tagCrafting _grilledFish;			//���� ����
	tagCrafting _rawFish;				//����ȸ
	tagCrafting _salad;					//������

	vector<ToolItem*> _toolList;		// ����

	vector<int*> _itemNum;				//������ ����

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
