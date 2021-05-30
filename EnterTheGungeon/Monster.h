#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__


#include "Obj.h"
class CMonster : public CObj
{
public:
	explicit CMonster();
	virtual ~CMonster();
	
public:
	void Scene_Change();
	void MonsterPos();

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


#endif // !__MONSTER_H__