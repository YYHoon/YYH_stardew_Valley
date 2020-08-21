#pragma once
#include "gameNode.h"

class ToolItem;

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

	ToolItem* _toolItem;

public:
	Crafting() {};
	~Crafting() {};

	HRESULT init();
	void release();
	void update();
	void render();

	bool GetGrilledFishIsPossible() { return _grilledFish.isPossible; }
	bool GetRawFishIsPossible() { return _rawFish.isPossible; }
	bool GetSaladIsPossible() { return _salad.isPossible; }

	void SetGrilledFishIsPossible(bool set) { _grilledFish.isPossible = set; }
	void SetRawFishIsPossible(bool set) { _rawFish.isPossible = set; }
	void SetSaladIsPossible(bool set) { _salad.isPossible = set; }
};
