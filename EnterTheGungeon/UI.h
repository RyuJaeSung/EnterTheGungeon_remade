#pragma once
#ifndef __UI_H__
#define __UI_H__

class CUI
{
public:
	CUI();
	~CUI();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

};


#endif // !__UI_H__