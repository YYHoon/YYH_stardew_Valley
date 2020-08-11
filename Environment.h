#pragma once
#include "gameNode.h"

struct tagClockHand
{
	POINT center;	//����
	POINT End;		//�ð�ħ ����
	int length;		//�ð�ħ ����
	float angle;	//�ð�ħ ����
};

class Environment : public gameNode
{
private:
	int _alphaValue;			//���İ�
	int _alphaCount;			//���ķ��� �ӵ� ����

	float _clockCalculrate;		//������

	float _elapsedTime;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

	bool _inGameTimeRunning;

	tagClockHand _clockHand;
	int _clockCount;			//�ð��� ī��Ʈ
	int _clockValue;			//�ð� ��(���� �ð�ħ�� ��ġ)

public:
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

