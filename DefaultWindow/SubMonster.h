#pragma once
#include "Monster.h"
class SubMonster :
    public CMonster
{

	enum SUBMOSTER_TATE {IDLE,ATTACK,TARGET_SHOT,MOVE_TO_BOSS,END };


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




	void Motion_Change();


private:
	void SubMonster_pattern();


private:
	float  Monster_AngleAdd;
	float m_fDistance;

	int FrameChek = 0;
	int FireCount = 0;
	int GFireCount = 0;

private:
	SUBMOSTER_TATE	SubState;

};

