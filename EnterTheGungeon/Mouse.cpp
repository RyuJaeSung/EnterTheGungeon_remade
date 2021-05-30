#include "stdafx.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{ 
	m_Info.size.cx = 30;
	m_Info.size.cy = 30;

	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Point.bmp", L"Mouse");
}

void CMouse::Update()
{
}

void CMouse::Last_Upate()
{
}

void CMouse::Render(HDC DC)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_ghWnd, &pt);
	ShowCursor(FALSE);
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Mouse");

	m_Info.x = (float)pt.x;
	m_Info.y = (float)pt.y;
	Update_Rect();

	GdiTransparentBlt(DC, m_Rect.left, m_Rect.top, m_Info.size.cx, m_Info.size.cy,
		BmpDC, 0, 0, 240, 240, RGB(255, 255, 255));
}

void CMouse::Release()
{
}
