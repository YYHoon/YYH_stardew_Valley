#pragma once
#include "gameNode.h"
class IsSleep : public gameNode
{
private:
	image* _sleepSlect; //�����̹���

	RECT _isSleepYesRc;  //�߰ž� ����
	RECT _non;			//�����̴�
	
	bool _isSleep;  //���� ���ý� ���
	bool _isSelectOpen;

public:
	IsSleep() {};
	~IsSleep() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setIsSleep(bool sleep) { _isSleep = sleep; }
	virtual void setIsSelectOpen(bool open) { _isSelectOpen = open; }
};