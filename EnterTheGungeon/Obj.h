#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	explicit CObj();
	virtual ~CObj();
	
public:
	inline void Set_Rect(RECT& rc) { m_Rect = rc; }
	inline void Set_Dead() { DeadorAlive = OBJ::DEAD; }
	inline void Set_Pos(float x, float y) { m_Info.x = x; m_Info.y = y; }
	inline void Set_FrameKey(TCHAR* Key) { FrameKey = Key; }
	inline void Set_PosX(float x) { m_Info.x += x; }
	inline void Set_PosY(float y) { m_Info.y += y; }
	inline void Set_Damage(int damage) { m_Ability.Hp -= damage; }
	inline void Set_Angle(float Angle) { m_fAngle = Angle; }
	inline ABILITY& Set_AbilityInfo() { return m_Ability; }
	inline OBJ::DEAD_OR_ALIVE Set_Survival() { return DeadorAlive; }

public:
	void	Get_Degree();
	inline	float	Get_Angle() { return m_fAngle; }
	inline	INFO&	Get_Info() { return m_Info; }
	inline	RECT&	Get_RECT() { return m_Rect; }
	inline	int		Get_Damage() { return m_Ability.Attack; }
	inline	int		Get_MaxMagazine() {	return MaxMagazine;	}

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Last_Upate() = 0;
	virtual void Render(HDC DC) = 0;
	virtual void Release() = 0;

public:
	void	Update_Rect();
	void	Frame_Move();

protected:
	INFO	m_Info;
	RECT	m_Rect;
	ABILITY	m_Ability;
	FRAME	m_Frame;

	int		MaxMagazine;
	float	m_fAngle;
	float	m_Speed;
	TCHAR*	FrameKey;
	OBJ::DEAD_OR_ALIVE	DeadorAlive;
};
#endif // !__OBJ_H__