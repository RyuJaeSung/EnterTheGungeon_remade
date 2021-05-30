#pragma once
#ifndef __BMPMGR_H__
#define __BMPMGR_H__

class CMyBitMap;
class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void Insect_Bmp(const TCHAR* FilePath, const TCHAR* ImageKey);
	HDC	Find_Bmp(const TCHAR* ImageKey);
	void Release();

public:
	inline static CBmpMgr* Get_Instance()
	{
		if (!Instance)
			Instance = new CBmpMgr;
		return Instance;
	}
	inline static void Destroy_Instance()
	{
		SAFE_DELETE(Instance);
	}

private:
	static CBmpMgr*					Instance;
	map<const TCHAR*, CMyBitMap*>	BmpMap;
};


#endif // !__BMPMGR_H__