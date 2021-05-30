#include "stdafx.h"
#include "AKBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"



CAKBullet::CAKBullet()
{
}


CAKBullet::~CAKBullet()
{
}

void CAKBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/AKBullet.bmp", L"AKBullet");
	m_Info.size.cx = 3;
	m_Info.size.cy = 10;

	m_Ability.Attack = 15;
	m_Speed = 15.f;
}

void CAKBullet::Update()
{
	m_Info.x += cosf((-m_fAngle) * PI / 180.f) * m_Speed;
	m_Info.y -= sinf((-m_fAngle) * PI / 180.f) * m_Speed;

	Update_Rect();
}

void CAKBullet::Last_Upate()
{
}

void CAKBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"AKBullet");
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();


	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
}

void CAKBullet::Release()
{
}
