#pragma once
#ifndef __GUNNET_H__
#define __GUNNET_H__

#include "Obj.h"
class CGunnet :	public CObj
{

public:
	enum STATE { ATTACK, IDLE, END};

public:
	explicit CGunnet();
	virtual ~CGunnet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

public:
	void Scene_Change();

private:
	DWORD	AttackTime;
	STATE	NowMonsterPos;
	STATE	NewMonsterPos;
};


#endif // !__GUNNET_H__