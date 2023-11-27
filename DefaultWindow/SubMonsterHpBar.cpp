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
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 7.f;
    m_eRender = UI;
}

int SubMonsterHpBar::Update()
{
	
	__super::Update_Rect();
	return 0;
}

void SubMonsterHpBar::Late_Update()
{
	m_fPercent = (m_fCurHp / m_fMaxHp);
}

void SubMonsterHpBar::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 20, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	m_tRect.right= m_tRect.left + 20 * m_fPercent;
	Rectangle(hDC, m_tRect.left, m_tRect.top,   m_tRect.right , m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void SubMonsterHpBar::Release()
{
}
