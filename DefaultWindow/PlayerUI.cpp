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
	//m_tInfo = { 100.f,100.f,148.f,32.f };
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
	Graphics g(hDC);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 20, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left+42 , m_tRect.top , m_tRect.right , m_tRect.bottom );
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_HP_UI"),(m_tInfo.fX-m_tInfo.fCX*0.5), (m_tInfo.fY-m_tInfo.fCY*0.5), 148.f, 32.f);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}

void PlayerUI::Release()
{
}
