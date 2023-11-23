#include "stdafx.h"
#include "PlayerWeaponBox.h"
#include"PngMrg.h"

PlayerWeaponBox::PlayerWeaponBox()
{
}

PlayerWeaponBox::~PlayerWeaponBox()
{
}

void PlayerWeaponBox::Initialize()
{
    m_tInfo = { WINCX - 100,WINCY - 100,170.f,120.f };

    WeaponImagwKey = nullptr;
    m_eRender = UI;
}

int PlayerWeaponBox::Update()
{
    //__super::Update_Rect();
    return 0;
}

void PlayerWeaponBox::Late_Update()
{
}

void PlayerWeaponBox::Render(HDC hDC)
{
    Graphics g(hDC);
    Image* WeaponImage = PngMrg::Get_Instance()->Get_Image(WeaponImagwKey);
    Image* WeaponBoxImage = PngMrg::Get_Instance()->Get_Image(L"Player_Weapon_UI");
    g.DrawImage(WeaponBoxImage, (m_tInfo.fX - m_tInfo.fCX * 0.5f), (m_tInfo.fY - m_tInfo.fCY * 0.5f), m_tInfo.fCX, m_tInfo.fCY);
    if (WeaponImagwKey) {
        g.DrawImage(WeaponImage, (int)(m_tInfo.fX- WeaponImage->GetWidth()), (int)(m_tInfo.fY- WeaponImage->GetHeight()), WeaponImage->GetWidth()*3, WeaponImage->GetHeight() * 3);
    }


}

void PlayerWeaponBox::Release()
{
}
