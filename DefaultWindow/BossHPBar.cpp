#include "stdafx.h"
#include "BossHPBar.h"

BossHPBar::BossHPBar() :m_fMaxHp(0.f),
m_fCurHp(0.f),
m_fPercent(0.f)
{

}

BossHPBar::~BossHPBar()
{

}

void BossHPBar::Initialize()
{
	m_eRender = UI;
}


int BossHPBar::Update()
{
	m_tInfo.fCX = 0.f;
	m_tInfo.fCY = 52.f;
	__super::Update_Rect();
	return 0;
}

void BossHPBar::Late_Update()
{
	m_fPercent =( m_fCurHp / m_fMaxHp);
}

void BossHPBar::Render(HDC hDC)
{

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 20, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC,20+ m_tRect.left, m_tRect.top,  460+ m_tRect.right * m_fPercent, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void BossHPBar::Release()
{
}
