#pragma once
#ifndef __MYBITMAP_H__
#define __MYBITMAP_H__

class CMyBitMap
{
public:
	CMyBitMap();
	~CMyBitMap();

public:
	inline HDC	Get_BmpDC() { return BmpDC; }
	void Load_Bmp(const TCHAR* FilePath);
	void Release();

private:
	HDC		BmpDC;
	HBITMAP	BitMap;
	HBITMAP	OldMap;
};


#endif // !__MYBITMAP_H__
