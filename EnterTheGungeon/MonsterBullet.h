#pragma once
#ifndef __MONSTERBULLET_H__
#define __MONSTERBULLET_H__

#include "Obj.h"
class CMonsterBullet :	public CObj
{
public:
	explicit CMonsterBullet();
	virtual ~CMonsterBullet();
public:
	void TargetPos();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

private:
	bool	TargetAngle;
};


#endif // !__MONSTERBULLET_H__