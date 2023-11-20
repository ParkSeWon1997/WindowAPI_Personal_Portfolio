#include "stdafx.h"
#include "Gun.h"
#include"PngMrg.h"
#include"ObjMgr.h"
#include"PlayerBullet.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Player.h"


Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 20.f;

	m_eRender = UI;
}

int Gun::Update()
{
	//m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	//m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Gun::Late_Update()
{
}

void Gun::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	Graphics g(hDC);

	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) ,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) ),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5),
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) ),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5),
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) ) };  // destination for lower-left point of original


	
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Posin_half_Check())
	{
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"),
			(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY,
			28.f, 20.f);
	}
	else
	{
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"), destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 28.f, 20.f, UnitPixel);
	}
	//dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Posin_half_Check()
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"), )
}

void Gun::Release()
{
}

void Gun::FIre(bool _IsShot)
{
	CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PlayerBullet>::Create(this->m_tInfo.fX,this->m_tInfo.fY,this->m_fAngle));
}
