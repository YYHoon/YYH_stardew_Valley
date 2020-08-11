#pragma once
#include "gameNode.h"
#include "Environment.h"
#include "Inventory.h"
#include <vector>

class TestScene : public gameNode
{
private:
	image* _Mouse; //���콺 �̹��� �̰� ����� �������

	image* _StoreWindow;	 //����â
	image* _StorePortrait;	//���������ʻ�ȭ
	image* _StoreItem;		//���� ������
	image* _StoreInfo;		//�����Ұ���â
	image* _StoreNPC;      //����npc��Ʈ�̹���

	image* _CloseButton;     //�ݱ��ư
	image* _BlackWindow;     //���ĸ��ϰ�

	RECT _StoreItemRc[20];   //���� ������������ǥ �� �浹ó����
	RECT _CloseRc;			 //�ݱ��ư
	RECT _StoreNpcRect;		 //npc�̹����������
	RECT _StoreNpcOpen;		 //�̿��� �������� ����� Ȱ��ȭ��ų������(����)

	int _StoreItmeFrameY; //������ǰ���ý�����

	image* _ChatWindow;      	 //��ȭâ �̹���
	image* _TalkingNpcImage;     //��ȭ����NPC ��Ʈ�̹���
	image* _TalkingNpcPortrait;  //��ȭ����NPC �ʻ�ȭ
	image* _TalkingXBox;		 //��ȭâ �����ϴܿ� �ִ°� ���ٸ� ȿ������
	animation* _TalkingXBoxAni;

	/// <summary>
	Inventory* _Inv;
	Environment* _env;
	/// </summary>

	RECT _TalkingNpcImageRc; //��ȭ��NPC �̹�����
	RECT _TalkingNpc;	     //��ȭ��NPC ��ȭ���ɿ���

	vector<string> _Test;   //txt���ϸ��� ��´�
	string _TextOut;		//������ 1���ھ� �޾ƿͼ� �����ִ� ����
	RECT _TestBoxRC;	    //���ڰ� �ѷ��� ��ġ

	RECT _TestP; //�׽�Ʈ�����

	bool _StoreOpen;  //����
	bool _Toking;	  //��ȭ

	int _stringNum;	  //strin.~.at()���� ���~

	int _mouseIndex;  //���콺 �̹��� ������

public:
	TestScene();
	~TestScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};