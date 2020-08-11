#pragma once
#include "gameNode.h"

class Environment : public gameNode
{
private:
	int _alphaValue;			//���İ�
	int _alphaCount;			//���ķ��� �ӵ� ����

	float _timeCount;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

public:
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

