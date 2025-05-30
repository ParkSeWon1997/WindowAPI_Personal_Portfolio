#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize()	PURE;
	virtual void	Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;


protected:
		void	Move_Frame();

protected:
	FRAME		m_tFrame;
	ULONGLONG		dwFrameTime = GetTickCount64();
};

