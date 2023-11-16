#pragma once

#include "Obj.h"
#include "Shield.h"




class CPlayer :	public CObj
{
	enum PLAYERSTATE { IDLE, RUN, JUMP,ATTACK, HIT, DEAD, PS_END };
	
private:
	CPlayer();
	virtual ~CPlayer();

public:
	static CObj* Get_Instance()
	{
		if (!m_Instance)
			m_Instance = new CPlayer;

		return m_Instance;
	}
private:
	static CObj* m_Instance;




public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;




public:
	float		Get_Damage() { return Damage; }
	void		Set_Damage(float _Damage) { Damage = _Damage; }

	float		Get_HP() { return HP; }
	void		Set_HP(float _HP) { HP = _HP; }

	void		Set_Posin(POINT _Posin) { m_tPosin = _Posin; }
	POINT		Get_Posin() { return m_tPosin; }

	bool		IsDead() { return m_bDead; }


private:
	void		Key_Input();
	void		Jump();
	void		Offset();
	void		Set_Posin();
	bool		Posin_half_Check();
	void		Motion_Change();

private:
	POINT				m_tPosin;
	float				m_fDiagonal;


	CObj*				 m_pMouse;

	bool				m_bJump;
	float				m_fPower;
	float				m_fAccelTime;

	float					Damage;
	float					HP;

	int					DashCount;



	TCHAR* m_PreImage;
	TCHAR* m_CurImage;
	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;
	
};

// 포물선 공식을 이용하여 플레이어가 점프하는 상태를 만들어라

// Y = 파워 * sin(θ) * 시간 - 중력(9.8f) * 시간의 제곱 / 2

