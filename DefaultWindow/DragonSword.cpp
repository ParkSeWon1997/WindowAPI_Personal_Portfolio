#include "stdafx.h"
#include "DragonSword.h"
#include "EasyMapLindeMgr.h"
#include "PngMrg.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "Player.h"

DragonSword::DragonSword()
{
    m_fDropSpeed = 5.0f;
    
}

DragonSword::~DragonSword()
{
}

void DragonSword::Initialize()
{
    m_tInfo.fCX = 26.f;
    m_tInfo.fCY = 60.f;
    m_fDamage = 30.0f;

	m_bJump = true;
    m_eRender = GAMEOBJECT;
}

int DragonSword::Update()
{

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void DragonSword::Late_Update()
{

    if (!IsAttach_To_Player)
    {
        NotYetAttachPlayer();
    }
}

void DragonSword::Render(HDC hDC)
{
    Graphics g(hDC);

    g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"),
        (m_tInfo.fX - m_tInfo.fCX * 0.5),
        (m_tInfo.fY - m_tInfo.fCY * 0.5),
        m_tInfo.fCX, m_tInfo.fCY);


   // Rectangle(hDC,
   // 	m_tRect.left,
   // 	m_tRect.top,
   // 	m_tRect.right,
   // 	m_tRect.bottom);
}

void DragonSword::Release()
{
}

void DragonSword::Touch_To_Player()
{
    if (CCollisionMgr::Check_Sphere(CPlayer::Get_Instance(), this))
    {



    }
}

void DragonSword::NotYetAttachPlayer()
{
	float	fY(0.f);
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(&fY, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCY);
    if (m_bJump)
    {
        m_tInfo.fX += m_fDropSpeed;
        m_tInfo.fY -= (m_fPower * m_fAccelTime) - (9.0f * m_fAccelTime * m_fAccelTime * 0.5f);

        m_fAccelTime += 0.2f;

        if (bLineCol && fY < m_tInfo.fY)
        {
            m_bJump = false;
            m_fAccelTime = 0.f;
            m_tInfo.fY = fY;
        }

    }

    else if (bLineCol)
    {
        m_tInfo.fY = fY;
    }

   



}