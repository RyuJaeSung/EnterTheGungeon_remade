#pragma once
#ifndef __KEYMGR_H__
#define __KEYMGR_H__
#define VK_MAX 0xFF

class CKeyMgr
{
public:
	CKeyMgr();
	~CKeyMgr();
	
public:
	bool Key_Down(int key);
	bool Key_Up(int key);
	bool Key_Pressing(int key);
	void Key_Update();

public:
	inline static CKeyMgr* Get_Instane()
	{
		if (!Instance)
			Instance = new CKeyMgr;
		return Instance;
	}
	inline static void Destroy_Instance()
	{
		SAFE_DELETE(Instance);
	}

private:
	static	CKeyMgr*	Instance;
	bool				keyState[VK_MAX];
};


#endif // !__KEYMGR_H__