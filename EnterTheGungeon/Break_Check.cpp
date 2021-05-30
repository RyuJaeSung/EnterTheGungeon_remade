#include "stdafx.h"
#include "Break_Check.h"
#include "Obj.h"


CBreak_Check::CBreak_Check()
{
}


CBreak_Check::~CBreak_Check()
{
}

void CBreak_Check::SphereRectCheck(list<CObj*>& Rect, list<CObj*>& sp)
{
	RECT Dst_rc;
	for (auto& Dst : Rect)
	{
		Dst_rc = Dst->Get_RECT();
		for (auto& Src : sp)
		{
			RECT Dst_rcEx;
			SetRect(&Dst_rcEx, Dst_rc.left - (Src->Get_Info().size.cx / 2), Dst_rc.top - (Src->Get_Info().size.cy / 2),
				Dst_rc.right + (Src->Get_Info().size.cx / 2), Dst_rc.bottom + (Src->Get_Info().size.cy / 2));

			if ((Src->Get_Info().x >= Dst_rcEx.left && Src->Get_Info().y >= Dst_rcEx.top)
				&& (Src->Get_Info().x <= Dst_rcEx.right && Src->Get_Info().y <= Dst_rcEx.bottom))
			{
				Dst->Set_Damage(Src->Get_Damage());
				Src->Set_Dead();
			}
		}
	}

}

bool CBreak_Check::PosRectangleCheck(POINT & MP, RECT & Rect)
{
	if((Rect.left <= MP.x && Rect.right >= MP.x) && 
		(Rect.top <= MP.y && Rect.bottom >= MP.y))
		return true;

	return false;
}

bool CBreak_Check::WallCheck(CObj* charactor, RECT & Fixed)
{
	bool move = false;

	if (charactor->Get_RECT().left <= Fixed.left)
	{
		charactor->Set_PosX((float)(Fixed.left - charactor->Get_RECT().left));
		move = true;
	}
	if (charactor->Get_RECT().right >= Fixed.right)
	{
		charactor->Set_PosX((float)(Fixed.right - charactor->Get_RECT().right));
		move = true;
	}
	if (charactor->Get_RECT().top <= Fixed.top)
	{
		charactor->Set_PosY((float)(Fixed.top - charactor->Get_RECT().top));
		move = true;
	}
	if (charactor->Get_RECT().bottom >= Fixed.bottom)
	{ 
		charactor->Set_PosY((float)(Fixed.bottom - charactor->Get_RECT().bottom));
		move = true;
	}
	return move;
}

void CBreak_Check::BulletWallCheck(list<CObj*>& bullet, RECT & Wall)
{
	if (bullet.empty())
		return;
	
	for (auto& iter : bullet)
	{
		if (Wall.left >= (*iter).Get_RECT().left || Wall.right <= (*iter).Get_RECT().right ||
			Wall.top >= (*iter).Get_RECT().top || Wall.bottom <= (*iter).Get_RECT().bottom)
			iter->Set_Dead();
	}
}


bool CBreak_Check::RectRectCheck(RECT * charactor, RECT * monter)
{

	RECT rc;
	if (IntersectRect(&rc, charactor, monter))
		return true;
	return false;
}

void CBreak_Check::MonsterCheck(CObj * Monster1, list<CObj*>& MonsterList)
{
	RECT rc;
	bool MonsterBreak = false;
	for (auto& iter = MonsterList.begin(); iter != MonsterList.end(); ++iter)
	{
		if (!MonsterBreak && Monster1 != (*iter))
			continue;

		if (Monster1 == (*iter))
		{
			MonsterBreak = true;
			continue;
		}


		if (IntersectRect(&rc, &Monster1->Get_RECT(), &(*iter)->Get_RECT()))
		{
			int BreakX = rc.right - rc.left;
			int BreakY = rc.bottom - rc.top;


			if (BreakX > BreakY)
				(*iter)->Set_PosY((float)BreakY);
			else
				(*iter)->Set_PosX((float)BreakX);
		}

	}
}

