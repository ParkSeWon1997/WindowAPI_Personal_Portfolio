#include "stdafx.h"
#include "PlayerBullet.h"
#include"PngMrg.h"
#include "LineMgr.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize()
{
	m_tInfo.fCX = 17.f;
	m_tInfo.fCY = 14.f;

	m_fSpeed = 10.f;


	m_fDamage = 15.f;
	m_fHP = 1.f;
	m_eRender = GAMEOBJECT;
}

int PlayerBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void PlayerBullet::Late_Update()
{
	//if (CLineMgr::Get_Instance()->Collision_Line(&this->m_tInfo.fX, this->m_tInfo.fY,m_tInfo.fCY))
	//{
		//m_bDead = true;
	//}

}

void PlayerBullet::Render(HDC hDC)
{
	//Ellipse(hDC,
	//	m_tRect.left,
	//	m_tRect.top,
	//	m_tRect.right,
	//	m_tRect.bottom);
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Bullet"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 17.f, 14.f);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Bullet"),
	//	Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
	//		(m_tInfo.fY - m_tInfo.fCY * 0.5),
	//		m_tInfo.fCX, m_tInfo.fCY),
	//	m_tInfo.fCX, m_tInfo.fCY,
	//	17.f, 14.f, UnitPixel);
}

void PlayerBullet::Release()
{
}
