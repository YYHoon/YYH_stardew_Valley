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
<<<<<<< HEAD
	void Init();
	void Release();
	void Update();
=======
	virtual	void Init();
	virtual void Release() ;
	virtual void Update() ;
>>>>>>> f6c703d3e25527c3dc880078fe28dab36e36e1d3

	void ChangeIsWet(bool isWet) { _isWet = isWet; }
	void IncreaseGrowCount(int increase) { _growCount += increase; }
	void SavePosIndex(int saveIndex) { _tileIndex = saveIndex; }
	void SetImgToString(string name) {_img = IMAGEMANAGER->findImage(name); }

	bool GetIsWet() { return _isWet; }
	bool GetCanHarvest() { return _isCanHarvest; }
	int GetSaveIndex() { return _tileIndex; }
	int GetGrowCount() { return _growCount; }
};

