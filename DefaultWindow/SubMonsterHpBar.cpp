#include "stdafx.h"
#include "SubMonsterHpBar.h"

SubMonsterHpBar::SubMonsterHpBar() :m_fMaxHp(0.f),
m_fCurHp(0.f),
m_fPercent(0.f)
{
}

SubMonsterHpBar::~SubMonsterHpBar()
{
}

void SubMonsterHpBar::Initialize()
{
    m_eRender = UI;
}

int SubMonsterHpBar::Update()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 32.f;
	__super::Update_Rect();
	return 0;
}

void SubMonsterHpBar::Late_Update()
{
}

void SubMonsterHpBar::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 20, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, 52 + m_tRect.right * m_fPercent, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void SubMonsterHpBar::Release()
{
}
