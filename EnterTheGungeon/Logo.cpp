#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
}

void CLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Logo.bmp", L"Logo");
	OneselfScene = GetTickCount();
}

void CLogo::Update()
{
}

void CLogo::Late_Update()
{
	if (OneselfScene + 3000 < GetTickCount())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_MENU);
		return;

	}
}

void CLogo::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Logo");

	StretchBlt(DC, 0, 0, Client_Rect.right , Client_Rect.bottom + 100, BmpDC, 0, 0, 800, 600, SRCCOPY);

}

void CLogo::Release()
{
}
