#pragma once
#include "Obj.h"
class Gun :
    public CObj
{
public:
    Gun();
   virtual ~Gun();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();


public:
    void    FIre(bool _IsShot);
    float   Get_GunDamage() { return m_fGunDamage; }



private:
    float				m_fGunDamage;
      


    list<CObj*>         m_pBulletList;

};

