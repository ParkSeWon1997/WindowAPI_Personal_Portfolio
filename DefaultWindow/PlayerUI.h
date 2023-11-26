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

    void    Set_UI_HpBar(float _MaxHp, float _CurHp);

 



private:

    CObj* m_pPlayerHpBar;

};

