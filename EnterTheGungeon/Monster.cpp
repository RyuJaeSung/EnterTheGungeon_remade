#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Break_Check.h"
#include "MonsterBullet.h"
#include "AbstractFactory.h"


CMonster::CMonster()
	:NowMonsterPos(MONSTER::END), NewMonsterPos(MONSTER::END)
{
	ZeroMemory(&AttackRange, sizeof(AttackRange));
}


CMonster::~CMonster()
{
}

void CMonster::Scene_Change()
{
	if (NewMonsterPos != NowMonsterPos)
	{
		switch (NewMonsterPos)
		{
		case MONSTER::LEFT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::RIGHT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameTime = GetTickCount();
			break;
		case MONSTER::DEAD:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 2;
			if (NowMonsterPos == MONSTER::IDLE || NowMonsterPos == MONSTER::LEFT)
				m_Frame.FrameMotion = 0;
			else
				m_Frame.FrameMotion = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
 		NowMonsterPos = NewMonsterPos;
	}
}

void CMonster::MonsterPos()
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


void CMonster::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/NomalLeft.bmp", L"Left");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/NomalRight.bmp", L"Right");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/NomalDead.bmp", L"NDead");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Big.bmp", L"NBack");

	m_Frame.FrameStart = 0;
	m_Frame.FrameEnd = 2;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameSpeed = 200;
	m_Frame.FrameTime = GetTickCount();
	AttackTime = GetTickCount();

	m_Info.size.cx = 60;
	m_Info.size.cy = 60;
	NewMonsterPos = MONSTER::LEFT;
	DeadorAlive = OBJ::ALIVE;
	m_Ability.Hp = 40;
	m_Speed = 2.f;
}

void CMonster::Update()
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

void CMonster::Last_Upate()
{

	if (AttackTime + 800 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CMonsterBullet>::Create(m_Info.x, m_Info.y));
		AttackTime = GetTickCount();
	}

}

void CMonster::Render(HDC DC)
{
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (NowMonsterPos == MONSTER::DEAD)
	{
		HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"NBack");
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"NDead");
		BitBlt(BackDC, 0, 0, 20, 20, BmpDC, m_Frame.FrameStart * 20, m_Frame.FrameMotion * 20, SRCCOPY);
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			BackDC, 0, 0, 20, 20, RGB(255, 255, 255));
	}
	if (NowMonsterPos == MONSTER::LEFT)
	{
		HDC	BmpDC_L = CBmpMgr::Get_Instance()->Find_Bmp(L"Left");
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			BmpDC_L, m_Frame.FrameStart * 16, m_Frame.FrameMotion * 26, 16, 26, RGB(255, 255, 255));
	}
	else
	{
		HDC BmpDC_R = CBmpMgr::Get_Instance()->Find_Bmp(L"Right");
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy, 
			BmpDC_R, m_Frame.FrameStart * 16, m_Frame.FrameMotion * 26, 16, 26, RGB(255, 255, 255));
	}


}

void CMonster::Release()
{
}
