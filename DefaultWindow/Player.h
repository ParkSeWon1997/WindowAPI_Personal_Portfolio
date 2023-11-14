#pragma once

#include "Obj.h"
#include "Shield.h"

class AnimSprite;


class CPlayer :	public CObj
{
	enum PLAYERSTATE { IDLE, WALK, JUMP,ATTACK, HIT, DEAD, PS_END };

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
	float				AnimTime;
	int					m_AnimIndex;

	vector<vector<TCHAR*>>	m_AnimBox[PS_END];
	vector<TCHAR*>			m_IDLE_Sprite;
	vector<TCHAR*>			m_JUMPSprite;
	vector<TCHAR*>			m_RUNSprite;
	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;
	
};

// 포물선 공식을 이용하여 플레이어가 점프하는 상태를 만들어라

// Y = 파워 * sin(θ) * 시간 - 중력(9.8f) * 시간의 제곱 / 2

