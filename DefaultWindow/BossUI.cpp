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
	m_tInfo.fCX = 125.f;
	m_tInfo.fCY = 16.f;


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
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Boss_UI"), 640.f, 600.f, 125.f, 16.f);

}

void BossUI::Release()
{
}
