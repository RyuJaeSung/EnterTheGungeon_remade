#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "ShotgunMan.h"
#include "ScrollMgr.h"
#include "UiMgr.h"
#include "Door.h"
#include "Boss.h"
#include "Break_Check.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"

CStage::CStage()
	:MapMove(0), MosterFight(0)
{
	ZeroMemory(StageWall, sizeof(StageWall));
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Map/AllMap.bmp", L"Map1");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Back.bmp", L"BackBuffer");
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Back2.bmp", L"Back2");
	CSoundMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->Get_AddObj(OBJ::PLAYER, Create_OBJ<CPlayer>::Create(640, 640));
	CUiMgr::Get_Instance()->Initialize();
	MakeingMonster = false;

	StageWall[START] = { 50,270 , 1060 , 1050 };
	StageWall[STF] = { 500, 1055, 630, 1465 };
	StageWall[FRIST] = { 380, 1470, 1990, 2050 };
	StageWall[FS] = { 1785, 1190 , 1915, 1470 };
	StageWall[SECOND] = { 1740, 140, 3430, 1190};
	StageWall[ST] = { 3430, 220, 3705, 355 };
	StageWall[TERCEROS] = { 3705, 140, 4800, 1180 };
	StageWall[SF] = {4615, 1180, 4755, 1530};
	StageWall[FOURTH] = {4515, 1530, 4755, 1760};
	StageWall[FB] = { 4265, 1580, 4515, 1710};
	StageWall[BOSS] = {2495, 1270, 4265, 2410};


	CSoundMgr::Get_Instance()->PlayBGM(L"02 LEAD LORDS KEEP.flac");
}

void CStage::Update()
{
	Wall_Check();
	CObjMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	Create_Monster();
}
void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC DC)
{
	GetClientRect(m_ghWnd, &Client_Rect);
	int ScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int ScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC BmpDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Map1");
	HDC	BufferDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BackBuffer");
	HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back2");

	StretchBlt(BufferDC, 30, 10, 5000, 2500, BmpDC, 0, 0, 1384, 830, SRCCOPY);
	BitBlt(BackDC, 0, 0, StageWall[MapMove].right + 500, StageWall[MapMove].bottom + 100, BufferDC, 0, 0, SRCCOPY);
	BitBlt(DC, Client_Rect .left- 100, Client_Rect .top , Client_Rect.right + 100, Client_Rect.bottom, BackDC, -ScrollX, -ScrollY, SRCCOPY);
	

	CUiMgr::Get_Instance()->Render(DC);
	CObjMgr::Get_Instance()->Render(DC);
}

void CStage::Release()
{
}

void CStage::Wall_Check()
{
	if (CObjMgr::Get_Instance()->Set_FightOn())
	{
		RECT rc;
		if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Set_Player()->Get_RECT(), &StageWall[MapMove + 1]))
		{
			MapMove++;
			return;
		}

		if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Set_Player()->Get_RECT(), &StageWall[MapMove - 1]))
		{
			MapMove--;
			return;
		}
	}
	else
	{
		if (CObjMgr::Get_Instance()->Set_CreateDoor())
		{
			if(MapMove != BOSS)
				CObjMgr::Get_Instance()->Get_AddObj(OBJ::DOOR, Create_OBJ<CDoor>::Create(StageWall[MapMove + 1]));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::DOOR, Create_OBJ<CDoor>::Create(StageWall[MapMove - 1]));
		}
	}

	CBreak_Check::WallCheck(CObjMgr::Get_Instance()->Set_Player(), StageWall[MapMove]);
}

void CStage::Create_Monster()
{
	if (MapMove == FRIST && MosterFight <= 0)
	{
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(1000, 1700));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(1200, 1750));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(1200, 1900));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(1800, 1620));
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(1800, 1900));
		++MosterFight;
		return;
	}

	else if (MapMove == SECOND && MosterFight <= 1)
	{
		if (CObjMgr::Get_Instance()->Set_Size() && MakeingMonster)
		{
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2500, 1000));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2650, 1100));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(2050, 755));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(3085, 595));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3200, 360));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3370, 620));
			++MosterFight;
			MakeingMonster = false;
			return;
		}

		if (!MakeingMonster)
		{
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3230, 1125));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2820, 1125));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(1900, 215));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2140, 215));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2500, 760));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2650, 760));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2800, 760));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(2950, 760));
			MakeingMonster = true;
		}

	}
	else if (MapMove == TERCEROS && MosterFight <= 2)
	{
		if (CObjMgr::Get_Instance()->Set_Size() && MakeingMonster)
		{
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3700, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3900, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4100, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(4300, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4500, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4700, 300));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4900, 300));
			++MosterFight;
			MakeingMonster = false;
			return;
		}

		if (!MakeingMonster)
		{
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(3800, 1080));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4000, 1080));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(4200, 1080));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CShotgunMan>::Create(4400, 1080));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4600, 1080));
			CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CMonster>::Create(4800, 1080));
			MakeingMonster = true;
		}
	}
	else if (MapMove == BOSS && MosterFight <= 3)
	{
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlayBGM(L"43 A CONVICTS LAST DANCE.flac");
		CObjMgr::Get_Instance()->Get_AddObj(OBJ::MONSTER, Create_OBJ<CBoss>::Create());
		++MosterFight;
	}
}

