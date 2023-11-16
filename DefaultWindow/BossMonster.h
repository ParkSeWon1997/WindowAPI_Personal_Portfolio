#pragma once
#include "Monster.h"
class BossMonster :
    public CMonster
{
	enum ImageSTATE { IDLE, ATTACK, HIT, DEAD, PS_END };


public:
	BossMonster();
	virtual ~BossMonster();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	virtual void Motion_Change() override;


private:
	void Boss_pattern();






private:
	ImageSTATE			m_ePreState;
	ImageSTATE			m_eCurState;

};

