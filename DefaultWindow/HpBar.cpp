#include "stdafx.h"
#include "HpBar.h"

HpBar::HpBar()
	:m_fMaxHp(0.f),
	m_fCurHp(0.f),
	m_fPercent(0.f)
{
}

HpBar::~HpBar()
{
}

void HpBar::Initialize()
{
	
	m_eRender = UI;
}

int HpBar::Update()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 32.f;
	__super::Update_Rect();
    return 0;
}

void HpBar::Late_Update()
{
	m_fPercent = m_fCurHp / m_fMaxHp;

}

void HpBar::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 20, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, 52+m_tRect.right*m_fPercent, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void HpBar::Release()
{
}
