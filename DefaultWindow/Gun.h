#pragma once
#include "Obj.h"
class Gun :
    public CObj
{
public:
    Gun();
    ~Gun();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();


public:
    float   Get_GunDamage() { return m_fGunDamage; }



private:
    float				m_fGunDamage;
 


    list<CObj*>         m_pBulletList;

};
