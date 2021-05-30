#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/NomalBullet.bmp", L"NomalBullet");
	m_Info.size.cx = 20;
	m_Info.size.cy = 20;
	CSoundMgr::Get_Instance()->PlaySound(L"Basics.wav", CSoundMgr::PLAYER);
	m_Ability.Attack = 999;
	m_Speed = 10.f;
}

void CBullet::Update()
{
	m_Info.x += cosf((-m_fAngle) * PI / 180.f) * m_Speed;
	m_Info.y -= sinf((-m_fAngle) * PI / 180.f) * m_Speed;

	Update_Rect();
}

void CBullet::Last_Upate()
{
}

void CBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"NomalBullet");
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();


	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
}

void CBullet::Release()
{
}
