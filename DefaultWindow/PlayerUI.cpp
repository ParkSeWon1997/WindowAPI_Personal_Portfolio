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
	m_tInfo.fCX = 148.f;
	m_tInfo.fCY = 32.f;

	m_eRender = UI;
}

int PlayerUI::Update()
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void PlayerUI::Late_Update()
{
	m_fPercent = m_fCurHp / m_fMaxHp;
}

void PlayerUI::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right , m_tRect.bottom );
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_HP_UI"),m_tInfo.fX, m_tInfo.fY, 148.f, 32.f);

		

}

void PlayerUI::Release()
{
}
