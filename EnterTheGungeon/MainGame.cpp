#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UiMgr.h"
#include "Mouse.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(m_ghWnd);
	srand(unsigned(time(NULL)));
	CBmpMgr::Get_Instance()->Insect_Bmp(L"../Image/Back/Back.bmp", L"Back");

	CObj* obj = new CMouse;
	obj->Initialize();
	CObjMgr::Get_Instance()->Get_AddObj(OBJ::MOUSE, obj);
	CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_LOGO);
	CSoundMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CObjMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Last_Upate()
{
	CObjMgr::Get_Instance()->Late_Update();
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC BackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back");
	CSceneMgr::Get_Instance()->Render(BackDC);
	CUiMgr::Get_Instance()->Render(BackDC);
	CObjMgr::Get_Instance()->Render(BackDC);
	BitBlt(m_DC, 0, 0, Client_Rect.right, Client_Rect.bottom + 100, BackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	CBmpMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CUiMgr::Dsetroy_Instance();
	ReleaseDC(m_ghWnd, m_DC);
}
