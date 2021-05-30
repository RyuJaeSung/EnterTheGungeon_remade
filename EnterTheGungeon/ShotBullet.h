#pragma once
#ifndef __SHOTBULLET_H__
#define __SHOTBULLET_H__

#include "Obj.h"
class CShotBullet : public CObj
{
public:
	explicit CShotBullet();
	virtual ~CShotBullet();

public:
	void BulletPosX();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

private:
	bool	Direction;
};


#endif // !__SHOTBULLET_H__