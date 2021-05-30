#pragma once
#ifndef __LINEBULLET_H__
#define __LINEBULLET_H__

#include "Obj.h"
class ClineBullet :	public CObj
{
public:
	explicit ClineBullet();
	virtual ~ClineBullet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
	
private:
	int		Dir;
};

#endif // !__LINEBULLET_H__