#pragma once
#include "Monster.h"
class BossMonster :
    public CMonster
{
	enum ImageSTATE { IDLE, ATTACK, HIT, DEAD, PS_END };
	enum BOSSSTATE {SC_CREATE_SUB,SC_IDLE,SC_EASY,SC_NORMAL,SC_HARD,SC_DEAD,SC_END};


public:
	BossMonster();
	BossMonster(float _X,float _Y);
	virtual ~BossMonster();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void Motion_Change();


private:
	void Boss_pattern();






private:
	ImageSTATE			m_ePreState;
	ImageSTATE			m_eCurState;
private:
	BOSSSTATE			m_eBossSTATE;

	int					CreateSubCount = 0;


	list<CObj*>			m_pSubMonsterList;
	//CObj*				m_pSubMonster1;
	//CObj*				m_pSubMonster2;
	//CObj*				m_pSubMonster3;
	//CObj*				m_pSubMonster4;

};

