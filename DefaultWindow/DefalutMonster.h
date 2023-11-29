#pragma once
#include "Monster.h"
class DefalutMonster :
    public CMonster
{

	enum ImageSTATE { IDLE, ATTACK, DEAD, PS_END };
public:
    DefalutMonster();
    DefalutMonster(float _X,float _Y);
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

	void Move();
	CObj* Fire(DIRECTION _eDir);


private:
	int FrameCheck = 0;


	//방향을 바꾸기 위한 스칼라 성분
	float mDirX = 1.0f;
	float mDirY = 1.0f;
	 ImageSTATE			m_ePreState;
	 ImageSTATE			m_eCurState;

};

