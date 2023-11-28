#pragma once
#include "Obj.h"
class HpPotion :
    public CObj
{
	enum HpItemImageSTATE { IDLE=0,
		PS_END };

public:
	HpPotion();
	virtual ~HpPotion();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Motion_Change();

	void Move();

	void DropMove();


private:
	int FrameCheck = 0;


	bool	m_bJump = false;
	float m_fPower = 0;
	float m_fAccelTime = 0;

	HpItemImageSTATE			m_ePreState;
	HpItemImageSTATE			m_eCurState;




};

