#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"


CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/Doorfront.bmp", L"Doorfront");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/UI/Doorfword.bmp", L"Doorfword");

	
		m_Info.size.cx = abs(m_Rect.right - m_Rect.left);
		m_Info.size.cy = abs(m_Rect.top - m_Rect.bottom);


}

void CDoor::Update()
{
	if (CObjMgr::Get_Instance()->Set_FightOn())
	{
		DeadorAlive = OBJ::DEAD;
		return;
	}

	 
}

void CDoor::Last_Upate()
{
}

void CDoor::Render(HDC DC)
{
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_Info.x > m_Info.y)
	{
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Doorfword");
		GdiTransparentBlt(DC, m_Rect.left + ScrollX, m_Rect.top + ScrollY, m_Info.size.cx, m_Info.size.cy,
			BmpDC, 0, 0, 6, 45, RGB(255, 255, 255));
	}
	else
	{
		HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Doorfront");
		GdiTransparentBlt(DC, m_Rect.left + ScrollX, m_Rect.top + ScrollY, m_Info.size.cx, m_Info.size.cy,
			BmpDC, 0, 0, 32, 39, RGB(255, 255, 255));
	}
}

void CDoor::Release()
{
}
