#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_Direction(DIRECTION eDir)
	{
		m_eDir = eDir;
	}
	void			Set_Dead() { m_bDead = true; }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }
	bool			Get_Dead() { return m_bDead; }
	

	void			Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void			Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	RENDERID		Get_RenderID() { return m_eRender; }

public:
	virtual void	Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;

protected:
	void		Update_Rect();
	void		Move_Frame();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	DIRECTION	m_eDir;
	RENDERID	m_eRender;

	CObj*		m_pTarget;

	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;
	DWORD		dwFrameTime=GetTickCount();

	TCHAR*		m_pStateKey;
	TCHAR*		m_pFrameKey;
};

