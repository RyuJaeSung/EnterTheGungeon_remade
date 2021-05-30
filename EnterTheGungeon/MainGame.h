#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMainGame
{
public:
	explicit CMainGame();
	virtual ~CMainGame();

public:
	void Initialize();
	void Update();
	void Last_Upate();
	void Render();
	void Release();
	
private:
	HDC		m_DC;
};


#endif // !__MAINGAME_H__