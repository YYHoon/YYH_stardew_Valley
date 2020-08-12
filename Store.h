#pragma once
#include "gameNode.h"
#include <string>
#include <vector>

struct tagStoreTsetItem //�׽�Ʈ���Դϴ�.
{
	image* img;				//������ �̹���
	RECT rc;				//������ ��Ʈ
	string name;			//������ �̸�
	string description;		//������ ����
	int price;				//������ ����
};

class Store : public gameNode
{
private:
	vector<tagStoreTsetItem>			_vStoreItem;	//��������?
	vector<tagStoreTsetItem>::iterator	_viStoreItem;

	image* _StoreWindow;	  //����â
	image* _StorePortrait;	  //���������ʻ�ȭ
	image* _StoreItem[20];	  //���� ������
	image* _StoreInfo;		  //�����Ұ���â
	image* _StoreNPC;		  //����npc��Ʈ�̹���

	image* _CloseButton;      //�ݱ��ư
	image* _BlackWindow;      //���ĸ��ϰ�
	
	vector<RECT> _Item;	     //��������
	RECT _CloseRc;			 //�ݱ��ư
	RECT _StoreNpcRect;		 //npc�̹����������
	RECT _StoreNpcOpen;		 //�̿��� �������� ����� Ȱ��ȭ��ų������(����)


	int _StoreItmeFrameY; //������ǰ���ý�����
	int _StoreItmeFrameY2;
	int _StoreItmeFrameY3;
	int _StoreItmeFrameY4;

public:
	Store();
	~Store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};