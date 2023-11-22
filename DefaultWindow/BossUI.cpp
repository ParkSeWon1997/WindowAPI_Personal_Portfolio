#include "stdafx.h"
#include "BossUI.h"
#include"PngMrg.h"

BossUI::BossUI() :m_fMaxHp(0.f),
m_fCurHp(0.f),
m_fPercent(0.f),
m_tInfo({}), m_tInnerRect({})
{

}

BossUI::~BossUI()
{
}

void BossUI::Initialize()
{
	m_eRender = UI;
}

int BossUI::Update()
{
	return 0;
}

void BossUI::Late_Update()
{
}

void BossUI::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossUI"), 0, 0, 1280, 800);

}

void BossUI::Release()
{
}
