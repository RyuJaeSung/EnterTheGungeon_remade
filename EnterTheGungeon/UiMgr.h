#pragma once
#ifndef __UIMGR_H__
#define __UIMGR_H__

class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

private:
	void HpRender(HDC DC);
	void MagazineRender(HDC DC);

public:
	inline static CUiMgr* Get_Instance()
	{
		if (!Instance)
			Instance = new CUiMgr;
		return Instance;
	}
	inline static void Dsetroy_Instance()
	{
		SAFE_DELETE(Instance);
	}


private:
	static CUiMgr* Instance;
	int		Hp;
	int		MaxHp;
	int		shield;
	
	int		MaxMagazine;
	
};


#endif // !__UIMGR_H__