#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	~CPlayer();
public:
	enum KEYDOWN { FRONT, BACK, LEFT, RIGHT, RI_FRONTFWORD, LF_FRONTFWORD, RI_BACKFWORD, LF_BACKFWORD, KEYEND};
	
public:
	void Key_Check();
	void OffSet();
	void Scene_Change();
	void LookMouse();
	void Player_Move();
	void Weapon_Change();
	
public:
	inline bool	Set_TurnImage() { return  TurnImage; }
	inline STATE::NOW Set_STATE() { return NowState; }
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
	
private:
	STATE::NOW	NowState;
	STATE::NOW	NewState;
	int		WeaponChice;

	KEYDOWN	KeyDown;

	bool	TurnImage;
	bool	TumblingState;
	HFONT	MyFont;
	HFONT	OldFont;
};


#endif // !__PLAYER_H__
