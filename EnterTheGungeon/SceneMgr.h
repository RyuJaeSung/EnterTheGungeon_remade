#pragma once
#ifndef __SCENNEMGR_H__
#define __SCENNEMGR_H__

class CScene;
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Scene_Change(SCENE::ID ID);
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

public:
	RECT& Set_Wall();
	inline SCENE::ID Set_NowScene() { return NowScene; }
	inline void Set_NewScene(SCENE::ID ID) { NewScene = ID; }
public:
	inline static CSceneMgr* Get_Instance()
	{
		if (!Instance)
			Instance = new CSceneMgr;
		return Instance;
	}

	inline static void Destroy_Instance()
	{
		SAFE_DELETE(Instance);
	}

private:
	static CSceneMgr*	Instance;
	CScene*				Scene;

	SCENE::ID			NowScene;
	SCENE::ID			NewScene;
};


#endif // !__SCENNEMGR_H__