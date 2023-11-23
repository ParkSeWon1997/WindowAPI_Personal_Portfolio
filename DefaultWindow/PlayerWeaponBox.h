#pragma once
#include "Obj.h"
class PlayerWeaponBox :
    public CObj
{
public:
    PlayerWeaponBox();
    virtual ~PlayerWeaponBox();





public:
    virtual void Initialize();
    virtual int Update();
    virtual void Late_Update();
    virtual void Render(HDC hDC);
    virtual void Release();


    void    Set_ImageKey(TCHAR* _Key) { WeaponImagwKey = _Key; }

private:
    TCHAR* WeaponImagwKey;

   
};

