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

	void Create_Weapon();


	ImageSTATE			m_ePreState = PS_END;
	ImageSTATE			m_eCurState = PS_END;



};

