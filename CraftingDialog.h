#pragma once
#include "gameNode.h"
#include <string>


class CraftingDialog : public gameNode
{
private:
	image* _CrDiaWindow; //이미지
	RECT _CrDiaRc; //문자들 좌표용
	bool _SeeStrin; //BoInDa AnBoInDa

public:
	CraftingDialog() {};
	~CraftingDialog() {};

	virtual HRESULT init();
	virtual void release();
	virtual void TxtOutPut(string itemName);  //랜더물린다.

	bool getSeeStrin() { return _SeeStrin; }
	void setSeeStrin(bool set) { _SeeStrin = set; }
};