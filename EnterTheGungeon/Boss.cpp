#include "stdafx.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "ClineBullet.h"
#include "ShotBullet.h"
#include "BossBullet.h"


CBoss::CBoss()
	:NowMonsterPos(END), NewMonsterPos(END), BulletTime(false)
{
}


CBoss::~CBoss()
{
}

void CBoss::Scene_Change()
{
	if (NowMonsterPos != NewMonsterPos)
	{
		switch (NewMonsterPos)
		{
		case CBoss::INTRO:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameEnd = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameEnd = 4;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::RUN:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameEnd = 4;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::ATTACK:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 200;
			if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y < m_Info.y)
				m_Frame.FrameEnd = 9;
			else
				m_Frame.FrameEnd = 10;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::CONTINUOUS:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed =200;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::SPIN:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 150;
			m_Frame.FrameEnd = 18;
			m_Frame.FrameTime = GetTickCount();
			break;
		case CBoss::DEAD:
			m_Frame.FrameStart = 0;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameEnd = 9;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
		NowMonsterPos = NewMonsterPos;
	}
}

void CBoss::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossIntroImage.bmp", L"Image");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/Boss.bmp", L"Boss");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossDead.bmp", L"Dead");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossIntro.bmp", L"BossIntro");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossMoveShot.bmp", L"BossMoveShot");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossSpin.bmp", L"BossSpin");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossAttack_Font.bmp", L"FAttack");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Monster/BossAttack_Back.bmp", L"BAttack");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Boss.bmp", L"Back5");
	
	RECT BossPos = CSceneMgr::Get_Instance()->Set_Wall();
 	m_Info.x = (float)(BossPos.left + ((BossPos.right - BossPos.left) >> 1) + 35);
	m_Info.y = (float)(BossPos.top + ((BossPos.bottom - BossPos.top) >> 1) - 220);

	m_Info.size.cx = 80;
	m_Info.size.cy = 100;
	DeadorAlive = OBJ::ALIVE;
	m_Ability.Hp = 900;
	m_Speed = 5.f;
	NewMonsterPos = INTRO;
}

void CBoss::Update()
{
	Scene_Change();
	Frame_Move();
	Update_Rect();
}

void CBoss::Last_Upate()
{
	if (m_Frame.FrameStart == m_Frame.FrameEnd - 1 && NowMonsterPos != INTRO)
	{
		int RandomSkill = rand() % 5 + 1;
		NewMonsterPos = (BOSSPATTERN)RandomSkill;
		BulletTime = false;
	}
	if (m_Ability.Hp <= 0)
		NewMonsterPos = DEAD;
}

void CBoss::Render(HDC DC)
{
	switch (NowMonsterPos)
	{
	case CBoss::INTRO:
		Boss_Intro(DC);
		return;
	case CBoss::IDLE:
		Boss_Idle(DC);
		break;
	case CBoss::RUN:
		Boss_Run(DC);
		break;
	case CBoss::ATTACK:
		Boss_Attack(DC);
		break;
	case CBoss::CONTINUOUS:
		Boss_ContinuousAttack(DC);
		break;
	case CBoss::SPIN:
		Boss_Spin(DC);
		break;
	case CBoss::DEAD:
		Boss_Dead(DC);
		return;
	}
	if(m_Ability.Hp > 0)
		Boss_HpBar(DC);
}

void CBoss::Boss_Intro(HDC DC)
{

	HDC IntroDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Image");
	GetClientRect(m_ghWnd, &Client_Rect);

	StretchBlt(DC, Client_Rect.left, Client_Rect.top, Client_Rect.right, Client_Rect.bottom,
		IntroDC, 0, 0, 115, 71, SRCCOPY);
	
	if (CKeyMgr::Get_Instane()->Key_Pressing(VK_SPACE))
		NewMonsterPos = IDLE;

}

void CBoss::Boss_Attack(HDC DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y <= m_Info.y)
	{
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BAttack");
		if(m_Frame.FrameStart <= 1)
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 30, m_Info.size.cy + 30,
			BmpDC, m_Frame.FrameStart * 50, 0, 50, 55, RGB(255, 255, 255));
		else if (m_Frame.FrameStart <= 4)
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, (m_Frame.FrameStart - 2) * 30, 55, 30, 35, RGB(255, 255, 255));
			if (!BulletTime && m_Frame.FrameStart == 3)
			{
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.right, m_Info.y - 10, 120.f));
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.right, m_Info.y - 10, 90.f));
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.right, m_Info.y - 10, 60.f));
				BulletTime = true;
			}
		}
		else
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx +30, m_Info.size.cy + 30,
				BmpDC, (m_Frame.FrameStart - 5) * 70, 90, 70, 60, RGB(255, 255, 255));
	}
	else
	{
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"FAttack");
		if (m_Frame.FrameStart <= 1)
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 30, m_Info.size.cy + 30,
				BmpDC, m_Frame.FrameStart * 50, 0, 50, 55, RGB(255, 255, 255));
		else if (m_Frame.FrameStart <= 6)
		{
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, (m_Frame.FrameStart - 2) * 30, 55, 30, 35, RGB(255, 255, 255));
			if (!BulletTime && m_Frame.FrameStart == 5)
			{
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.left, m_Info.y, 300.f));
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.left, m_Info.y, 270.f));
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CBossBullet>::Create((float)m_Rect.left, m_Info.y, 240.f));
				BulletTime = true;
			}
		}
		else
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 30, m_Info.size.cy + 30,
				BmpDC, (m_Frame.FrameStart - 7) * 70, 90, 70, 60, RGB(255, 255, 255));
	}
}

void CBoss::Boss_Spin(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BossSpin");
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_Frame.FrameStart <= 5)
	{
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			BmpDC, m_Frame.FrameStart * 40, 0, 40, 40, RGB(255, 255, 255));
	}
	else if (m_Frame.FrameStart <= 14)
	{
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 40, m_Info.size.cy,
			BmpDC, (m_Frame.FrameStart- 6) * 70, 40, 70, 40, RGB(255, 255, 255));
		for (int i = 0; i < 2; ++i)
		{
			float Angle = rand() % 360 + 1.f;
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create((float)m_Rect.left, m_Info.y - 10, Angle));
		}
	}
	else
	{
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
			BmpDC, (m_Frame.FrameStart - 15) * 40, 80, 40, 40, RGB(255, 255, 255));
	}
}

void CBoss::Boss_ContinuousAttack(HDC DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BossMoveShot");

	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().x <= m_Info.x)
	{
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 55, m_Info.size.cy,
			BmpDC, m_Frame.FrameStart * 55, 0, 55, 40, RGB(255, 255, 255));
			float Angle = rand() % 30 + 165.f;
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create((float)m_Rect.left, m_Info.y - 10, Angle));
	}
	else
	{
		GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx + 55, m_Info.size.cy,
			BmpDC, m_Frame.FrameStart * 55, 40, 55, 40, RGB(255, 255, 255));

			float Angle = rand() % 30 + 345.f;
			if (Angle >= 360)
				Angle -= 360.f;
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTERBULLET, Create_OBJ<CShotBullet>::Create((float)m_Rect.right, m_Info.y - 10, Angle));
		
	}
	
	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y <= m_Info.y)
		m_Info.y -= m_Speed;
	else
		m_Info.y += m_Speed;
}

void CBoss::Boss_Idle(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Boss");
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx , m_Info.size.cy,
		BmpDC, m_Frame.FrameStart * 40, 0, 40, 40, RGB(255, 255, 255));

}

void CBoss::Boss_Run(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Boss");
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().y <= m_Info.y)
	{
		m_Info.y -= m_Speed;
		if (Turn_Run())
		{
			m_Info.x -= m_Speed;
			HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back5");
			StretchBlt(BackDC, 0,0, 40, 40,
				BmpDC, m_Frame.FrameStart  * 40 + 40, 80, -40, 40, SRCCOPY);
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy, BackDC, 0, 0, 40, 40, RGB(255, 255, 255));
		}
		else
		{
			m_Info.x += m_Speed;
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, m_Frame.FrameStart * 40, 80, 40, 40, RGB(255, 255, 255));
		}
	}
	else
	{
		m_Info.y += m_Speed;
		if (Turn_Run())
		{
			m_Info.x -= m_Speed;
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
				BmpDC, m_Frame.FrameStart * 40, 40, 40, 40, RGB(255, 255, 255));
		}
		else
		{
			m_Info.x += m_Speed;
			HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back5");
			StretchBlt(BackDC, 0, 0, 40, 40,
				BmpDC, m_Frame.FrameStart * 40 + 40, 40, -40, 40, SRCCOPY);
			GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy, BackDC, 0, 0, 40, 40, RGB(255,255,255));
		}
	}

}

void CBoss::Boss_Dead(HDC DC)
{
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Dead");
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, (int)(m_Rect.left + ScrollX), (int)(m_Rect.top + ScrollY), m_Info.size.cx, m_Info.size.cy,
		BmpDC, m_Frame.FrameStart * 42, 0, 42, 35, RGB(255, 255, 255));
}

bool CBoss::Turn_Run()
{



	if (CObjMgr::Get_Instance()->Set_Player()->Get_Info().x <= m_Info.x)
		return true; //오른쪽에서 왼쪽으로 변경
	return false; //
}

void CBoss::Boss_HpBar(HDC DC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(255,0,0));
	oldBrush = (HBRUSH)SelectObject(DC, myBrush);
	GetClientRect(m_ghWnd, &Client_Rect);
	int HpBar = (Client_Rect.right - Client_Rect.left) >> 1;

	Rectangle(DC, HpBar - (m_Ability.Hp >> 1), Client_Rect.bottom - 50, HpBar + (m_Ability.Hp >> 1), Client_Rect.bottom - 20);

	SelectObject(DC, oldBrush);
	DeleteObject(myBrush);
}

void CBoss::Release()
{
}
