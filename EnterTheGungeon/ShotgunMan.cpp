#include "stdafx.h"
#include "ShotgunMan.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ShotBullet.h"
#include "Break_Check.h"
#include "ScrollMgr.h"

CShotgunMan::CShotgunMan()
	:NowMonsterPos(MONSTER::END), NewMonsterPos(MONSTER::END)
{
}

CShotgunMan::~CShotgunMan()
{
}

void CShotgunMan::Scene_Change()
{
	if (NowMonsterPos != NewMonsterPos)
	{
		switch (NewMonsterPos)
		{
		case MONSTER::LEFT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::RIGHT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 2;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::DEAD:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 9;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
		NowMonsterPos = NewMonsterPos;
	}
}

void CShotgunMan::MonsterPos()
{
	SetRect(&AttackRange, (int)(m_Info.x - 600), (int)(m_Info.y - 600), (int)(m_Info.x + 600), (int)(m_Info.y + 600));
	if (!CBreak_Check::RectRectCheck(&CObjMgr::Get_Instance()->Set_Player()->Get_RECT(), &AttackRange))
	{
		if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().x <= m_Info.x)
		{
			m_Info.x -= m_Speed;
			NewMonsterPos = MONSTER::LEFT;
		}
		if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().x >= m_Info.x)
		{
			m_Info.x += m_Speed;
			NewMonsterPos = MONSTER::RIGHT;
		}
	}
	else
		NewMonsterPos = MONSTER::IDLE;
}

void CShotgunMan::TargetPos()
{
	float PlayerPosX = CObjMgr::Get_Instance()->Set_Player()->Get_Info().x;
	float PlayerPosY = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y;

	m_fAngle = atan2f((PlayerPosY - m_Info.y), (PlayerPosX - m_Info.x)) * 180 / PI;
}

void CShotgunMan::Initialize()
{

	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/ShotgunMan.bmp", L"Shotgunman");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/ShotgunDead.bmp", L"SDead");
		
	m_Frame.FrameStart = 0;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameSpeed = 100;
	m_Frame.FrameTime = GetTickCount();
	AttackTime = GetTickCount();

	m_Info.size.cx = 60;
	m_Info.size.cy = 90;
	NewMonsterPos = MONSTER::LEFT;
	DeadorAlive = OBJ::ALIVE;
	m_Ability.Hp = 60;
	m_Speed = 2.f;
}

void CShotgunMan::Update()
{
	if (m_Ability.Hp <= 0)
	{
		NewMonsterPos = MONSTER::DEAD;

		if (m_Frame.FrameStart == m_Frame.FrameEnd - 1)
		{
			DeadorAlive = OBJ::DEAD;
			return;
		}
	}
	Scene_Change();
	MonsterPos();
	Frame_Move();
	Update_Rect();
}

void CShotgunMan::Last_Upate()
{
	if (AttackTime + 1000 < GetTickCount())
	{
		TargetPos();
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create(m_Info.x, m_Info.y, m_fAngle + 40));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create(m_Info.x, m_Info.y, m_fAngle +20));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create(m_Info.x, m_Info.y, m_fAngle));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create(m_Info.x, m_Info.y, m_fAngle - 20));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create(m_Info.x, m_Info.y, m_fAngle - 40));

		AttackTime = GetTickCount();
	}
}

void CShotgunMan::Render(HDC DC)
{

	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (NowMonsterPos == MONSTER::DEAD)
	{
		HDC DeadDC = CBmpMgr::Get_Instance()->Find_Bmp(L"SDead");
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			DeadDC, m_Frame.FrameStart * 25, 25, 25, 25, RGB(255, 255, 255));
	}
	else
	{
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Shotgunman");

		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			BmpDC, m_Frame.FrameStart * 20, m_Frame.FrameMotion * 30, 20, 30, RGB(255, 255, 255));
	}


}

void CShotgunMan::Release()
{
}
