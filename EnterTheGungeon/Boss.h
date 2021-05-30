#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "Obj.h"
class CBoss :	public CObj
{
public:
	explicit CBoss();
	virtual ~CBoss();
	
public:
	enum BOSSPATTERN { INTRO, IDLE, RUN, ATTACK, CONTINUOUS, SPIN, DEAD, END};

public:
	void Scene_Change();
	void Boss_Intro(HDC DC);
	void Boss_Attack(HDC DC);
	void Boss_Spin(HDC DC);
	void Boss_ContinuousAttack(HDC DC);
	void Boss_Idle(HDC DC);
	void Boss_Run(HDC DC);
	void Boss_Dead(HDC DC);
	void Boss_HpBar(HDC DC);

public:
	bool	Turn_Run();
	inline bool Now_Intro() { if (NowMonsterPos == INTRO) return true;	return false; }

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

private:
	int		Pattern;
	RECT	AttackRange;
	bool	BulletTime;

	BOSSPATTERN	NowMonsterPos;
	BOSSPATTERN	NewMonsterPos;
};


#endif // !__BOSS_H__