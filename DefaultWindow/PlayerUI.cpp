#include "stdafx.h"
#include "PlayerUI.h"
#include"PngMrg.h"
#include"HpBar.h"

PlayerUI::PlayerUI(): m_pPlayerHpBar(nullptr)
{

}

PlayerUI::~PlayerUI()
{
	Release();
}

void PlayerUI::Initialize()
{
	m_tInfo.fCX = 148.f;
	m_tInfo.fCY = 32.f;

	m_pPlayerHpBar = new HpBar; 
	m_pPlayerHpBar->Set_Pos(m_tInfo.fX-5, m_tInfo.fY);
	m_eRender = UI;
}

int PlayerUI::Update()
{
	m_pPlayerHpBar->Update();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void PlayerUI::Late_Update()
{
	m_pPlayerHpBar->Late_Update();

}

void PlayerUI::Render(HDC hDC)
{

	Graphics g(hDC);

	
	//Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right, m_tRect.bottom );
	m_pPlayerHpBar->Render(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_HP_UI"),(m_tInfo.fX-m_tInfo.fCX*0.5), (m_tInfo.fY-m_tInfo.fCY*0.5), 148.f, 32.f);

	

}

void PlayerUI::Release()
{
	Safe_Delete(m_pPlayerHpBar);
}

void PlayerUI::Set_UI_HpBar(float _MaxHp, float _CurHp)
{
	dynamic_cast<HpBar*>(m_pPlayerHpBar)->Set_MaxHp(_MaxHp);
	dynamic_cast<HpBar*>(m_pPlayerHpBar)->Set_CurHp(_CurHp);


}


