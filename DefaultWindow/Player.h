#pragma once

#include "Obj.h"
#include "Shield.h"

class AnimSprite;


class CPlayer :	public CObj
{
	enum PLAYERSTATE { IDLE, RUN, JUMP,ATTACK, HIT, DEAD, PS_END };
	enum PLAYERLEFT {LEFT};
	
public:
	CPlayer();
	virtual ~CPlayer();


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




private:
	void		Key_Input();
	void		Jump();
	void		Offset();
	void		Motion_Change();

private:
	POINT				m_tPosin;
	float				m_fDiagonal;

	bool				m_bJump;
	float				m_fPower;
	float				m_fAccelTime;
	float				Start_Animation;
	float				End_Animation;

	float					Damage;
	float					HP;

	int					DashCount;


	vector<vector<TCHAR*>>	m_AnimBox[PS_END];
	vector<TCHAR*>			m_IDLE_Sprite;
	vector<TCHAR*>			m_JUMPSprite;
	vector<TCHAR*>			m_RUNSprite;
	TCHAR* m_PreImage;
	TCHAR* m_CurImage;
	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;
	
};

// ������ ������ �̿��Ͽ� �÷��̾ �����ϴ� ���¸� ������

// Y = �Ŀ� * sin(��) * �ð� - �߷�(9.8f) * �ð��� ���� / 2

