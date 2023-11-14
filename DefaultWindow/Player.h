#pragma once

#include "Obj.h"
#include "Shield.h"

class CPlayer :	public CObj
{
	enum PLAYERSTATE { IDLE, WALK, ATTACK, HIT, DEAD, PS_END };

public:
	CPlayer();
	virtual ~CPlayer();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

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

	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;

};

// ������ ������ �̿��Ͽ� �÷��̾ �����ϴ� ���¸� ������

// Y = �Ŀ� * sin(��) * �ð� - �߷�(9.8f) * �ð��� ���� / 2

