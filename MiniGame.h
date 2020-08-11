#pragma once





class MiniGame

{
private:
	bool _fishFloatMove = false; //����������̴���
	bool _isPlay = false;	//����������
	Vector2 _gauge;			//�����󸶳���ư����� ������
	Vector2 _fishingUI;		//������UIǥ������ǥ(left,top)
	Vector2 _fishingHitBox;	//�������Ʈ�ڽ�
	Vector2 _playerCenter;	//�÷��̾� ���� ���� ����
	PLAYER_DIRECTION _dir;	//�÷��̾� ���¹��� ����
	int _clickTime=0;			//�Ŀ������� Ŭ���ð��޴º���
	int _power=0;				//�� ������ŭ � ���ư�
	Vector2 _fishfloat;		//��������ǥ

public:

	void InitKeyDown(PLAYER_DIRECTION dir, Vector2 center);
	void InitKeyUp();
	void FishFloatUpdate();
	void Update();
	void Render();


};

