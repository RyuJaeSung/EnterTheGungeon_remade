#include "stdafx.h"
#include "ClineBullet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"


ClineBullet::ClineBullet()
	:Dir(0)
{
}


ClineBullet::~ClineBullet()
{
}

void ClineBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/MonsterBullet.bmp", L"MonsterBullet");
	m_Info.size.cx = 16;
	m_Info.size.cy = 18;

	m_Speed = 5.f;


	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().x <= m_Info.x)
		Dir = -1;
	else
		Dir = 1;
}

void ClineBullet::Update()
{
	m_Info.x += (m_Speed * Dir);

	Update_Rect();
}

void ClineBullet::Last_Upate()
{
}

void ClineBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"MonsterBullet");
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Info.x + ScrollX), (int)(m_Info.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
}

void ClineBullet::Release()
{
}
