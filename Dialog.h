#pragma once
#include "gameNode.h"
#include <string>
#include <fstream>
#include <vector>
#include <queue>

class Dialog : public gameNode
{
private:
	int _stringNum; //strin.~.at()�� ���

	image* _infoHealBox;	//ȸ�������� �϶�
	image* _infoBox;		//������ �϶�

	vector<string> _txtInTest;    //txt���ϸ��� ��´�(����)

	queue<string> _txtInqueue;	 //txt���ϸ��� ���(ť)

	string _txtOutTest;		    //������ 1���ھ� �޾ƿͼ� �����ִ� ����
	RECT _TxtBoxRC;			   //���ڰ� �ѷ��� ��ǥ

	bool _stringInfo;          //�������� �ǹ��̴�.

public:
	Dialog();
	~Dialog();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};