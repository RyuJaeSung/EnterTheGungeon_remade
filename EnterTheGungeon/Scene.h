#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__


class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC DC) = 0;
	virtual void Release() = 0;

};


#endif // !__SCENE_H__