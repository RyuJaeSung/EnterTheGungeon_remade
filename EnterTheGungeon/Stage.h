#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include "Scene.h"
class CStage :	public CScene
{
public:
	enum MapList {START, STF, FRIST, FS, SECOND, ST, TERCEROS, SF, FOURTH, FB, BOSS, END };

public:
	explicit CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

public:
	void Wall_Check();
	void Create_Monster();

public:
	inline RECT& Set_StageWall() { return StageWall[MapMove]; }

private:
	RECT	StageWall[END];
	int		MapMove;
	int		MosterFight;
	bool	MakeingMonster;
};


#endif // !__STAGE_H__
