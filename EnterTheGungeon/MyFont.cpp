#include "stdafx.h"
#include "MyFont.h"
#include "KeyMgr.h"
#include "Break_Check.h"
#include "SceneMgr.h"

CMyFont::CMyFont()
	:NowChoice(END)
{
}


CMyFont::~CMyFont()
{
}

void CMyFont::Initialize()
{
	GetClientRect(m_ghWnd, &Client_Rect);
	MenuFont = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0,
		ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_ROMAN, L"굴림");

	for (int i = 2; i >= 0; --i)
		SetRect(&FontPos[2 - i], Client_Rect.left + 50, Client_Rect.bottom - (50 * (i + 1)) - (20 * i),
			Client_Rect.left + 210, Client_Rect.bottom - (50 * i) - (20 * i));
	NowChoice = START;
}

void CMyFont::Update()
{
}

void CMyFont::Late_Update()
{
	POINT mp;
	GetCursorPos(&mp);
	ScreenToClient(m_ghWnd, &mp);

	for (int i = 0; i < END; ++i)
	{
		if (CBreak_Check::PosRectangleCheck(mp, FontPos[i]))
			NowChoice = (Menu)i;
	}
	
	if (CBreak_Check::PosRectangleCheck(mp, FontPos[NowChoice]))
	{
		if (CKeyMgr::Get_Instane()->Key_Down(VK_LBUTTON) || CKeyMgr::Get_Instane()->Key_Down(VK_SPACE))
		{
			switch (NowChoice)
			{
			case CMyFont::START:
				CSceneMgr::Get_Instance()->Scene_Change(SCENE::SCENE_STAGE);
				return;
			case CMyFont::OPTION:
			case CMyFont::QUIT:
				DestroyWindow(m_ghWnd);
				return;
			}
		}
	}
}

void CMyFont::Render(HDC DC)
{
	FontDC = DC;
	OldFont = (HFONT)SelectObject(FontDC, MenuFont);
	SetBkMode(FontDC, TRANSPARENT);
	SetTextColor(FontDC, RGB(192, 192, 192));

	switch (NowChoice)
	{
	case CMyFont::START:
		DrawText(DC, L"옵  션", -1, &FontPos[OPTION], DT_VCENTER | DT_CENTER);
		DrawText(DC, L"게임종료", -1, &FontPos[QUIT], DT_VCENTER | DT_CENTER);
		SetTextColor(FontDC, RGB(255, 255, 255));
		DrawText(DC, L"게임시작", -1, &FontPos[START], DT_VCENTER | DT_CENTER);
		break;
	case CMyFont::OPTION:
		DrawText(DC, L"게임시작", -1, &FontPos[START], DT_VCENTER | DT_CENTER);
		DrawText(DC, L"게임종료", -1, &FontPos[QUIT], DT_VCENTER | DT_CENTER);
		SetTextColor(FontDC, RGB(255, 255, 255));
		DrawText(DC, L"옵  션", -1, &FontPos[OPTION], DT_VCENTER | DT_CENTER);
		break;
	case CMyFont::QUIT:
		DrawText(DC, L"옵  션", -1, &FontPos[OPTION], DT_VCENTER | DT_CENTER);
		DrawText(DC, L"게임시작", -1, &FontPos[START], DT_VCENTER | DT_CENTER);
		SetTextColor(FontDC, RGB(255, 255, 255));
		DrawText(DC, L"게임종료", -1, &FontPos[QUIT], DT_VCENTER | DT_CENTER);
		break;
	}
}

void CMyFont::Release()
{
	SelectObject(FontDC, OldFont);
}
