#pragma once
#include "gameNode.h"
#include <string>
#include <vector>
//������ �ι��丮�� �����Ѵ�~

struct tagStoreTsetItem //�׽�Ʈ���Դϴ�. �����׽�Ʈ��
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
	vector<tagStoreTsetItem>			_vStoreItem;	//�����ǸŹ���~
	vector<tagStoreTsetItem>::iterator	_viStoreItem;

	image* _StoreWindow;	  //����â
	image* _StorePortrait;	  //���������ʻ�ȭ
	image* _StoreItem[4];	  //���� ������
	image* _StoreInfo;		  //�����Ұ���â
	image* _StoreNPC;		  //����npc��Ʈ�̹���

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
	virtual void OpenStoreRender();
	virtual void draw();

	RECT getStoreNpcRect() {return _StoreNpcRect; }
	RECT getStoreNpcOpen() {return _StoreNpcOpen; }

};