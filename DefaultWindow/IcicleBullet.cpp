#include "stdafx.h"
#include "IcicleBullet.h"
#include "PngMrg.h"

IcicleBullet::IcicleBullet()
{
}

IcicleBullet::~IcicleBullet()
{
}

void IcicleBullet::Initialize()
{
	m_tInfo.fCX = 27.f;
	m_tInfo.fCY = 40.f;

	RotaeImage = 0.f;
	m_fSpeed = 7.f;
	m_fDamage = 30.f;
	m_fHP = 1.f;
	m_eRender = GAMEOBJECT;
}

int IcicleBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void IcicleBullet::Late_Update()
{
	if (m_tInfo.fX > WINCX ||
		m_tInfo.fX < 0 ||
		m_tInfo.fY > WINCY ||
		m_tInfo.fY < 0)
	{
		m_bDead = true;
	}
}

void IcicleBullet::Render(HDC hDC)
{
	Graphics g(hDC);
	//g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	//g.RotateTransform(RotaeImage);
	//g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossMonset_Icicle"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 27.f, 40.f);
}

void IcicleBullet::Release()
{
}


