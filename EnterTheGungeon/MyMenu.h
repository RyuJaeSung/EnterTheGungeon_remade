#pragma once
#ifndef __MYMENU_H__
#define __MYMENU_H__
#include "Scene.h"

class CMyFont;
class CMyMenu : public CScene
{
public:
	explicit CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;
	
private:
	CMyFont*	Font;
};


#endif // !__MYMENU_H__
