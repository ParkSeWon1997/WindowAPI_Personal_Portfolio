#include "stdafx.h"
#include "HpBar.h"

HpBar::HpBar()
	:m_fMaxHp(0.f),
	m_fCurHp(0.f),
	m_fPercent(0.f),
	m_tInfo({}),
	m_tOuterRect({}),
	m_tInnerRect({})
{
}

HpBar::~HpBar()
{
}

void HpBar::Initialize()
{
	//m_tOuterRect = { 100, 20, WINCX - 100, 60 };
	//m_tInnerRect = { 100, 20, WINCX - 200, 60 };
	//
	//m_fMaxHp = 100.f;
	//m_fCurHp = 100.f;
}

int HpBar::Update()
{
    return 0;
}

void HpBar::Late_Update()
{
	m_fPercent = m_fCurHp / m_fMaxHp;
}

void HpBar::Render(HDC hDC)
{
	Rectangle(hDC, m_tOuterRect.left, m_tOuterRect.top, m_tOuterRect.right, m_tOuterRect.bottom);
}

void HpBar::Release()
{
}
