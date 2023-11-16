#include "stdafx.h"
#include "BossMonster.h"
#include"PngMrg.h"
#include"ScrollMgr.h"
#include "KeyMgr.h"
#include"ObjMgr.h"
#include"Player.h"
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



    m_tInfo = { 900.f, 300.f, 40, 40 };

//C:\3개월 차\포트폴리오\Image\Dun\Monster\Boss
    PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Boss_Nifl.png", L"Boss_Monster");

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pStateKey = L"Boss_Monster";

	m_eRender = GAMEOBJECT;
	

}

int BossMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
	//CObjMgr::Get_Instance()->Get_Target(PLAYER,CPlayer)
#ifdef _DEBUG
	if (dwFrameTime + 1000 < GetTickCount()) {
		cout << "몬스터 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		dwFrameTime = GetTickCount();
	}
#endif



	Boss_pattern();



    __super::Update_Rect();
    return OBJ_NOEVENT;
  
}

void BossMonster::Late_Update()
{


	Move_Frame();
	Motion_Change();
}

void BossMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original

	Graphics g(hDC);
	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);

	if (Turn_By_Player()){
		g.DrawImage(img, Rect((m_tInfo.fX - m_tInfo.fCX * 0.5)+ iScrollX, (m_tInfo.fY - m_tInfo.fCY * 0.5)+ iScrollY, m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 40, 40, UnitPixel);
	}
	else {
		g.DrawImage(img, destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 40, 40, UnitPixel);

	}


}

void BossMonster::Release()
{

}

void BossMonster::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
	
		switch (m_eCurState)
		{
	
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
	
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
	
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 1;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;
	
		case HIT:
	
			break;
	
		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 2;
	
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
	
	
		}
	
		m_ePreState = m_eCurState;
	}
}

void BossMonster::Boss_pattern()
{
	if (m_bDead) {
		m_eCurState = DEAD;
	}
	else {
		m_eCurState = IDLE;

		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			
			m_eCurState = ATTACK;
			
		}

	
	}



}
