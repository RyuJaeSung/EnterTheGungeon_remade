#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "Obj.h"

class CMouse : public CObj
{
public:
	explicit CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
};


#endif // !__MOUSE_H__