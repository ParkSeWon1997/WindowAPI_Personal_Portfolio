#include "stdafx.h"
#include "PlayerHPBar.h"
#include"PngMrg.h"
PlayerHPBar::PlayerHPBar()
{
}

PlayerHPBar::~PlayerHPBar()
{
}

void PlayerHPBar::Initialize()
{
	m_tOuterRect = { 100, 20, WINCX - 100, 60 };
	m_tInnerRect = { 100, 20, WINCX - 200, 60 };

	m_fMaxHp = 100.f;
	m_fCurHp = 100.f;

	m_eRender = UI;
}

int PlayerHPBar::Update()
{
	return 0;
}

void PlayerHPBar::Late_Update()
{

	HpBar::Late_Update();
}

void PlayerHPBar::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_HP_UI"), m_tInfo.fX, m_tInfo.fY, 0.f, 0.f);
	//Rectangle(hDC, m_tOuterRect.left, m_tOuterRect.top, m_tOuterRect.right, m_tOuterRect.bottom);
}

void PlayerHPBar::Release()
{
}
