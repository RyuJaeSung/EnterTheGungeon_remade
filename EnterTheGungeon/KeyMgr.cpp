#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::Instance = nullptr;
CKeyMgr::CKeyMgr()
{
	ZeroMemory(&keyState, sizeof(keyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Down(int key)
{
	if (!keyState[key] && (GetAsyncKeyState(key) & 0x8000))
	{
		keyState[key] = !keyState[key];
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Up(int key)
{
	if (!keyState[key] && !(GetAsyncKeyState(key) & 0x8000))
	{
		keyState[key] = !keyState[key];
		return true;
	}
	return false;
}

bool CKeyMgr::Key_Pressing(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	return false;
}

void CKeyMgr::Key_Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (keyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			keyState[i] = !keyState[i];
		if(!keyState[i] && (GetAsyncKeyState(i) & 0x8000))
			keyState[i] = !keyState[i];
	}
}
