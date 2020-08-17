#pragma once
#include "gameNode.h"

struct tagClockHand
{
	POINT center;		//����
	POINT end;			//�ð�ħ ����
	int length;			//�ð�ħ ����
	float angle;		//�ð�ħ ����
	int count;			//�ð� ī��Ʈ
	int value;			//�ð� ��(���� �ð�ħ�� ��ġ)
};

class Environment : public gameNode
{
private:
	tagClockHand _clockHand;	//�ð�ħ struct

	int _alphaValue;			//���İ�

	int _dayCount;				//��¥
	float _timeRatio;			//�ð� �� ĭ �ۼ�Ʈ

	float _clockCalculate;		//�ð� ���

	float _elapsedTime;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

	bool _isInventoryOpen;		//�κ��丮�� ������
	bool _isDayIncrease;		//��¥�� �����ϸ�

	int _alphaDelay;

	float _delay;
	float _count;

	bool timeUpdate(const float count)
	{
		_count += count;
		if (_count >= _delay)
		{
			_count -= _delay;
			return true;
		}
		return false;
	}

public:
	Environment() {};
	~Environment() {};

	HRESULT init();
	void release();
	void update();
	void render();

	int GetCluckValue() { return _clockHand.value; }				//�ð� ��
	int GetDayCount() { return _dayCount; }							//��¥ ��
	bool GetIsDayIncrease() { return _isDayIncrease; }				//��¥�� �����ϸ�
	bool GetIsInventoryOpen() { return _isInventoryOpen; }			//�κ��丮�� ������

	void SetIsInventoryOpen(bool open) { _isInventoryOpen = open; }	//�κ��丮��
};

