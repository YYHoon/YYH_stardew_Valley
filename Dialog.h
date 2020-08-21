#pragma once
#include "gameNode.h"
#include <string>
#include <fstream>
#include <vector>
#include <queue>

class Dialog : public gameNode
{
private:
	int _stringNum; //strin.~.at()에 사용

	image* _infoHealBox;	//회복아이템 일때
	image* _infoBox;		//아이템 일때

	vector<string> _vInfoTxtInPut;    //txt파일만을 담는다(백터)

	queue<string> _qInfoTxtInPut;	 //txt파일만을 담는(큐)

	string _infoTxtOutPut;		    //위에서 1글자씩 받아와서 보여주는 아이
	RECT _TxtBoxRC;			   //문자가 뿌려질 좌표

	bool _stringClear;          //쓰일지는 의문이다.

public:
	Dialog() {};
	~Dialog() {};

	void setDialogClear(bool set) { _stringClear = set; }

	virtual HRESULT init();
	virtual void release();
	virtual void update(string itemName);
	virtual void render();
};