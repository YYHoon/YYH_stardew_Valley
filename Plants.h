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
	virtual	void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;

	void ChangeIsWet(bool isWet) { _isWet = isWet; }
	void IncreaseGrowCount(int increase) { _growCount += increase; }
	void SavePosIndex(int saveIndex) { _tileIndex = saveIndex; }

	bool GetIsWet() { return _isWet; }
	bool GetCanHarvest() { return _isCanHarvest; }
	int GetSaveIndex() { return _tileIndex; }
};

