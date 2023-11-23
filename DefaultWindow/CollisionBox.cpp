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

    //Rectangle()
    Rectangle(hDC,
    	m_tRect.left,
    	m_tRect.top,
    	m_tRect.right,
    	m_tRect.bottom);


}

void CollisionBox::Release()
{
}
