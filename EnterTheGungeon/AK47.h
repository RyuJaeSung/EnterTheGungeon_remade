#pragma once
#ifndef __AK47_H__
#define __AK47_H__

#include "Obj.h"
class CAK47 : public CObj
{
public:
	explicit CAK47();
	virtual ~CAK47();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

public:
	CObj*	Create_Bullet();
	void	Scene_Change();
	void	Key_Check();
	void	Gun_Turn();
	void	Scene_Turn();

public:
	inline int Set_Magazine() { return MaxMagazine; }

private:
	POINT		TurnPoint[3];
	POINT		Posin;

	DWORD		BulletSpeed;
	GUN::GUNSTATE	NowState;
	GUN::GUNSTATE	NewState;

};


#endif // !__AK47_H__