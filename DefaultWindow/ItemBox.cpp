#include "stdafx.h"
#include "ItemBox.h"
#include "PngMrg.h"
#include "EasyMapLindeMgr.h"
#include "BossMapLineMgr.h"

ItemBox::ItemBox()
{
}

ItemBox::~ItemBox()
{
}

void ItemBox::Initialize()
{
    m_tInfo.fCX = 46.f;
    m_tInfo.fCY = 32.f;
    m_pFrameKey = L"Item_Box";
    m_fHP = 20.f;
    m_bJump = true;
    m_eRender = GAMEOBJECT;
}

int ItemBox::Update()
{
    if (m_bDead) {
        if (dwFrameTime + 1500 < GetTickCount()) {
            return OBJ_DEAD;
            dwFrameTime = GetTickCount();
        }
    }

    DropMove();


    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void ItemBox::Late_Update()
{
}

void ItemBox::Render(HDC hDC)
{
    Graphics g(hDC);

    g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey),
        Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
            (m_tInfo.fY - m_tInfo.fCY * 0.5),
            m_tInfo.fCX, m_tInfo.fCY),
        m_tInfo.fCX * m_tFrame.iFrameStart,
        m_tInfo.fCY * m_tFrame.iMotion,
        m_tInfo.fCX, m_tInfo.fCY,
        UnitPixel);
    if (m_bDead) {
        m_tInfo.fCX = 62.f;
        m_tInfo.fCY = 66.f;
        g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Item_Box_broken"),
            Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
                (m_tInfo.fY - m_tInfo.fCY * 0.5),
                m_tInfo.fCX, m_tInfo.fCY),
            m_tInfo.fCX * m_tFrame.iFrameStart,
            m_tInfo.fCY * m_tFrame.iMotion,
            m_tInfo.fCX, m_tInfo.fCY,
            UnitPixel);
    }

}

void ItemBox::Release()
{
}

void ItemBox::DropMove()
{
    float	fY(0.f);

    bool bLineCol = BossMapLineMgr::Get_Instance()->DropItemCollision_Line(&fY, m_tInfo.fX, 0, 0);

    if (m_bJump)
    {
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
