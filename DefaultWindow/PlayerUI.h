#pragma once
#include "Obj.h"
class PlayerUI :
    public CObj
{
public:
    PlayerUI();
     ~PlayerUI();




public:
    virtual void Initialize();
    virtual int Update();
    virtual void Late_Update();
    virtual void Render(HDC hDC);
    virtual void Release();

private:
    float m_fMaxHp;
    float m_fCurHp;

    float m_fPercent;

   // INFO m_tInfo;
    RECT m_tInnerRect;

};

