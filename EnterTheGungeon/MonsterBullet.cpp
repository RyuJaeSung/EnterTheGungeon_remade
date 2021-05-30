#include "stdafx.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "MonsterBullet.h"


CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}

void CMonsterBullet::TargetPos()
{
	float PlayerPosX = CObjMgr::Get_Instance()->Set_Player()->Get_Info().x;
	float PlayerPosY = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y;

	m_fAngle = atan2f((PlayerPosY - m_Info.y), (PlayerPosX - m_Info.x)) * 180 / PI;
	TargetAngle = false;
}

void CMonsterBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Bullet/MonsterBullet.bmp", L"MonsterBullet");
	m_Info.size.cx = 16;
	m_Info.size.cy = 18;
	
	TargetAngle = true;
	m_Ability.Attack = 1;
	m_Speed = 3.f;
}

void CMonsterBullet::Update()
{
	if(TargetAngle)
		TargetPos();

	m_Info.x += cosf((-m_fAngle) * PI / 180.f) * m_Speed;
	m_Info.y -= sinf((-m_fAngle) * PI / 180.f) * m_Speed;

	Update_Rect();
}

void CMonsterBullet::Last_Upate()
{
}

void CMonsterBullet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"MonsterBullet");
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Info.x + ScrollX), (int)(m_Info.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));

}

void CMonsterBullet::Release()
{
}
