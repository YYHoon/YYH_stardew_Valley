#pragma once
#include "gameNode.h"

class Inventory;

struct tagCrafting
{
	image* Image;
	image* ImageBefore;
	int x, y;
};

class Crafting : public gameNode
{
private:
	tagCrafting _craftItem;
	tagCrafting _craftItem1;
	tagCrafting _craftItem2;

	Inventory* _inventory;

public:
	Crafting() {};
	~Crafting() {};

	HRESULT init();
	void release();
	void update();
	void render();

};
