#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	inline float Get_ScrollX() { return ScrollPos.fX; }
	inline float Get_ScrollY() { return ScrollPos.fY; }

public:
	inline void Set_ScrollX(float x) { ScrollPos.fX += x; }
	inline void Set_ScrollY(float y) { ScrollPos.fY += y; }
	inline void Set_Scroll(float x, float y) { ScrollPos.fX = x; ScrollPos.fY = y; }

public:
	inline static CScrollMgr* Get_Instance()
	{
		if (!Instance)
			Instance = new CScrollMgr;
		return Instance;
	}
	inline static void Destroy_Instance()
	{
		SAFE_DELETE(Instance);
	}
private:
	static CScrollMgr*	Instance;
	POS					ScrollPos;
};


#endif // !__SCROLLMGR_H__
