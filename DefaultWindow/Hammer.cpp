#include "stdafx.h"
#include "Hammer.h"
#include "PngMrg.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "ObjMgr.h"

Hammer::Hammer()
{
}

Hammer::~Hammer()
{
}

void Hammer::Initialize()
{
	m_tInfo.fCX = 52.f;
	m_tInfo.fCY = 82.f;
	m_fDamage = 30.0f;
	m_eRender = GAMEOBJECT;
}

int Hammer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Hammer::Late_Update()
{
	if (CCollisionMgr::Check_Sphere(CPlayer::Get_Instance(), this))
	{
		this->m_bDead = true;

	}
}

void Hammer::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Hammer"), m_tInfo.fX, m_tInfo.fY- m_tInfo.fCY);
}

void Hammer::Release()
{
}

void Hammer::MoveToEndEntry()
{

}
