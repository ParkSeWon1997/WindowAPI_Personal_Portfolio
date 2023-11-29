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



    //플레이어의 부착하기 전에 아이템을 보여주기 위한 용도
    bool m_bJump;

    float m_fPower = 0;
    float m_fAccelTime = 0;
};

