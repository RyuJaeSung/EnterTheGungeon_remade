#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct ObjInfo
{
	float x;
	float y;
	SIZE size;
}INFO;

typedef struct Line_Pos
{
	Line_Pos() { ZeroMemory(this, sizeof(Line_Pos)); }
	Line_Pos(float x, float y) :fX(x), fY(y) {}
	float fX;
	float fY;
}POS;

typedef struct Line_Info
{
	Line_Info() { ZeroMemory(this, sizeof(Line_Info)); }
	Line_Info(POS& x, POS& y) :Left_Pos(x), Right_Pos(y) {}
	POS Left_Pos;
	POS Right_Pos;
}Line;

typedef struct Frame_Info
{
	int		FrameStart;
	int		FrameMotion;
	int		FrameEnd;
	DWORD	FrameSpeed;
	DWORD	FrameTime;
}FRAME;

typedef struct Ability_Info
{
	int Hp;
	int MaxHp;
	int	Attack;
	int Shield;
	int Bomb;
}ABILITY;

#endif // !__STRUCT_H__
