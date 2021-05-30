#pragma once
#ifndef __SHOTGUNMAN_H__
#define __SHOTGUNMAN_H__

#include "Obj.h"
class CShotgunMan : public CObj
{
public:
	explicit CShotgunMan();
	virtual ~CShotgunMan();
	
public:
	void Scene_Change();
	void MonsterPos();
	void TargetPos();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override; 
	virtual void Release() override;

private:
	RECT	AttackRange;
	DWORD	AttackTime;
	MONSTER::POS	NowMonsterPos;
	MONSTER::POS	NewMonsterPos;
};


#endif // !__SHOTGUNMAN_H__