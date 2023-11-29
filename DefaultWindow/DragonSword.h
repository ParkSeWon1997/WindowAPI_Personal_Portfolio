#pragma once
#include "Obj.h"
class DragonSword :
    public CObj
{
public:
    DragonSword();
    virtual ~DragonSword();
public:

    virtual void	Initialize();
    virtual int		Update();
    virtual void	Late_Update();
    virtual void	Render(HDC hDC);
    virtual void	Release();


public:
    void    Touch_To_Player();



private:
    void    NotYetAttachPlayer();





private:
    bool IsTouch_To_Player = false;
    bool IsAttach_To_Player = false;
    float m_fDropSpeed;



    //�÷��̾��� �����ϱ� ���� �������� �����ֱ� ���� �뵵
    bool m_bJump;

    float m_fPower = 0;
    float m_fAccelTime = 0;
};

