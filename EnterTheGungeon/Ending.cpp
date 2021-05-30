#include "stdafx.h"
#include "Ending.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

void CEnding::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/Ending.bmp", L"Ending");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Big.bmp", L"Back7");
	GetClientRect(m_ghWnd, &Client_Rect);

	m_info.fX = (float)((Client_Rect.right - Client_Rect.left) >> 1);
	m_info.fY = (float)((Client_Rect.bottom - Client_Rect.top) >> 1);
	BookSize.cx = 450;
	BookSize.cy = 280;


	Frame.FrameStart = 0;
	Frame.FrameEnd = 31;
	Frame.FrameSpeed = 100;
	Frame.FrameTime = GetTickCount();
}

void CEnding::Update()
{
	if (Frame.FrameTime + Frame.FrameSpeed < GetTickCount())
	{
		++Frame.FrameStart;
		Frame.FrameTime = GetTickCount();
	}
}

void CEnding::Late_Update()
{
}

void CEnding::Render(HDC DC)
{
	HDC BmpDC =	CBmpMgr::Get_Instance()->Find_Bmp(L"Ending");
	HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back7");

	BitBlt(DC, (int)(m_info.fX - 225), (int)(m_info.fY - 140), BookSize.cx, BookSize.cy, BmpDC, 0, Frame.FrameStart * BookSize.cy, SRCCOPY);
}

void CEnding::Release()
{
}
