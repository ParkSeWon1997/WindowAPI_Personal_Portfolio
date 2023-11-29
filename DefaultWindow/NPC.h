#pragma once
#include "Obj.h"
class NPC :
    public CObj
{

	enum ImageSTATE { IDLE=0,  PS_END };

public:
	NPC();
	virtual ~NPC();


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


public:
	void Motion_Change();
	void Set_Interacted(bool _IsInteracted) { IsInteracted = _IsInteracted; }


	void Create_Weapon();

	void Move();


private:

	bool	IsInteracted;

	//마을 돌아다니는 용도
	float	mDirX = 1.0f;
	float	mDirY = 1.0f;
	ImageSTATE			m_ePreState = PS_END;
	ImageSTATE			m_eCurState = PS_END;



};

