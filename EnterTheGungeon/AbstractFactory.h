#pragma once
#ifndef __ADSTRACTFACTROY_H__
#define __ADSTRACTFACTROY_H__

class CObj;
template <typename T>
class Create_OBJ
{
public:
	static CObj* Create()
	{
		CObj* obj = new T;
		obj->Initialize();

		return obj;
	}

	static CObj* Create(float x, float y)
	{
		CObj* obj = new T;
		obj->Set_Pos(x, y);
		obj->Initialize();

		return obj;
	}

	static CObj* Create(float x, float y, float Angle)
	{
		CObj* obj = new T;
		obj->Set_Pos(x, y);
		obj->Set_Angle(Angle);
		obj->Initialize();
		
		return obj;
	}

	static CObj* Create(RECT& rc)
	{
		CObj* obj = new T;
		obj->Set_Rect(rc);
		obj->Initialize();

		return obj;
	}
};



#endif // !__ADSTRACTFACTROY_H__
