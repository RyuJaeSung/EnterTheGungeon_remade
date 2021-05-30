#pragma once
#ifndef __ENDING_H__
#define __ENDING_H__

#include "Scene.h"
class CEnding :	public CScene
{
public:
	explicit CEnding();
	virtual ~CEnding();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC DC) override;
	virtual void Release() override;

private:
	POS		m_info;
	SIZE	BookSize;
	FRAME	Frame;
};


#endif // !__ENDING_H__