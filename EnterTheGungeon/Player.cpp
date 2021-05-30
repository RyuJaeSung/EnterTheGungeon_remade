#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "NomalGun.h"
#include "AK47.h"
#include "SceneMgr.h"


CPlayer::CPlayer()
	: TumblingState(false), KeyDown(KEYEND), TurnImage(false), WeaponChice(0)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Check()
{
	if (CKeyMgr::Get_Instane()->Key_Pressing('A'))
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing('W'))
			KeyDown = LF_BACKFWORD;
		else if (CKeyMgr::Get_Instane()->Key_Pressing('S'))
			KeyDown = LF_FRONTFWORD;
		else
			KeyDown = LEFT;

		if (!TumblingState)
			NewState = STATE::WALK;
	}
	else if (CKeyMgr::Get_Instane()->Key_Pressing('D'))
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing('W'))
			KeyDown = RI_BACKFWORD;
		else if (CKeyMgr::Get_Instane()->Key_Pressing('S'))	
			KeyDown = RI_FRONTFWORD;
		else
			KeyDown = RIGHT;

		if (TumblingState)
			NewState = STATE::TUMBLING;
		else
			NewState = STATE::WALK;
	}

	else if (CKeyMgr::Get_Instane()->Key_Pressing('W'))
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing('A'))
			KeyDown = LF_BACKFWORD;
		else if (CKeyMgr::Get_Instane()->Key_Pressing('D'))
			KeyDown = RI_BACKFWORD;
		else
			KeyDown = BACK;


		if (!TumblingState)
			NewState = STATE::WALK;
	}

	else if (CKeyMgr::Get_Instane()->Key_Pressing('S'))
	{
		if (CKeyMgr::Get_Instane()->Key_Pressing('A'))
			KeyDown = LF_FRONTFWORD;
		else if (CKeyMgr::Get_Instane()->Key_Pressing('D'))
			KeyDown = RI_FRONTFWORD;
		else
			KeyDown = FRONT;

		if (!TumblingState)
			NewState = STATE::WALK;
	}
	else
	{
		NewState = STATE::IDLE;
		KeyDown = KEYEND;
	}

	if (CKeyMgr::Get_Instane()->Key_Pressing(VK_SPACE) && NewState == STATE::WALK)
		NewState = STATE::TUMBLING;


	if (CKeyMgr::Get_Instane()->Key_Pressing('Q'))
		m_Ability.Hp++;
}
	
void CPlayer::OffSet()
{
	GetClientRect(m_ghWnd, &Client_Rect);
	int OffSetX = Client_Rect.right >> 1;
	int	OffSetY = Client_Rect.bottom >> 1;
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (OffSetX > m_Info.x + ScrollX)
	{
		if(m_Info.x > 780)
			CScrollMgr::Get_Instance()->Set_ScrollX(OffSetX - (m_Info.x + ScrollX));
	}
	if (OffSetX < m_Info.x + ScrollX)
	{
		if(m_Info.x < 4400)
			CScrollMgr::Get_Instance()->Set_ScrollX(OffSetX - (m_Info.x + ScrollX));
	}
	if (OffSetY > m_Info.y + ScrollY)
	{
		if(m_Info.y > 440)
			CScrollMgr::Get_Instance()->Set_ScrollY(OffSetY - (m_Info.y + ScrollY));
	}
	if (OffSetY < m_Info.y + ScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(OffSetY - (m_Info.y + ScrollY));



}

void CPlayer::Scene_Change()
{

	if (NowState != NewState)
	{
		switch (NewState)
		{
		case STATE::IDLE:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 0;
			m_Frame.FrameTime = GetTickCount();
			break;
		case STATE::WALK:
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 6;
			m_Frame.FrameMotion = 1;
			m_Frame.FrameTime = GetTickCount();
			break;
		case STATE::TUMBLING:
			TumblingState = true;
			m_Frame.FrameStart = 0;
			m_Frame.FrameEnd = 9;
			m_Frame.FrameMotion = 2;
			m_Frame.FrameTime = GetTickCount();
			break;
		case STATE::ATTACK:
			break;
		case STATE::DEAD:
			CSceneMgr::Get_Instance()->Set_NewScene(SCENE::SCENE_ENDING);
			break;
		}
		NowState = NewState;
	}
}


void CPlayer::Initialize()
{	
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Stretch.bmp", L"Stretch");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Character/Playerfront.bmp", L"Playerfront");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Character/Playerback.bmp", L"Playerback");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Character/Playerbackfword.bmp", L"Playerbackfword");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Character/Playerfword.bmp", L"Playerfword");
	CObjMgr::Get_Instance()->Get_AddObj(OBJ::GUN, Create_OBJ<CNomalGun>::Create());
	
	m_Info.size.cx = 60;
	m_Info.size.cy = 60;
	
	m_Frame.FrameStart = 0;
	m_Frame.FrameMotion = 0;
	m_Frame.FrameEnd = 6;
	m_Frame.FrameSpeed = 100;
	m_Frame.FrameTime = GetTickCount();


	NowState = STATE::IDLE;
	NewState = STATE::IDLE;
	WeaponChice = 1;

	m_Speed = 5.0f;
	m_fAngle = 271.f;
	FrameKey = L"Playerfront";
	DeadorAlive = OBJ::ALIVE;
	m_Ability.MaxHp = 6;
	m_Ability.Hp = 6;
	m_Ability.Shield = 0;
	m_Ability.Bomb = 2;

	MyFont = CreateFont(0, 0, 0, 0, FW_BOLD, 0, 0, 0,
		ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_ROMAN, L"±¼¸²");
}

void CPlayer::Update()
{
	if (!TumblingState)
	{
		LookMouse();
		Scene_Change();
		Key_Check();
	}
	else
	{
		if (m_Frame.FrameStart == m_Frame.FrameEnd - 1)
			TumblingState = false;
		
	}
	Weapon_Change();
	OffSet();
	Player_Move();
	Frame_Move();
	Update_Rect();
}

void CPlayer::Last_Upate()
{
	if (m_Ability.Hp <= 0)
		NewState = STATE::DEAD;
}

void CPlayer::Render(HDC DC)
{
	Update_Rect();
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(FrameKey);
	
	if (TurnImage)
	{
		HDC Stretch = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
		StretchBlt(Stretch, 0, 0, 24, 24, BmpDC,
			m_Frame.FrameStart * 23 + 23, m_Frame.FrameMotion * 24
			, -23, 24, SRCCOPY);
		
		GdiTransparentBlt(DC, m_Rect.left + ScrollX, m_Rect.top + ScrollY, m_Info.size.cx, m_Info.size.cy,
			Stretch, 0, 0, 23, 24, RGB(255, 255, 255));
	}
	else
	{
		GdiTransparentBlt(DC, m_Rect.left + ScrollX, m_Rect.top + ScrollY, m_Info.size.cx, m_Info.size.cy,
			BmpDC, m_Frame.FrameStart * 23, m_Frame.FrameMotion * 24, 23, 24, RGB(255, 255, 255));
	}


	if (CObjMgr::Get_Instance()->Set_Gun()->Get_MaxMagazine() <= 0)
	{
		RECT rc = { m_Rect.left + ScrollX , m_Rect.top - 20 + ScrollY, m_Rect.right + ScrollX, m_Rect.top + ScrollY };

		OldFont = (HFONT)SelectObject(DC, MyFont);
		SetBkMode(DC, TRANSPARENT);
		SetTextColor(DC, RGB(255, 255, 255));

		DrawText(DC, L"ÀçÀåÀü", -1, &rc, DT_VCENTER | DT_CENTER);
	}
	

	////ÁÂÇ¥ À§Ä¡
	//TCHAR PlayerPos[20] = {};
	//swprintf_s(PlayerPos, L"X : %d Y : %d", (int)m_Info.x, (int)m_Info.y);
	//TextOut(DC, 600, 450, PlayerPos, sizeof(PlayerPos));
}

void CPlayer::Release()
{
}

void CPlayer::LookMouse()
{
	Get_Degree();
	if (m_fAngle < 0)
		m_fAngle += 360.f;

	if (240 < m_fAngle && m_fAngle < 300)
	{
		if (240 < m_fAngle && m_fAngle < 270)
			TurnImage = true;

		else
			TurnImage = false;
		FrameKey = L"Playerback";
	}
	else if (60 < m_fAngle && m_fAngle < 120)
	{
		if (60 < m_fAngle && m_fAngle < 90)
			TurnImage = false;

		else
			TurnImage = true;
		FrameKey = L"Playerfront";
	}
	else if (0 < m_fAngle && m_fAngle < 60)
	{
		TurnImage = false;
		FrameKey = L"Playerfword";
	}

	else if (120 < m_fAngle && m_fAngle < 180)
	{
		TurnImage = true;
		FrameKey = L"Playerfword";
	}
	else if (180 < m_fAngle && m_fAngle < 240)
	{
		TurnImage = true;
		FrameKey = L"Playerbackfword";
	}
	else if (300 < m_fAngle && m_fAngle < 360)
	{
		TurnImage = false;
		FrameKey = L"Playerbackfword";
	}

}

void CPlayer::Player_Move()
{
	switch (KeyDown)
	{
	case CPlayer::FRONT:
		m_Info.y += m_Speed;
		if(TumblingState)
			FrameKey = L"Playerfront";
		break;
	case CPlayer::BACK:
		m_Info.y -= m_Speed;
		if (TumblingState)
			FrameKey = L"Playerback";
		break;
	case CPlayer::LEFT:
		m_Info.x -= m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerfword";
			TurnImage = true;
		}
		break;
	case CPlayer::RIGHT:
		m_Info.x += m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerfword";
			TurnImage = false;
		}
		break;
	case CPlayer::RI_FRONTFWORD:
		m_Info.x += m_Speed;
		m_Info.y += m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerfword";
			TurnImage = false;
		}
		break;
	case CPlayer::LF_FRONTFWORD:
		m_Info.x -= m_Speed;
		m_Info.y += m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerfword";
			TurnImage = true;
		}
		break;
	case CPlayer::RI_BACKFWORD:
		m_Info.x += m_Speed;
		m_Info.y -= m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerbackfword";
			TurnImage = false;
		}
		break;
	case CPlayer::LF_BACKFWORD:
		m_Info.x -= m_Speed;
		m_Info.y -= m_Speed;
		if (TumblingState)
		{
			FrameKey = L"Playerbackfword";
			TurnImage = true;
		}
		break;
	}
}

void CPlayer::Weapon_Change()
{
	if (WeaponChice != 1 && CKeyMgr::Get_Instane()->Key_Pressing('1'))
	{
		CObjMgr::Get_Instance()->Delete_ID(OBJ::GUN);
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::GUN, Create_OBJ<CNomalGun>::Create());
		WeaponChice = 1;
	}
	if (WeaponChice != 2 && CKeyMgr::Get_Instane()->Key_Pressing('2'))
	{
		CObjMgr::Get_Instance()->Delete_ID(OBJ::GUN);
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::GUN, Create_OBJ<CAK47>::Create());
		WeaponChice = 2;
	}
}
