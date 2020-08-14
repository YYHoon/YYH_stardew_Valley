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
	int _alphaValue;			//���İ�

	/// ���� ���ӿ����� �ð� ����(%)
	float _originalTime = 860;			//���� ������ �� �ð�
	float _originalDelay = 7.96296f;	//���� ������ �� ƽ�� �ð�
	float _ratio;						//�ð� �� ĭ �ۼ�Ʈ
	/// </summary>

	float _clockCalculate;		//�ð� ���
	float _currentTimeSec;		//���� �ð�

	float _elapsedTime;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

	bool _isInventoryOpen;		//�κ��丮�� ������

	tagClockHand _clockHand;	//�ð�ħ struct

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

	int GetCluckValue() { return _clockHand.value; }		//�ð� ��
};

