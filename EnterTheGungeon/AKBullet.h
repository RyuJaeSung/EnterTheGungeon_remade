#pragma once
#ifndef __AKBULLET_H__
#define __AKBULLET_H__

#include "Obj.h"
class CAKBullet : public CObj
{
public:
	explicit CAKBullet();
	virtual ~CAKBullet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
};


#endif // !__AKBULLET_H__