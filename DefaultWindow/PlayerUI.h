#pragma once
#include "Obj.h"
class PlayerUI :
    public CObj
{
public:
    PlayerUI();
	virtual ~PlayerUI();




public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:
    float m_fMaxHp;
    float m_fCurHp;

    float m_fPercent;

    INFO m_tInfo;
    RECT m_tInnerRect;

};

