#pragma once

#include "Obj.h"
#include "Shield.h"

class PlayerUI;


class CPlayer : public CObj
{
	enum PLAYERSTATE { IDLE, RUN, JUMP, ATTACK, HIT, DEAD, PS_END };
	enum WEAPONMODE {GUN,SWORD,END};
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


	static void Destroy_Instance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
private:

	static CObj* m_Instance;




public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;


	void		Set_SC_ID(SCENEID _SC_ID) { LineSC = _SC_ID; }
public:
	CObj* Get_Player() { return this; }

public:
	void		Set_Posin(POINT _Posin) { m_tPosin = _Posin; }
	POINT		Get_Posin() { return m_tPosin; }

	bool		IsDead() { return m_bDead; }
	bool		Posin_half_Check();


private:
	void		Key_Input();
	void		Jump();
	void		Offset();
	void		Set_Posin();
	void		Motion_Change();
	void		WeaponChage();
private:
	POINT				m_tPosin;
	CObj*				m_pMouse;
	float				m_fDiagonal;

	float				m_fJumpPower;
	float				m_fJumpTime;

	float				m_fPower;
	float				m_fAccelTime;




	float				m_InitSpeedX = 0.0f;
	float				m_InitSpeedY = 0.0f;

	float				m_InitX = 0.0f;
	float				m_InitY = 0.0f;
	float				m_t = 0.0f;
	
	float				m_fGravity = 9.8f;



	bool				IsGround;

	int					nSoundCount;

	//CObj* PlayerUI_HpBar;
	SCENEID				LineSC;

	CObj*	m_pWeaponList[END];
	int					DashCount;
	bool				m_bJump;
	WEAPONMODE			m_eWeaponMode;
	

	TCHAR* m_PreImage;
	TCHAR* m_CurImage;
	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;

};

// ������ ������ �̿��Ͽ� �÷��̾ �����ϴ� ���¸� ������

// Y = �Ŀ� * sin(��) * �ð� - �߷�(9.8f) * �ð��� ���� / 2

