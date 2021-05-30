#include "stdafx.h"
#include "AK47.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"  
#include "Player.h"
#include "AKBullet.h"
#include "SoundMgr.h"

CAK47::CAK47()
	:NowState(GUN::END), NewState(GUN::END)
{
	ZeroMemory(&TurnPoint, sizeof(TurnPoint));
}


CAK47::~CAK47()
{
}

void CAK47::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Gun/AK-47.bmp", L"AK");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Big.bmp", L"Big");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Rotation.bmp", L"Rotation");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Stretch.bmp", L"Stretch");

	m_Info.size.cx = 45;
	m_Info.size.cy = 45;
	BulletSpeed = GetTickCount();

	NowState = GUN::IDLE;
	DeadorAlive = OBJ::ALIVE;

	MaxMagazine = 30;
	m_Speed = 8.f;

	m_Frame.FrameStart = 0;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameSpeed = 200;
	m_Frame.FrameEnd = 4;
	m_Frame.FrameTime = GetTickCount();
}

void CAK47::Update()
{
	if (NowState == GUN::RELORD&& m_Frame.FrameEnd -1 == m_Frame.FrameStart)
		MaxMagazine = 30;

	Scene_Change();
	Scene_Turn();
	Frame_Move();
	Key_Check();
	Update_Rect();
}

void CAK47::Last_Upate()
{
	Gun_Turn();
}

void CAK47::Render(HDC DC)
{
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_STATE() == STATE::TUMBLING)
		return;
	GetClientRect(m_ghWnd, &Client_Rect);
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"AK");
	HDC BigDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Big");
	HDC RotationDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Rotation");

	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(DC, Client_Rect.right - 95, Client_Rect.bottom - 60, m_Info.size.cx, m_Info.size.cy,
		BmpDC, m_Frame.FrameStart * 30, m_Frame.FrameMotion * 10, 30, 10, RGB(255, 255, 255));

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
	{
		HDC Stretch = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
		StretchBlt(Stretch, 0, 0, m_Info.size.cx, m_Info.size.cy, BmpDC,
			m_Frame.FrameStart * 30 + 30, m_Frame.FrameMotion * 10, -30, 10, SRCCOPY);
		PlgBlt(RotationDC, TurnPoint, Stretch, 0, 0, m_Info.size.cx, m_Info.size.cy, NULL, NULL, NULL);
		GdiTransparentBlt(DC, (int)(Posin.x + ScrollX), (int)(Posin.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
			RotationDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
	}
	else
	{
		PlgBlt(RotationDC, TurnPoint, BmpDC, m_Frame.FrameStart * 30, m_Frame.FrameMotion * 10, 30, 10, NULL, NULL, NULL);
		GdiTransparentBlt(DC, (int)(Posin.x + ScrollX), (int)(Posin.y + ScrollY), m_Info.size.cx, m_Info.size.cy,
			RotationDC, 0, 0, m_Info.size.cx, m_Info.size.cy, RGB(255, 255, 255));
	}

}

void CAK47::Release()
{
}

CObj * CAK47::Create_Bullet()
{
	Get_Degree();
	CObj* obj = Create_OBJ<CAKBullet>::Create((float)(Posin.x + (m_Info.size.cx >> 1)), (float)Posin.y + (m_Info.size.cy >> 1), m_fAngle);
	return obj;
}

void CAK47::Scene_Change()
{
	if (NewState != NowState)
	{
		switch (NewState)
		{
		case GUN::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameSpeed = 200;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameTime = GetTickCount();
			break;
		case GUN::RELORD:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameSpeed = 300;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameTime = GetTickCount();
			break;
		case GUN::SHOT:
			m_Frame.FrameStart = 0;
			m_Frame.FrameMotion = 2;
			m_Frame.FrameSpeed = 100;
			m_Frame.FrameEnd = 2;
			m_Frame.FrameTime = GetTickCount();
			break;
		}
		NowState = NewState;
	}
}

void CAK47::Key_Check()
{
	if (CKeyMgr::Get_Instane()->Key_Down('R') || CKeyMgr::Get_Instane()->Key_Pressing('R') && MaxMagazine < 30)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"AK-47Reroad.wav", CSoundMgr::PLAYER);
		NewState = GUN::RELORD;
		return;
		CKeyMgr::Get_Instane()->Key_Update();

	}

	if (MaxMagazine <= 0)
	{
		NewState = GUN::IDLE;
		return;
	}

	if (BulletSpeed + 100 < GetTickCount() && dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_STATE() != STATE::TUMBLING)
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"AK-47Shot.wav", CSoundMgr::PLAYER);
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::BULLET, Create_Bullet());
			NewState = GUN::SHOT;
			--MaxMagazine;
			BulletSpeed = GetTickCount();
		}
		else
			NewState = GUN::IDLE;
	}
}

void CAK47::Gun_Turn()
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
		Posin.x = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().x - cosf((-m_fAngle) * PI / 180.f) * 15.f - 40.f);
		Posin.y = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().y + sinf((-m_fAngle) * PI / 180.f) * 15.f);
	}
	else
	{
		Posin.x = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().x + cosf((-m_fAngle) * PI / 180.f) * 15.f);
		Posin.y = (LONG)(CObjMgr::Get_Instance()->Set_Player()->Get_Info().y - sinf((-m_fAngle) * PI / 180.f) * 15.f);
	}

}

void CAK47::Scene_Turn()
{
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Set_Player())->Set_TurnImage())
	{
		m_Info.x = (float)(CObjMgr::Get_Instance()->Set_Player()->Get_RECT().left);
		m_Info.y = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y - 5.f;
	}
	else
	{
		m_Info.x = (float)(CObjMgr::Get_Instance()->Set_Player()->Get_RECT().right);
		m_Info.y = CObjMgr::Get_Instance()->Set_Player()->Get_Info().y;
	}
}
