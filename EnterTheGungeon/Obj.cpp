#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_Rect.left = (LONG)(m_Info.x - (m_Info.size.cx >> 1));
	m_Rect.right = (LONG)(m_Info.x + (m_Info.size.cx >> 1));
	m_Rect.top = (LONG)(m_Info.y - (m_Info.size.cx >> 1));
	m_Rect.bottom = (LONG)(m_Info.y + (m_Info.size.cx >> 1));
}

void CObj::Get_Degree()
{
	POINT mp;
	GetCursorPos(&mp);
	ScreenToClient(m_ghWnd, &mp);
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	mp.x -= ScrollX;
	mp.y -= ScrollY;

	m_fAngle = (float)(atan2f((mp.y - m_Info.y), (mp.x - m_Info.x)) * 180 / PI);
}

void CObj::Frame_Move()
{
	if (m_Frame.FrameTime + m_Frame.FrameSpeed < GetTickCount())
	{
		++m_Frame.FrameStart;
		m_Frame.FrameTime = GetTickCount();
	}
	
	if (m_Frame.FrameStart >= m_Frame.FrameEnd)
		m_Frame.FrameStart = 0;
}
