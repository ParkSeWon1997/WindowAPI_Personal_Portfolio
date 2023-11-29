#include "stdafx.h"
#include "DefalutMonster.h"
#include"PngMrg.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include"AroundBullet.h"
#include"ObjMgr.h"
#include "AbstractFactory.h"
#include "HpPotion.h"

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

   
	m_fSpeed = 3.f;
	m_fHP = 20.f;

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pStateKey = L"Defalut_Ice";
    m_eRender = GAMEOBJECT;
}

int DefalutMonster::Update()
{
	if (m_bDead) {
		CObjMgr::Get_Instance()->Add_Object(ITEM_HP, CAbstractFactory<HpPotion>::Create(this->m_tInfo.fX, this->m_tInfo.fY, 0));
        return OBJ_DEAD;
	}

	Move();
	FrameCheck++;




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
		g.DrawImage(img, Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX, 
			(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY, 
			m_tInfo.fCX, m_tInfo.fCY),
			m_tInfo.fCX * m_tFrame.iFrameStart,
			m_tInfo.fCY * m_tFrame.iMotion, 
			64, 40, UnitPixel);
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
		

		if (FrameCheck>50) {

			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_LEFT));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_RIGHT));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_UP));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_DOWN));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_LU));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_RU));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_LD));
			CObjMgr::Get_Instance()->Add_Object(OBJID::SUB_MONSTER_BULLET, Fire(DIR_RD));
			
			FrameCheck = 0;
			
		}


		


	}
}

void DefalutMonster::Move()
{
	if (m_tInfo.fX < WINCX)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	if (m_tInfo.fX > 0)
	{
		m_tInfo.fX += m_fSpeed;
	}
	//	m_tInfo.fY > WINCY ||
	//	m_tInfo.fY < 0)
	//{
	//	m_bDead = true;
	//}

	
}

CObj* DefalutMonster::Fire(DIRECTION _eDir)
{
	CObj* pBullet = new AroundBullet;

	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Direction(_eDir);

	return pBullet;

}
