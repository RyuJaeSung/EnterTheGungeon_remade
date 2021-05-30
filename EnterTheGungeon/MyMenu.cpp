#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "MyFont.h"
#include "SoundMgr.h"

CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
}


void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Menu.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Gun/Basics.bmp", L"Gun");
	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.wav");
	Font = new CMyFont;
	Font->Initialize();
}

void CMyMenu::Update()
{
	Font->Update();
}

void CMyMenu::Late_Update()
{
	Font->Late_Update();
}

void CMyMenu::Render(HDC DC)
{
	HDC gun = CBmpMgr::Get_Instance()->Find_Bmp(L"Gun");
	GetClientRect(m_ghWnd, &Client_Rect);
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Menu");
	StretchBlt(DC, 0, 0, Client_Rect.right, Client_Rect.bottom + 100, BmpDC, 0, 0, 1000, 600, SRCCOPY);
	Font->Render(DC);


	GdiTransparentBlt(DC,Client_Rect.right, Client_Rect.bottom, 30, 30 ,
		gun, 0, 0, 15, 15, RGB(255, 255, 255));

}

void CMyMenu::Release()
{
	SAFE_DELETE(Font);
}
