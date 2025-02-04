#include "stdafx.h"
#include "Gun.h"
#include"PngMrg.h"
#include"ObjMgr.h"
#include"PlayerBullet.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "SoundMgr.h"

static float  g_fVolume = 1.0f;
Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 40.f;

	m_eRender = GAMEOBJECT;
}

int Gun::Update()
{

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Gun::Late_Update()
{
}

void Gun::Render(HDC hDC)
{
	
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
		g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
		g.RotateTransform(m_fAngle);
		g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"),
			(m_tInfo.fX - m_tInfo.fCX * 0.5) ,
			(m_tInfo.fY - m_tInfo.fCY * 0.5) ,
			m_tInfo.fCX, m_tInfo.fCY);
	}
	else
	{
		g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
		g.RotateTransform(m_fAngle+180);
		g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"), destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, m_tInfo.fCX, m_tInfo.fCY, UnitPixel);
	}

}

void Gun::Release()
{
}

void Gun::FIre(bool _IsShot)
{
	CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PlayerBullet>::Create(this->m_tInfo.fX,this->m_tInfo.fY,this->m_fAngle));
	
}
