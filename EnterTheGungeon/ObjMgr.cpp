#include "stdafx.h"
#include "Obj.h"
#include "Player.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "Break_Check.h"

CObjMgr* CObjMgr::Instance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJ::ID_END; ++i)
	{
		for (auto& iter = Obj_List[i].begin(); iter != Obj_List[i].end();)
		{
			(*iter)->Update();
			OBJ::DEAD_OR_ALIVE Survial = (*iter)->Set_Survival();
			if (Survial == OBJ::DEAD)
			{
				SAFE_DELETE((*iter));
				iter = Obj_List[i].erase(iter);
			}
			else
				++iter;

		}
	}
	if (CSceneMgr::Get_Instance()->Set_NowScene() == SCENE::SCENE_STAGE)
	{
		for (auto& Nowiter = Obj_List[OBJ::MONSTER].begin(); Nowiter != Obj_List[OBJ::MONSTER].end(); ++Nowiter)
		{
			CBreak_Check::MonsterCheck((*Nowiter), Obj_List[OBJ::MONSTER]);
		}

		if (!Obj_List[OBJ::MONSTERBULLET].empty() || !Obj_List[OBJ::BULLET].empty())
		{
			if (static_cast<CPlayer*>(Obj_List[OBJ::PLAYER].front())->Set_STATE() != STATE::NOW::TUMBLING)
				CBreak_Check::SphereRectCheck(Obj_List[OBJ::PLAYER], Obj_List[OBJ::MONSTERBULLET]);

			CBreak_Check::SphereRectCheck(Obj_List[OBJ::MONSTER], Obj_List[OBJ::BULLET]);
			CBreak_Check::BulletWallCheck(Obj_List[OBJ::MONSTERBULLET], CSceneMgr::Get_Instance()->Set_Wall());
		}
	}

}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJ::ID_END; ++i)
	{
		for (auto& iter : Obj_List[i])
			iter->Last_Upate();
	}

	if(CSceneMgr::Get_Instance()->Set_NowScene() == SCENE::SCENE_STAGE)
		CBreak_Check::BulletWallCheck(Obj_List[OBJ::BULLET], CSceneMgr::Get_Instance()->Set_Wall());
}

void CObjMgr::Render(HDC DC)
{
	for (int i = 0; i < OBJ::ID_END; ++i)
	{
		for (auto& iter : Obj_List[i])
			iter->Render(DC);
	}
}


void CObjMgr::Release()
{
	for (int i = 0; i < OBJ::ID_END; ++i)
	{
		for_each(Obj_List[i].begin(), Obj_List[i].end(), Safe_Delete<CObj*>);
		Obj_List[i].clear();
	}
}


void CObjMgr::Get_AddObj(OBJ::ID ID, CObj * Obj)
{
	Obj_List[ID].emplace_back(Obj);
}

void CObjMgr::Delete_ID(OBJ::ID ID)
{
	for_each(Obj_List[ID].begin(), Obj_List[ID].end(), Safe_Delete<CObj*>);
	Obj_List[ID].clear();
}

ABILITY & CObjMgr::Get_AbilityInfo()
{
	ABILITY& Tmep = Obj_List[OBJ::PLAYER].front()->Set_AbilityInfo();
	return Tmep;
}
