#pragma once
#include "Obj.h"

class CollisionBox;

class Sword :
    public CObj
{

public:
    Sword();
    virtual ~Sword();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();


public:
    void    Swing(bool _IsSwing);
    float   Get_SwordDamage() { return m_fSwordDamage; }
    void    AttachCollisionBox(float _X,float _Y);
    void    SwordEndPoint();

private:
    float               m_RotateAngle;
    float				m_fSwordDamage;
    bool                IsSwing;
    float               m_fDiagonal;
    int                 CollisionBOxCount = 0;
    POINT               SwordEND;

    CObj* CollisionBoxQue[1];

};

