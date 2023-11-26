#pragma once
#include "Monster.h"
class BossMonster :
    public CMonster
{
	enum ImageSTATE { IDLE, ATTACK, HIT, DEAD, PS_END };
	enum BOSS_STATE {SC_BOSS_CREATE_SUB,SC_BOSS_IDLE,SC_BOSS_EASY,SC_BOSS_NORMAL,SC_BOSS_HARD,SC__BOSS_DEAD,SC_END};


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
	bool IsSubMonsterAlive();
	void CheckSpearOverrWindow();
	void CreateSpear(int _Dir,float _X, float _Y);
	void CreateIcicle(float _X);

private:
	void Boss_pattern();






private:
	ImageSTATE			m_ePreState;
	ImageSTATE			m_eCurState;
private:
	BOSS_STATE			m_eBOSS_STATE;


	int					CreateSubCount = 0;
	int					FrameCheck = 0;
	int					CreateSpearCount = 0;
	int					CreateIcicleCount = 0;

	list<CObj*>			m_pSubMonsterList;
	//CObj*				m_pSubMonster1;
	//CObj*				m_pSubMonster2;
	//CObj*				m_pSubMonster3;
	//CObj*				m_pSubMonster4;

};

