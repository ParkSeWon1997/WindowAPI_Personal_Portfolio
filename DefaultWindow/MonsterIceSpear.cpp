#include "stdafx.h"
#include "MonsterIceSpear.h"
#include "PngMrg.h"

MonsterIceSpear::MonsterIceSpear()
{
}

MonsterIceSpear::~MonsterIceSpear()
{
}

void MonsterIceSpear::Initialize()
{
	m_tInfo.fCX = 25.f;
	m_tInfo.fCY = 111.f;

	m_fSpeed = 7.f;

	m_fDamage = 50.f;
	m_fHP = 1.f;
	m_eRender = GAMEOBJECT;
}

int MonsterIceSpear::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void MonsterIceSpear::Late_Update()
{
}

void MonsterIceSpear::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossMonset_Spear"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 25.f, 111.f);
}

void MonsterIceSpear::Release()
{
}
