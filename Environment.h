#pragma once

struct tagClockHand
{
	POINT center;		//����
	POINT end;			//�ð�ħ ����
	int length;			//�ð�ħ ����
	float angle;		//�ð�ħ ����
	int count;			//�ð� ī��Ʈ
	int value;			//�ð� ��(���� �ð�ħ�� ��ġ)
};

class Environment : public singletonBase<Environment>
{
private:
	Environment() {};

	tagClockHand _clockHand;	//�ð�ħ struct

	int _alphaValue;			//���İ�

	int _dayCount;				//��¥
	float _timeRatio;			//�ð� �� ĭ �ۼ�Ʈ

	float _clockCalculate;		//�ð� ���

	float _elapsedTime;			//����� �ð�
	float _realTimeSecond;		//���ǽð�(��)

	bool _isInventoryOpen;		//�κ��丮�� ������
	bool _isDayIncrease;		//��¥�� �����ϸ�

	float _delay;
	float _count;

	float _test;
	float _test1;

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
	~Environment() {};

	HRESULT init();
	void release();
	void update();
	void render(HDC _hdc);

	static Environment* GetInstance()
	{
		static Environment* _env;
		if (!_env)
		{
			_env = new Environment;
			return _env;
		}
		else return _env;
	}

	int GetCluckValue() { return _clockHand.value; }				//�ð� ��
	int GetDayCount() { return _dayCount; }							//��¥ ��
	bool GetIsDayIncrease() { return _isDayIncrease; }				//��¥�� �����ϸ�
	bool GetIsInventoryOpen() { return _isInventoryOpen; }			//�κ��丮�� ������

	void SetIsInventoryOpen(bool open) { _isInventoryOpen = open; }	//�κ��丮��
};

