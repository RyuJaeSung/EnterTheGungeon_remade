#include "stdafx.h"
#include "BossBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBossBullet::CBossBullet()
{
}


CBossBullet::~CBossBullet()
{
}

void CBossBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/MonsterBullet.bmp", L"BossBullet");

	m_Info.size.cx = 16;
	m_Info.size.cy = 18;
	m_Ability.Attack = 1;
	m_Speed = 3.f;

}

void CBossBullet::Update()
{
	m_Info.x += cosf(m_fAngle * PI / 180.f) * m_Speed;
	m_Info.y -= sinf(m_fAngle  * PI / 180.f) * m_Speed;
	Frame_Move();
	Update_Rect();
}

void CBossBullet::Last_Upate()
{
}

void CBossBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BossBullet");
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
}

void CBossBullet::Release()
{
}