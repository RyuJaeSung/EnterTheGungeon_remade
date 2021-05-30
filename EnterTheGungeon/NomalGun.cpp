#include "stdafx.h"
#include "NomalGun.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Bullet.h"
#include "KeyMgr.h"
#include "Player.h"
#include "SoundMgr.h"


CNomalGun::CNomalGun()
	:NowState(GUN::END) , NewState(GUN::END), BulletMotion(false)
{
	ZeroMemory(&TurnPoint, sizeof(TurnPoint));
}


CNomalGun::~CNomalGun()
{
}

void CNomalGun::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Gun/NomalGun.bmp", L"MyGun");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Big.bmp", L"Big");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Rotation.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Stretch.bmp", L"Stretch");

	m_Info.size.cx = 30;
	m_Info.size.cy = 30;
	BulletSpeed = GetTickCount();

	NowState = GUN::IDLE;
	DeadorAlive = OBJ::ALIVE;
	MaxMagazine = 6;

	m_Frame.FrameStart = 0;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameSpeed = 10;
	m_Frame.FrameEnd = 1;
	m_Frame.FrameTime = GetTickCount();
}
	
void CNomalGun::Update()
{
	if (NowState == GUN::RELORD&& m_Frame.FrameEnd >= 5)
		MaxMagazine = 6;

	Scene_Change();
	Scene_Turn();
	Frame_Move();
	Key_Check();
	Update_Rect();
}

void CNomalGun::Last_Upate()
{
	Gun_Turn();
}

void CNomalGun::Render(HDC DC)
{
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_STATE() == STATE::TUMBLING)
		return;
	GetClientRect(m_ghWnd, &Client_Rect);
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"MyGun");
	HDC BigDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Big");
	HDC RotationDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Rotation");

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, Client_Rect.right - 95, Client_Rect.bottom - 60, m_Info.size.cx, m_Info.size.cy,
		BmpDC, m_Frame.FrameStart * 15, m_Frame.FrameMotion * 15, 15, 15, RGB(255, 255, 255));

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
	{
		HDC Stretch = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
		StretchBlt(Stretch, 0, 0, 30, 30, BmpDC,
			m_Frame.FrameStart * 15 + 15, m_Frame.FrameMotion * 15, -15, 15, SRCCOPY);
		PlgBlt(RotationDC, TurnPoint, Stretch, 0, 0, 30, 30, NULL, NULL, NULL);
		GdiTransparentBlt(DC, (int)(Posin.x + ScrollX), (int)(Posin.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
			RotationDC, 0, 0, 30, 30, RGB(255, 255, 255));
	}
	else
	{
		PlgBlt(RotationDC, TurnPoint, BmpDC, m_Frame.FrameStart * 15, m_Frame.FrameMotion * 15, 15, 15, NULL, NULL, NULL);
		GdiTransparentBlt(DC, (int)(Posin.x + ScrollX), (int)(Posin.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
			RotationDC, 0, 0, 30 , 30, RGB(255, 255, 255));
	}

}

void CNomalGun::Release()
{
}

CObj * CNomalGun::Create_Bullet()
{
	Get_Degree();
	CObj* obj = Create_OBJ<CBullet>::Create((float)(Posin.x + (m_Info.size.cx >> 1)), (float)Posin.y + (m_Info.size.cy >> 1), m_fAngle);
	return obj;
}

void CNomalGun::Scene_Change()
{
	if (NewState != NowState)
	{
		switch (NewState)
		{
		case GUN::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameEnd = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		case GUN::RELORD:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameSpeed =500;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameTime = GetTickCount();
			break;
		case GUN::SHOT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 2;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
		NowState = NewState;
	}
}

void CNomalGun::Key_Check()
{
	if (CKeyMgr::Get_Instane()->Key_Pressing('R')  &&  MaxMagazine < 6)
	{
		NewState = GUN::RELORD;
		CSoundMgr::Get_Instance()->PlaySound(L"BasicsReroad.wav", CSoundMgr::PLAYER);
		return;
		CKeyMgr::Get_Instane()->Key_Update();
	}

	if (MaxMagazine <= 0)
	{
		NewState = GUN::IDLE;
		return;
	}

	if (BulletSpeed + 400 < GetTickCount() && dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_STATE() != STATE::TUMBLING)
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing(VK_LBUTTON))
		{
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::BULLET, Create_Bullet());
			BulletMotion = true;
			NewState = GUN::SHOT;
			--MaxMagazine;
			BulletSpeed = GetTickCount();


		}
		else
			NewState = GUN::IDLE;
	}
}

void CNomalGun::Gun_Turn()
{
	float X = (float)(m_Info.size.cx >> 1);
	float Y = (float)(m_Info.size.cy >> 1);
	float Dis = sqrtf((X*X) + (Y*Y));

	Get_Degree();
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
		m_fAngle += 180;


	TurnPoint[0].x = (LONG)(X + cosf((135 - m_fAngle) * PI / 180.f) * Dis);
	TurnPoint[0].y = (LONG)(Y - sinf((135 - m_fAngle)* PI / 180.f) * Dis);

	TurnPoint[1].x = (LONG)(X + cosf((45 - m_fAngle)* PI / 180.f) * Dis);
	TurnPoint[1].y = (LONG)(Y - sinf((45 - m_fAngle)* PI / 180.f) * Dis);

	TurnPoint[2].x = (LONG)(X + cosf((225 - m_fAngle)* PI / 180.f) * Dis);
	TurnPoint[2].y = (LONG)(Y - sinf((225 - m_fAngle)* PI / 180.f) * Dis);

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
	{
		Posin.x = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_RECT().left - cosf((-m_fAngle) * PI / 180.f) * 15.f);
		Posin.y = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().y + sinf((-m_fAngle) * PI / 180.f) * 15.f);
	}
	else
	{
		Posin.x = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().x + cosf((-m_fAngle) * PI / 180.f) * 15.f);
		Posin.y = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().y - sinf((-m_fAngle) * PI / 180.f) * 15.f);
	}

}

void CNomalGun::Scene_Turn()
{
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
	{
		m_Info.x = (float)(CObjMgr::Get_Instance()->Set_Player()->Get_RECT().left);
		m_Info.y = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y - 5.f;
	}
	else
	{
		m_Info.x = (float)(CObjMgr::Get_Instance()->Set_Player()->Get_RECT().right);
		m_Info.y = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y - 5.f;
	}
}
