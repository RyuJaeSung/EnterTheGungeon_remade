#pragma once
#ifndef __LOGO_H__
#define __LOGO_H__

#include "Scene.h"
class CLogo :	public CScene
{
public:
	explicit CLogo();
	virtual ~CLogo();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

private:
	DWORD	OneselfScene;
};


#endif // !__LOGO_H__