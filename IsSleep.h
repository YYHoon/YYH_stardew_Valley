#pragma once
#include "gameNode.h"
class IsSleep : public gameNode
{
private:
	image* _sleepSlect; //선택이미지
	image* _black; //잠때는 검은화면~

	RECT _isSleepYesRc;  //잘거야 선택
	RECT _non;			//아직이다

	int _alp; //알파값

	bool _isSleep;  //잠든다 선택시 사용
	bool _isSelectOpen;


public:
	IsSleep() {};
	~IsSleep() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool getIsSelectOpen() { return _isSelectOpen; }
	virtual void setIsSelectOpen(bool open) { _isSelectOpen = open; }
};