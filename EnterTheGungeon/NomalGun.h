#pragma once
#ifndef __NOMALGUN_H__
#define __NOMALGUN_H__
#include "Obj.h"

class CNomalGun : public CObj
{
public:
	explicit CNomalGun();
	virtual ~CNomalGun();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

public:
	inline int Set_Magazine() { return MaxMagazine; }

public:
	CObj*	Create_Bullet();
	void	Scene_Change();
	void	Key_Check();
	void	Gun_Turn();
	void	Scene_Turn();

private:
	POINT		TurnPoint[3];
	POINT		Posin;
	bool		BulletMotion;

	DWORD		BulletSpeed;
	GUN::GUNSTATE	NowState;
	GUN::GUNSTATE	NewState;
};


#endif // !__NOMALGUN_H__