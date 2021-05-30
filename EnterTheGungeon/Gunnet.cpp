#include "stdafx.h"
#include "Gunnet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CGunnet::CGunnet()
	:NowMonsterPos(END), NewMonsterPos(END)
{
}


CGunnet::~CGunnet()
{
}

void CGunnet::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/GunNetAttack.bmp", L"GunNet");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/GunNetIdle.bmp", L"GunNetIdle");

	m_Info.size.cx = 70;
	m_Info.size.cx = 70;
	AttackTime = GetTickCount();
	m_Ability.Hp = 200;
	DeadorAlive = OBJ::ALIVE;
	NewMonsterPos = IDLE;

	m_Frame.FrameStart = 0;
	m_Frame.FrameEnd = 4;
	m_Frame.FrameSpeed = 200;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameTime = GetTickCount();
}

void CGunnet::Update()
{
	if (m_Ability.Hp <= 0)
		DeadorAlive = OBJ::DEAD;
	Scene_Change();
	Frame_Move();
	Update_Rect();
}

void CGunnet::Last_Upate()
{
	if (AttackTime + 2000 < GetTickCount())
	{
		//CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CMonsterBullet>::Create(m_Info.x, m_Info.y));
		AttackTime = GetTickCount();
	}
}

void CGunnet::Render(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"GunNet");
	HDC IdleDC = CBmpMgr::Get_Instance()->Find_Bmp(L"GunNetIdle");

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	switch (NowMonsterPos)
	{
	case CGunnet::ATTACK:
		if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y <= m_Info.y)
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, m_Frame.FrameStart * 55, 0, 55, 55, RGB(255, 255, 255));
		}
		else
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, m_Frame.FrameStart * 50, 55, 55, 65, RGB(255, 255, 255));
		}
		break;
	case CGunnet::IDLE:
		if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y <= m_Info.y)
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				IdleDC, m_Frame.FrameStart * 50, 0, 50, 50, RGB(255, 255, 255));
		}
		else
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				IdleDC, m_Frame.FrameStart * 50, 50, 50, 50, RGB(255, 255, 255));
		}
		break;
	}

}

void CGunnet::Release()
{
}

void CGunnet::Scene_Change()
{
	if (NewMonsterPos != NowMonsterPos)
	{
		switch (NewMonsterPos)
		{
		case ATTACK:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 11;
			m_Frame.FrameSpeed = 150;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameTime = GetTickCount();
			break;
		case IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 4;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
		NowMonsterPos = NewMonsterPos;
	}
}
