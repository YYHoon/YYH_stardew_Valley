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

	/// ���� ���ӿ����� �ð� ����(Percentage)
	float _originalTime = 860;
	float _originalDelay = 7.96296f;
	float _originalRatio;
	/// </summary>

	float _clockCalculate;		//�ð� ���
	float _currentTimeSec;		//���� �ð�

	float _elapsedTime;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

	bool _isGamePause;			//���� �ð��� ���ư���

	tagClockHand _clockHand;	//�ð�ħ struct
	int _clockValue;			//�ð� ��(���� �ð�ħ�� ��ġ)


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
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

