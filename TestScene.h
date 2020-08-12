#pragma once
#include "gameNode.h"
#include "Inventory.h"
#include "Environment.h"
#include <string>
#include <fstream>	//��������� �Ҷ� �ʿ�
#include <vector>
#include <queue>

class TestScene : public gameNode
{
private:
	image* _Mouse; //���콺 �̹��� ->������ �ѹ����� �̹��� �����ֽð� ������ ��ǥ�� _ptmouseX, _ptmouseY  ���ֻ���
	Inventory* _inv;

	image* _StoreWindow;	 //����â
	image* _StorePortrait;	//���������ʻ�ȭ
	image* _StoreItem[4];		//���� ������
	image* _StoreInfo;		//�����Ұ���â
	image* _StoreNPC;      //����npc��Ʈ�̹���

	image* _CloseButton;     //�ݱ��ư
	image* _BlackWindow;     //���ĸ��ϰ�

	RECT _CloseRc;			 //�ݱ��ư
	RECT _StoreNpcRect;		 //npc�̹����������
	RECT _StoreNpcOpen;		 //�̿��� �������� ����� Ȱ��ȭ��ų������(����)
	vector<RECT> _Item;

	int _StoreItmeFrameY; //������ǰ���ý�����
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;

	bool _StoreOpen;  //����

//-------------------------���̾�α�_����--------------------------------

	image* _ChatWindow;      	 //��ȭâ �̹���
	image* _TalkingNpcImage;     //��ȭ����NPC ��Ʈ�̹���
	image* _TalkingNpcPortrait;  //��ȭ����NPC �ʻ�ȭ
	image* _TalkingXBox;		 //��ȭâ �����ϴܿ� �ִ°� ���ٸ� ȿ������

	/// <summary>
	Inventory* _Inv;
	Environment* _env;
	/// </summary>

	RECT _TalkingNpcImageRc; //��ȭ��NPC �̹�����
	RECT _TalkingNpc;	     //��ȭ��NPC ��ȭ���ɿ���

	vector<string> _txtInTest;    //txt���ϸ��� ��´�
	string _txtOutTest;		 //������ 1���ھ� �޾ƿͼ� �����ִ� ����
	RECT _TxtBoxRC;	     //���ڰ� �ѷ��� ��ġ

	bool _Talking;			 //��ȭ�� �ϴ����ΰ�
	int _stringNum;			 //strin.~.at()���� ���~


	RECT _TestP;	  //�׽�Ʈ�����
	int _mouseIndex;  //���콺 �̹��� ������

public:
	TestScene();
	~TestScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Draw();

};