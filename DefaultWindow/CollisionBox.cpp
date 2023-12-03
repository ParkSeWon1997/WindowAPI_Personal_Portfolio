#include "stdafx.h"
#include "CollisionBox.h"
#include"PngMrg.h"
#include "Player.h"
#include "ObjMgr.h"

CollisionBox::CollisionBox()
{
}

CollisionBox::~CollisionBox()
{
}

void CollisionBox::Initialize()
{
    m_fDamage = 15.f;
    m_eRender = GAMEOBJECT;
   m_pStateKey = L"Player_Sword_Effect";
   m_tFrame.iFrameStart = 0;
   m_tFrame.iFrameEnd = 6;
   m_tFrame.iMotion = 0;
   
   m_tFrame.dwSpeed = 50;
   m_tFrame.dwTime = GetTickCount();
}

int CollisionBox::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
   
   
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CollisionBox::Late_Update()
{
    Move_Frame();
}

void CollisionBox::Render(HDC hDC)
{
    Graphics g(hDC);

    m_fSpeed = 100.f;
  
 // Rectangle(hDC,
 // 	m_tRect.left,
 // 	m_tRect.top,
 // 	m_tRect.right,
 // 	m_tRect.bottom);

  if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Posin_half_Check())
  {
      g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
      g.RotateTransform(m_fAngle+90);
      g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
      g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
          Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
              (m_tInfo.fY - m_tInfo.fCY * 0.5),
              m_tInfo.fCX, m_tInfo.fCY),
          m_tInfo.fCX * m_tFrame.iFrameStart,
          m_tInfo.fCY * m_tFrame.iMotion,
          m_tInfo.fCX, m_tInfo.fCY, UnitPixel);

  }
  else
  {
     g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
     g.RotateTransform(m_fAngle+90);
     g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
    g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
        Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
            (m_tInfo.fY - m_tInfo.fCY * 0.5),
            m_tInfo.fCX, m_tInfo.fCY),
        m_tInfo.fCX * m_tFrame.iFrameStart,
        m_tInfo.fCY * m_tFrame.iMotion,
        m_tInfo.fCX, m_tInfo.fCY, UnitPixel);
  }


}

void CollisionBox::Release()
{
}
