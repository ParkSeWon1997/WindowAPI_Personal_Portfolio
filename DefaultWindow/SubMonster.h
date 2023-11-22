#pragma once
#include "Monster.h"
class SubMonster :
    public CMonster
{




public:
	SubMonster();
	SubMonster(float _X, float _Y);
	virtual ~SubMonster();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void SetSubState(SUBMOSTER_STATE _ID) { SubState = _ID; }
	float Get_m_fRotateAngle() { return m_fRotateAngle; }
	//360µµ °ø°Ý
	void Attack();
	void Target_Attack();
	void MoveToBoss();
	void AroundBOss();
	void MoveToPoint(float _X, float _Y) 
	{ 
		m_tInfo.fX = _X;
		m_tInfo.fY = _Y; 
	}
	void MoveToWidth(float _X)
	{
		if(!_X==m_tInfo.fX)
		m_tInfo.fX += m_fSpeed;
	}

	void CheckOverrWindow();


	void Motion_Change();


private:
	void SubMonster_pattern();


private:
	float  Monster_AngleAdd;
	float m_fDistance;

	int FrameChek = 0;
	int FireCount = 0;
	int GFireCount = 0;

	float m_fRotateAngle=0;

private:
	SUBMOSTER_STATE	SubState;

};

