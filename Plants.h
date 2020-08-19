#pragma once
#include "GameObject.h"

class Plants : public GameObject
{
protected:
	bool _isWet;
	bool _isCanHarvest;
	int _growCount;
	int _tileIndex;
public:
	void Init();
	void Release();
	void Update();

	void ChangeIsWet(bool isWet) { _isWet = isWet; }
	void IncreaseGrowCount(int increase) { _growCount += increase; }
	void SavePosIndex(int saveIndex) { _tileIndex = saveIndex; }
	void SetImgToString(string name) {_img = IMAGEMANAGER->findImage(name); }
	void SetCanHarvest(bool can) { _isCanHarvest = can; }
	bool GetIsWet() { return _isWet; }
	bool GetCanHarvest() { return _isCanHarvest; }
	int GetSaveIndex() { return _tileIndex; }
	int GetGrowCount() { return _growCount; }
};

