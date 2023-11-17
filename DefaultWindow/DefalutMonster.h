#pragma once
#include "Monster.h"
class DefalutMonster :
    public CMonster
{

	enum ImageSTATE { IDLE, ATTACK, DEAD, PS_END };
public:
    DefalutMonster();
	virtual ~DefalutMonster();


public:
	 virtual void Initialize() override;
	 virtual int Update() override;
	 virtual void Late_Update() override;
	 virtual void Render(HDC hDC) override;
	 virtual void Release() override;

public:
	void Motion_Change();
	void Default_Pattern();


	 ImageSTATE			m_ePreState;
	 ImageSTATE			m_eCurState;

};

