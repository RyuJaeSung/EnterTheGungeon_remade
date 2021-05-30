#include "stdafx.h"
#include "BmpMgr.h"
#include "MyBitMap.h"

CBmpMgr* CBmpMgr::Instance = nullptr;
CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
}

void CBmpMgr::Insect_Bmp(const TCHAR * FilePath, const TCHAR * ImageKey)
{
	auto iter = find_if(BmpMap.begin(), BmpMap.end(), CStrCmp(ImageKey));
	
	if (BmpMap.end() == iter)
	{
		CMyBitMap* Bmp = new CMyBitMap;
		Bmp->Load_Bmp(FilePath);

		BmpMap.emplace(ImageKey, Bmp);
	}
}

HDC CBmpMgr::Find_Bmp(const TCHAR * ImageKey)
{

	auto iter = find_if(BmpMap.begin(), BmpMap.end(), CStrCmp(ImageKey));

	if (BmpMap.end() == iter)
		return nullptr;

	return iter->second->Get_BmpDC();
}

void CBmpMgr::Release()
{
}
