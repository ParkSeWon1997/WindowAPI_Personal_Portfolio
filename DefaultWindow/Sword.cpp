#include "stdafx.h"
#include "Sword.h"


#include"PngMrg.h"
#include"ObjMgr.h"
#include "AbstractFactory.h"
#include"CollisionBox.h"
Sword::Sword()
{
}

Sword::~Sword()
{
}

void Sword::Initialize()
{
	m_tInfo.fCX = 26.f;
	m_tInfo.fCY = 60.f;

	m_eRender = GAMEOBJECT;
}

int Sword::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Sword::Late_Update()
{
}

void Sword::Render(HDC hDC)
{
	Graphics g(hDC);


	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Sword_FireDragon"), (m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), m_tInfo.fCX, m_tInfo.fCY);



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
	CObjMgr::Get_Instance()->Add_Object(COLLISIONBOX, CAbstractFactory<CollisionBox>::Create(_X , _Y , m_tInfo.fCX, m_tInfo.fCY, 0));

}

void Sword::SwordEndPoint()
{

}
