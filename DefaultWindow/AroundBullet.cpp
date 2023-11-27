#include "stdafx.h"
#include "AroundBullet.h"

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

	m_fDamage = 1.0f;
	m_fAngle = 40.f;
	m_fSpeed = 5.f;
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
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void AroundBullet::Release()
{
}
