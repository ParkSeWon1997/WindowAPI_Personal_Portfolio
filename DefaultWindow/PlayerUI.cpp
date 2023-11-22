#include "stdafx.h"
#include "PlayerUI.h"
#include"PngMrg.h"


PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Initialize()
{


	m_eRender = UI;
}

int PlayerUI::Update()
{

	return 0;
}

void PlayerUI::Late_Update()
{
	m_fPercent = m_fCurHp / m_fMaxHp;
}

void PlayerUI::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_HP_UI"), 0, 0, 148, 32);
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

}

void PlayerUI::Release()
{
}
