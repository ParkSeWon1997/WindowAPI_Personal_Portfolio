#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 3.f;
	m_fDistance = 100.f;
}

int CShield::Update()
{
	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CShield::Release()
{
}
