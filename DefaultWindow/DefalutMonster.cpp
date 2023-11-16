#include "stdafx.h"
#include "DefalutMonster.h"
#include"PngMrg.h"



DefalutMonster::DefalutMonster()
{
  
}

DefalutMonster::~DefalutMonster()
{
    Release();
}

void DefalutMonster::Initialize()
{
    this->fDamage = 5.f;
    this->fHp = 20.f;





    m_eRender = GAMEOBJECT;
}

int DefalutMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;







    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void DefalutMonster::Late_Update()
{
}

void DefalutMonster::Render(HDC hDC)
{
}

void DefalutMonster::Release()
{
}
