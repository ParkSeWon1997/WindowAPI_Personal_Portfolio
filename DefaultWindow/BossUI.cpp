#include "stdafx.h"
#include "BossUI.h"
#include"PngMrg.h"

BossUI::BossUI() :m_fMaxHp(0.f),
m_fCurHp(0.f),
m_fPercent(0.f)
{

}

BossUI::~BossUI()
{
}

void BossUI::Initialize()
{
	m_tInfo.fCX = 375.f;
	m_tInfo.fCY = 48.f;


	m_eRender = UI;
}

int BossUI::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void BossUI::Late_Update()
{
}

void BossUI::Render(HDC hDC)
{
	Graphics g(hDC);
	Rectangle(hDC, m_tRect.left , m_tRect.top, m_tRect.right, m_tRect.bottom);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Boss_UI"),(m_tInfo.fX-m_tInfo.fCX*0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 375.f, 48.f);

}

void BossUI::Release()
{
}
