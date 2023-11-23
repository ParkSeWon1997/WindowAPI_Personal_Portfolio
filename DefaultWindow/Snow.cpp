#include "stdafx.h"
#include "Snow.h"
#include "PngMrg.h"

Snow::Snow()
{
}

Snow::~Snow()
{
}

void Snow::Initialize()
{
   
    m_tInfo.fCX = 1280.f;
    m_tInfo.fCY = 800.f;

    m_fSpeed = 7.0f;
    m_eRender = BACKGROUND;
}

int Snow::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

   
    m_tInfo.fY += m_fSpeed;

    __super::Update_Rect();
    return OBJ_NOEVENT;

}

void Snow::Late_Update()
{
}

void Snow::Render(HDC hDC)
{
    Graphics g(hDC);


    g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Snow"), (m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 1280.f, 800.f);

}

void Snow::Release()
{
}
