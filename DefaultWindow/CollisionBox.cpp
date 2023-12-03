#include "stdafx.h"
#include "CollisionBox.h"
#include"PngMrg.h"

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
}

void CollisionBox::Render(HDC hDC)
{
    Graphics g(hDC);

    m_fSpeed = 100.f;
  
   // m_tRect.left += LONG(m_fSpeed * cos(m_fAngle * (PI / 180.f)));
   //m_tRect.top -= LONG(m_fSpeed * cos(m_fAngle * (PI / 180.f)));
   //m_tRect.right += LONG(m_fSpeed * sin(m_fAngle * (PI / 180.f)));
   // m_tRect.bottom -= LONG(m_fSpeed * sin(m_fAngle * (PI / 180.f)));
    //Rectangle()
   // Rectangle(hDC,
   // 	m_tRect.left,
   // 	m_tRect.top,
   // 	m_tRect.right,
   // 	m_tRect.bottom);


}

void CollisionBox::Release()
{
}
