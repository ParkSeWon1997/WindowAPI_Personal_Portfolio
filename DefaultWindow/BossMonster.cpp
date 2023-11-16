#include "stdafx.h"
#include "BossMonster.h"
#include"PngMrg.h"
#include"ScrollMgr.h"
BossMonster::BossMonster()
{
}

BossMonster::~BossMonster()
{
    Release();
}

void BossMonster::Initialize()
{
	this->fDamage = 10.f;
	this->fHp = 200.f;



    m_tInfo = { 50.f, 300.f, 32, 32 };

//C:\3개월 차\포트폴리오\Image\Dun\Monster\Boss
    PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss.png", L"Boss_Monster");





}

int BossMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;







    __super::Update_Rect();
    return OBJ_NOEVENT;
  
}

void BossMonster::Late_Update()
{
}

void BossMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original




	Graphics g(hDC);


	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);

	g.DrawImage(img, destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 32, 32, UnitPixel);



}

void BossMonster::Release()
{

}

void BossMonster::Motion_Change()
{
	//if (m_ePreState != m_eCurState)
	//{
	//
	//	switch (m_eCurState)
	//	{
	//
	//	case IDLE:
	//		m_tFrame.iFrameStart = 0;
	//		m_tFrame.iFrameEnd = 4;
	//		m_tFrame.iMotion = 0;
	//
	//		m_tFrame.dwSpeed = 50;
	//		m_tFrame.dwTime = GetTickCount();
	//
	//		break;
	//
	//	case JUMP:
	//		m_tFrame.iFrameStart = 0;
	//		m_tFrame.iFrameEnd = 0;
	//		m_tFrame.iMotion = 1;
	//
	//		m_tFrame.dwSpeed = 50;
	//		m_tFrame.dwTime = GetTickCount();
	//
	//		break;
	//
	//	case RUN:
	//		m_tFrame.iFrameStart = 0;
	//		m_tFrame.iFrameEnd = 5;
	//		m_tFrame.iMotion = 2;
	//
	//		m_tFrame.dwSpeed = 100;
	//		m_tFrame.dwTime = GetTickCount();
	//		break;
	//	case ATTACK:
	//
	//		break;
	//
	//	case HIT:
	//
	//		break;
	//
	//	case DEAD:
	//		m_tFrame.iFrameStart = 0;
	//		m_tFrame.iFrameEnd = 0;
	//		m_tFrame.iMotion = 3;
	//
	//		m_tFrame.dwSpeed = 100;
	//		m_tFrame.dwTime = GetTickCount();
	//		break;
	//
	//
	//	}
	//
	//	m_ePreState = m_eCurState;
	//}
}

void BossMonster::Boss_pattern()
{
}
