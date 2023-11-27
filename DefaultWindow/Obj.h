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
	void			Set_Info(float _fX,float _fY,float _fCX,float _fCY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;


	}
	void			Set_Dead() { m_bDead = true; }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void			Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float			Get_Speed() { return m_fSpeed; }

	float			Get_HP() { return m_fHP; }
	void			Set_HP(float _HP) { m_fHP = _HP; }
	void			TakeDamage(float _Damage) { m_fHP -= _Damage; }

	float			GetDamage() { return m_fDamage; }
	void			SetDamage(float _Damage) { m_fDamage = _Damage; }
	

	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }
	
	bool			Get_Dead() { return m_bDead; }
	

	void			Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void			Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	RENDERID		Get_RenderID() { return m_eRender; }


	//추가
	float			Get_Target_InitX() {	return m_fTargetInitX;}
	float			Get_Target_InitY() {	return m_fTargetInitY;}
	void			Set_Target_InitX(float _Target_X) { m_fTargetInitX = _Target_X; }
	void			Set_Target_InitY(float _Target_Y) { m_fTargetInitY = _Target_Y; }

public:
	virtual void	Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;

	

protected:
	void		Update_Rect();
	void		Move_Frame();
	bool		Turn_By_Player() {};

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	DIRECTION	m_eDir;
	RENDERID	m_eRender;

	CObj*		m_pTarget;

	//추가
	float m_fHP;
	float m_fDamage;
	float m_fTargetInitX;
	float m_fTargetInitY;
	bool  m_IsGround;


	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;
	ULONGLONG		dwFrameTime=GetTickCount64();

	TCHAR*		m_pStateKey;
	TCHAR*		m_pFrameKey;
};

