#include "stdafx.h"
#include "ShotBullet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"


CShotBullet::CShotBullet()
	:Direction(false)
{
}


CShotBullet::~CShotBullet()
{
}

void CShotBullet::BulletPosX()
{
	m_Info.x += cosf(-m_fAngle * PI / 180.f) * m_Speed;
	m_Info.y -= sinf(-m_fAngle * PI / 180.f) * m_Speed;
}

void CShotBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/MonsterBullet.bmp", L"MonsterBullet");

	m_Info.size.cx = 16;
	m_Info.size.cy = 18;
	m_Ability.Attack = 1;
	m_Speed = 3.f;

}

void CShotBullet::Update()
{
	
	BulletPosX();
	Frame_Move();
	Update_Rect();
}

void CShotBullet::Last_Upate()
{
}

void CShotBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"MonsterBullet");
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
}



void CShotBullet::Release()
{
}
