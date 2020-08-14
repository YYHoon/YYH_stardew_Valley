#pragma once
#include "gameNode.h"
#include <string>
#include <vector>
//������ �ι��丮�� �����Ѵ�~


class Store : public gameNode
{
private:

	image* _StoreWindow;	  //����â
	image* _StorePortrait;	  //���������ʻ�ȭ
	image* _StoreItem[4];	  //���� ������
	image* _StoreInfo;		  //�����Ұ���â
	image* _StoreNPC;		  //����npc��Ʈ
	
	image* _StoreUpArrow;	  //������������ ���ǰ��� ����ȭ��ǥ
	image* _StoreDownArrow;   //������������ ���ǰ��� �Ʒ���ȭ��ǥ

	vector<RECT> _Item;	     //�������ڵ�(4��)
	RECT _CloseRc;			 //�ݱ��ư
	RECT _StoreNpcRect;		 //npc�̹����������
	RECT _StoreNpcOpen;		 //�̿��� �������� ����� Ȱ��ȭ��ų������(����)

	RECT _StoreUpArrowRc;	 //������������ ���ǰ��� ����ȭ��ǥ �浹ó����
	RECT _StoreDownArrowRc;	 //������������ ���ǰ��� �Ʒ���ȭ��ǥ �浹ó����

	int _StoreItmeFrameY;	//������ǰ���ý�����
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;

	int _StoreSearchMin;
	int _StoreSearchMax;

public:
	Store();
	~Store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void OpenStoreRender();
	virtual void draw();

	RECT getStoreNpcRect() {return _StoreNpcRect; }
	RECT getStoreNpcOpen() {return _StoreNpcOpen; }
};