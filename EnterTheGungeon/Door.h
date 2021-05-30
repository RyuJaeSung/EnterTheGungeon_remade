#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__


#include "Obj.h"
class CDoor : public CObj
{
public:
	explicit CDoor();
	virtual ~CDoor();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Last_Upate() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
};


#endif // !__DOOR_H__