#include "stdafx.h"
#include "UiMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "NomalGun.h"
#include "ScrollMgr.h"

CUiMgr* CUiMgr::Instance = nullptr;
CUiMgr::CUiMgr()
{
}


CUiMgr::~CUiMgr()
{
}

void CUiMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/UI.bmp", L"UI");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/Bulletui.bmp", L"BulletUI");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/MyWeapon.bmp", L"Weapon");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Big.bmp", L"Back3");

	MaxMagazine = 6;
}

void CUiMgr::Update()
{
	Hp = CObjMgr::Get_Instance()->Get_AbilityInfo().Hp;
	MaxHp = CObjMgr::Get_Instance()->Get_AbilityInfo().MaxHp;
	shield = CObjMgr::Get_Instance()->Get_AbilityInfo().Shield;
	MaxMagazine = static_cast<CNomalGun*>(CObjMgr::Get_Instance()->Set_Obj(OBJ::GUN))->Set_Magazine();
}

void CUiMgr::Late_Update()
{
}

void CUiMgr::Render(HDC DC)
{
	HpRender(DC);
	MagazineRender(DC);
}

void CUiMgr::Release()
{
}

void CUiMgr::HpRender(HDC DC)
{
	int HpBar = MaxHp - Hp;
	int Heart = 0;
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"UI");
	HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back3");

	for (int i = 0; i < Hp / 2; ++i)
	{
		BitBlt(BackDC, (19 * Heart), 0, 19, 12, BmpDC, 0, 0, SRCCOPY);
		++Heart;
	}
	for (int i = 0; i < HpBar % 2; ++i)
	{
		BitBlt(BackDC, (19 * Heart), 0, 19, 12, BmpDC, 19, 0, SRCCOPY);
		++Heart;
	}
	for (int i = 0; i < HpBar / 2; ++i)
	{
		BitBlt(BackDC, (19 * Heart), 0, 19, 12, BmpDC, 38, 0, SRCCOPY);
		++Heart;
	}

	GdiTransparentBlt(DC, 10, 10, 200, 50,
		BackDC, 0, 0, (19 * (MaxHp / 2)), 12, RGB(255, 255, 255));
}

void CUiMgr::MagazineRender(HDC DC)
{
	GetClientRect(m_ghWnd, &Client_Rect);
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BulletUI");
	HDC WeaponDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Weapon");


	GdiTransparentBlt(DC, Client_Rect.right - 30 , Client_Rect.bottom - 20, 20, 10,
		BmpDC, 0, 0, 7, 4, RGB(255, 255, 255));
	GdiTransparentBlt(DC, Client_Rect.right - 30 , Client_Rect.bottom - ( 30 + (10 * MaxMagazine)), 20, 10,
		BmpDC, 0, 4, 7, 8, RGB(255, 255, 255));
	GdiTransparentBlt(DC, Client_Rect.right - 120, Client_Rect.bottom - 80, 80, 70, WeaponDC, 0, 0, 20, 20, RGB(255, 255, 255));

	for (int i = 0; i < MaxMagazine; ++i)
		Rectangle(DC, Client_Rect.right - 30, Client_Rect.bottom - 20 - ((i + 1) * 10), Client_Rect.right - 10, Client_Rect.bottom - 20 -(i * 10));

	//RoundRect(DC, Client_Rect.right - 120, Client_Rect.bottom - 80, Client_Rect.right - 40, Client_Rect.bottom - 10, 20, 20);

}
