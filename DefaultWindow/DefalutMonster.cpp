#include "stdafx.h"
#include "DefalutMonster.h"
#include"PngMrg.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"



DefalutMonster::DefalutMonster()
{
  
}

DefalutMonster::DefalutMonster(float _X, float _Y)
{
	m_tInfo.fX = _X;
	m_tInfo.fY = _Y;
}



DefalutMonster::~DefalutMonster()
{
    Release();
}

void DefalutMonster::Initialize()
{
    m_tInfo = { 600.f,100.f,64.f,40.f };

    this->fDamage = 5.f;
    this->fHp = 100.f;
    //C:\3개월 차\포트폴리오\Image\Dun\Monster\Default
    PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Default/Bat_Ice_Defalut.png", L"Defalut_Ice");


	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pStateKey = L"Defalut_Ice";
    m_eRender = GAMEOBJECT;
}

int DefalutMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;







    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void DefalutMonster::Late_Update()
{
	Default_Pattern();
    Move_Frame();
    Motion_Change();
}

void DefalutMonster::Render(HDC hDC)
{


	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original


    Graphics g(hDC);
	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);
	if (Turn_By_Player()) {
		g.DrawImage(img, Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX, (m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY, m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 64, 40, UnitPixel);
	}
	else {
		g.DrawImage(img, destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 64, 40, UnitPixel);

	}
	

}

void DefalutMonster::Release()
{
}

void DefalutMonster::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;


		}

		m_ePreState = m_eCurState;
	}



}

void DefalutMonster::Default_Pattern()
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
