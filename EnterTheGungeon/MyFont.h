#pragma once
#ifndef __MYFONT_H__
#define __MYFONT_H__

class CMyFont
{
public:
	CMyFont();
	~CMyFont();

public:
	enum Menu { START, OPTION, QUIT, END };

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

private:
	HDC		FontDC;
	RECT	FontPos[END];
	
	HFONT	MenuFont;
	HFONT	OldFont;
	Menu	NowChoice;
};


#endif // !__MYFONT_H__
