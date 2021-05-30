#pragma once
#ifndef __BREAK_CHECK_H__
#define __BREAK_CHECK_H__

class CObj;
class CBreak_Check
{
public:
	CBreak_Check();
	~CBreak_Check();

public:
	static void SphereRectCheck(list<CObj*>& Rect, list<CObj*>& sp);
	static bool PosRectangleCheck(POINT& MP, RECT& Rect);
	static bool	WallCheck(CObj* charactor, RECT& Fixed);
	static void	BulletWallCheck(list<CObj*>& bullet, RECT& Wall);
	static bool RectRectCheck(RECT* charactor, RECT* monter);
	static void MonsterCheck(CObj* Monster1, list<CObj*>& MonsterList);

};


#endif // !__BREAK_CHECK_H__