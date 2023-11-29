#include "stdafx.h"
#include "AroundBullet.h"
#include "PngMrg.h"

AroundBullet::AroundBullet()
{
}

AroundBullet::~AroundBullet()
{
}

void AroundBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDamage = 5.0f;
	m_fAngle = 40.f;
	m_fSpeed = 3.f;
	m_eRender = GAMEOBJECT;
}

int AroundBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;

	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;

	case DIR_LU:
		m_tInfo.fY -= m_fSpeed * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fX -= m_fSpeed * sin(m_fAngle * (PI / 180.f));
		break;

	case DIR_RU:
		m_tInfo.fY -= m_fSpeed * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fX += m_fSpeed * sin(m_fAngle * (PI / 180.f));
		break;

	case DIR_LD:
		m_tInfo.fX -= m_fSpeed * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));
		break;

	case DIR_RD:
		m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void AroundBullet::Late_Update()
{
}

void AroundBullet::Render(HDC hDC)
{

	Graphics g(hDC);
	//g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	//g.RotateTransform(m_fAngle + 10);
	//g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);


	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SubMonster_Bullet"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 10.f, 20.f);
	//Ellipse(hDC,
	//	m_tRect.left,
	//	m_tRect.top,d
	//	m_tRect.right,
	//	m_tRect.bottom);
}

void AroundBullet::Release()
{
}
