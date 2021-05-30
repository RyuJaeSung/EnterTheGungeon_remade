#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__


#include "Obj.h"
class CBullet : 	public CObj
{
public:
	explicit CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
};


#endif // !__BULLET_H__