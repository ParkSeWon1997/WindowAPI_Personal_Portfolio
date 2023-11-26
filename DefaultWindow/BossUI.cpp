#include "stdafx.h"
#include "BossUI.h"
#include"PngMrg.h"
#include"BossHPBar.h"

BossUI::BossUI() :m_pBossHpBar(nullptr)
{

}

BossUI::~BossUI()
{
	Release();
}

void BossUI::Initialize()
{
	m_tInfo.fCX = 545.f;
	m_tInfo.fCY = 52.f;
	m_pBossHpBar = new BossHPBar;
	m_pBossHpBar->Set_Pos(m_tInfo.fX-180 , m_tInfo.fY);
	m_eRender = UI;
}

int BossUI::Update()
{
	m_pBossHpBar->Update();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void BossUI::Late_Update()
{
	m_pBossHpBar->Late_Update();
}

void BossUI::Render(HDC hDC)
{
	Graphics g(hDC);

	m_pBossHpBar->Render(hDC);
	
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Boss_UI"),(m_tInfo.fX-m_tInfo.fCX*0.465), (m_tInfo.fY - m_tInfo.fCY * 0.5), m_tInfo.fCX, m_tInfo.fCY);


}

void BossUI::Release()
{
	Safe_Delete(m_pBossHpBar);
}

void BossUI::Set_UI_HpBar(float _MaxHp, float _CurHp)
{
	dynamic_cast<BossHPBar*>(m_pBossHpBar)->Set_MaxHp(_MaxHp);
	dynamic_cast<BossHPBar*>(m_pBossHpBar)->Set_CurHp(_CurHp);
}
