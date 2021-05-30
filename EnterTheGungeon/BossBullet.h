#pragma once
#ifndef __BOSSBULLET_H__
#define __BOSSBULLET_H__

#include "Obj.h"
class CBossBullet :	public CObj
{
public:
	explicit CBossBullet();
	virtual ~CBossBullet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
};


#endif // !__BOSSBULLET_H__