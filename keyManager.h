#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _KeyPast;
	bitset<KEYMAX> _keyCurrent;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void update();

	void release();
	//키를 한 번 누르면
	bool isOnceKeyDown(const int& key);
	//키를 눌렀다가 떼면
	bool isOnceKeyUp(const int& key);
	//키를 계속 누르고 있으면
	bool isStayKeyDown(const int& key);
	//키가 토글되면(?) 캡스롹 생각해라
	bool isToggleKey(const int& key);

};

