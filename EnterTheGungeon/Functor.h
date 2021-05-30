#pragma once
#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

class CStrCmp
{
public:
	CStrCmp(const TCHAR* src)
		: String(src)
	{
	}

public:
	template<typename T>
	bool operator()(T& obj)
	{
		return !lstrcmp(String, obj.first);
	}

private:
	const TCHAR* String;
};



template <typename T>
void Safe_Delete(T& obj)
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

#endif // !__FUNCTOR_H__
