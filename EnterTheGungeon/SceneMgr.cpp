#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "Ending.h"


CSceneMgr* CSceneMgr::Instance = nullptr;
CSceneMgr::CSceneMgr()
	:NewScene(SCENE::SCENE_END), NowScene(SCENE::SCENE_END), Scene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENE::ID ID)
{
	NewScene = ID;

	if (NewScene != NowScene)
	{
		SAFE_DELETE(Scene);

		switch (NewScene)
		{
		case SCENE::SCENE_LOGO:
			Scene = new CLogo;
			break;
		case SCENE::SCENE_MENU:
			Scene = new CMyMenu;
			break;
		case SCENE::SCENE_STAGE:
			Scene = new CStage;
			break;
		case SCENE::SCENE_ENDING:
			Scene = new CEnding;
			break;
		}
		Scene->Initialize();
		NowScene = NewScene;
	}
}

void CSceneMgr::Update()
{
	Scene->Update();
}

void CSceneMgr::Late_Update()
{
	Scene->Late_Update();
}

void CSceneMgr::Render(HDC DC)
{
	Scene->Render(DC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(Scene);
}

RECT & CSceneMgr::Set_Wall()
{
	return dynamic_cast<CStage*>(Scene)->Set_StageWall();
}
