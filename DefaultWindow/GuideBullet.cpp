#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"


CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
}

void CGuideBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CGuideBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(MONSTER, this);
	
	float		fWidth, fHeight, fDiagonal, fRadian;

	if (m_pTarget)
	{
		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		fRadian = acos(fWidth / fDiagonal);

		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}
	
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sin(m_fAngle * PI / 180.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update()
{
}

void CGuideBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CGuideBullet::Release()
{
}
