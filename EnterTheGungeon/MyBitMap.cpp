#include "stdafx.h"
#include "MyBitMap.h"


CMyBitMap::CMyBitMap()
{
}


CMyBitMap::~CMyBitMap()
{
	Release();
}

void CMyBitMap::Load_Bmp(const TCHAR * FilePath)
{
	HDC DC = GetDC(m_ghWnd);
	BmpDC = CreateCompatibleDC(DC);
	ReleaseDC(m_ghWnd,DC);

	BitMap = (HBITMAP)LoadImage(NULL, FilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	OldMap = (HBITMAP)SelectObject(BmpDC, BitMap);

}

void CMyBitMap::Release()
{
	SelectObject(BmpDC, OldMap);
	DeleteObject(BitMap);
	DeleteDC(BmpDC);
}
