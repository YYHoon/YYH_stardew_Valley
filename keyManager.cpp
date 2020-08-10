#include "stdafx.h"
#include "keyManager.h"

keyManager::keyManager()
{
}

keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	_KeyPast.reset();
	_keyCurrent.reset();

	return S_OK;
}

void keyManager::update()
{
	_KeyPast = _keyCurrent;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_KeyPast[key])
		{
			_keyCurrent.set(key, true);

			return true;
		}
	}
	else _keyCurrent.set(key, false);

	return false;
}

bool keyManager::isOnceKeyUp(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000) _keyCurrent.set(key, true);
	else
	{
		if (_KeyPast[key])
		{
			_keyCurrent.set(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(const int& key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
