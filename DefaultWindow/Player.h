#pragma once

#include "Obj.h"
#include "Shield.h"




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
private:
	static CObj* m_Instance;




public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;




public:
	float		Get_Damage() { return m_fPlayerDamage; }
	void		Set_Damage(float _Damage) { m_fPlayerDamage = _Damage; }

	float		Get_HP() { return m_fPlayerHP; }
	void		Set_HP(float _HP) { m_fPlayerHP = _HP; }

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
	void		WeaponChage();
private:
	POINT				m_tPosin;
	CObj*				m_pMouse;
	float				m_fDiagonal;
	float				m_fPower;
	float				m_fAccelTime;

	float				m_fPlayerDamage;
	float				m_fPlayerHP;

	//�ʱ� �ӵ�
	//��� �ð�
	//float				




	list<CObj*>		m_pWeaponList;
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

