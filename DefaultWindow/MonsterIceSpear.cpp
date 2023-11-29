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

	RotaeImage = 0.f;
	m_fSpeed = 7.f;
	m_fDamage = 5.f;
	m_fHP = 1.f;
	m_eRender = GAMEOBJECT;
}

int MonsterIceSpear::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move(m_eMoveDir);

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void MonsterIceSpear::Late_Update()
{

	if (m_tInfo.fX > WINCX ||
		m_tInfo.fX < 0 ||
		m_tInfo.fY > WINCY ||
		m_tInfo.fY < 0)
	{
		m_bDead = true;
	}
}

void MonsterIceSpear::Render(HDC hDC)
{
	Graphics g(hDC);
	g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	g.RotateTransform(RotaeImage);
	g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossMonset_Spear"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 25.f, 111.f);
}

void MonsterIceSpear::Release()
{
}

void MonsterIceSpear::Move(BOSSMONSTER_SPEAR_DIR _ID)
{

	switch (m_eMoveDir)
	{
	case BOSSMONSTER_SPEAR_DIR::MOVE_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case BOSSMONSTER_SPEAR_DIR::MOVE_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case BOSSMONSTER_SPEAR_DIR::MOVE_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case BOSSMONSTER_SPEAR_DIR::MOVE_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;

	default:
		break;
	}


}
