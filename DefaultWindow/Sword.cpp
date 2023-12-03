#include "stdafx.h"
#include "Sword.h"


#include"PngMrg.h"
#include"ObjMgr.h"
#include "AbstractFactory.h"
#include"CollisionBox.h"
#include "Mouse.h"
Sword::Sword()
{
}

Sword::~Sword()
{
}

void Sword::Initialize()
{



	

	m_fSpeed = 10.f;
	m_tInfo.fCX = 39.f;
	m_tInfo.fCY = 90.f;
	m_fDiagonal = 100.f;
	//m_fAngle = 45.f;

	m_RotateAngle = 45.f;

	m_eRender = GAMEOBJECT;
}

int Sword::Update()
{
	CollisionBOxCount++;
	
	SwordEndPoint();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Sword::Late_Update()
{
	if (CollisionBOxCount > 20) {
		CollisionBoxQue[0] = nullptr;
		CObjMgr::Get_Instance()->Delete_ID(COLLISIONBOX);
		CollisionBOxCount = 0;
	}
}

void Sword::Render(HDC hDC)
{


	
	Graphics g(hDC);
	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) ,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5)),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5),
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5)),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5),
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5)) };  // destination for lower-left point of original



	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Posin_half_Check())
	{
		if (IsSwing == false)
		{
			g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
			g.RotateTransform(-m_RotateAngle);
			g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
			g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"),
				(m_tInfo.fX - m_tInfo.fCX * 0.5),
				(m_tInfo.fY - m_tInfo.fCY * 0.5),
				m_tInfo.fCX, m_tInfo.fCY);
		}
		else
		{
			g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
			g.RotateTransform(m_RotateAngle+90);
			g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
			g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"),
				(m_tInfo.fX - m_tInfo.fCX * 0.5),
				(m_tInfo.fY - m_tInfo.fCY * 0.5),
				m_tInfo.fCX, m_tInfo.fCY);
		}
	}
	else
	{

		if (IsSwing == false)
		{

			g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
			g.RotateTransform(m_RotateAngle);
			g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
			g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"),
				(m_tInfo.fX - m_tInfo.fCX * 0.5),
				(m_tInfo.fY - m_tInfo.fCY * 0.5),
				m_tInfo.fCX, m_tInfo.fCY);
		}
		else
		{
			g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
			g.RotateTransform(m_RotateAngle + 90);
			g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
			g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"),
				(m_tInfo.fX - m_tInfo.fCX * 0.5),
				(m_tInfo.fY - m_tInfo.fCY * 0.5),
				m_tInfo.fCX, m_tInfo.fCY);
		}

	}


	



	//Rectangle(hDC,
	//	m_tRect.left,
	//	m_tRect.top,
	//	m_tRect.right,
	//	m_tRect.bottom);


}

void Sword::Release()
{

}

void Sword::AttachCollisionBox(float _X, float _Y)
{
	if (CollisionBoxQue[0] == nullptr) {
		if (IsSwing == false)
		{
			CObjMgr::Get_Instance()->Add_Object(COLLISIONBOX, CAbstractFactory<CollisionBox>::Create(SwordEND.x, SwordEND.y, 124.f, 98.f, m_fAngle));
			CollisionBoxQue[0] = CObjMgr::Get_Instance()->Get_ObjList(COLLISIONBOX);
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(COLLISIONBOX, CAbstractFactory<CollisionBox>::Create(SwordEND.x, SwordEND.y, 124.f, 98.f, m_fAngle));
			CollisionBoxQue[0] = CObjMgr::Get_Instance()->Get_ObjList(COLLISIONBOX);
		}
	}


	
}

void Sword::SwordEndPoint()
{
	
	float m_pMouse_X = CMouse::Get_Instance()->Get_Info().fX - m_tInfo.fX;
	float m_pMouse_Y = CMouse::Get_Instance()->Get_Info().fY - m_tInfo.fY;
	float m_pMouse_R = (float)sqrt(m_pMouse_X * m_pMouse_X + m_pMouse_Y * m_pMouse_Y);

	m_fAngle = (float)acos(m_pMouse_X / m_pMouse_R) * 180 / PI;


	SwordEND.x = LONG(m_tInfo.fX + m_fDiagonal * cos(m_fAngle * (PI / 180.f)));
	if (m_pMouse_Y < 0)
	{
		m_fAngle *= -1;
	}

	SwordEND.y = LONG(m_tInfo.fY + m_fDiagonal * sin(m_fAngle * (PI / 180.f))) ;//허리춤에 오게 +10조정
}



