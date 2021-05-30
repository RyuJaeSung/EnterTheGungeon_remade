#pragma once
#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

public:
	inline CObj* Set_Player() { return Obj_List[OBJ::PLAYER].front(); }
	inline CObj* Set_Gun() { return Obj_List[OBJ::GUN].front(); }
	inline CObj* Set_Obj(OBJ::ID ID) { return Obj_List[ID].front(); }
	inline list<CObj*> Set_List(OBJ::ID ID) { return Obj_List[ID]; };
	inline bool	 Set_FightOn() { if (Obj_List[OBJ::MONSTER].empty()) return true; return false; }
	inline bool	 Set_CreateDoor() { if (Obj_List[OBJ::DOOR].empty()) return true; return false; }
	inline bool  Set_Size() { if (Obj_List[OBJ::MONSTER].size() <= 2) return true; return false; }

public:
	void			Get_AddObj(OBJ::ID ID, CObj* Obj);
	ABILITY&		Get_AbilityInfo();

public:
	void			Delete_ID(OBJ::ID ID);

public:
	inline static CObjMgr* Get_Instance()
	{
		if (!Instance)
			Instance = new CObjMgr;
		return Instance;
	}
	inline static void Destroy_Instance()
	{
		SAFE_DELETE(Instance);
	}

private:
	static CObjMgr* Instance;
	list<CObj*>		Obj_List[OBJ::ID_END];
};



#endif // !__OBJMGR_H__