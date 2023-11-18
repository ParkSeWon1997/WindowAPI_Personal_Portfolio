#include "stdafx.h"
#include "Gun.h"
#include"PngMrg.h"
#include"ObjMgr.h"
#include"PlayerBullet.h"
#include "AbstractFactory.h"


Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Initialize()
{
	
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Gun/RussianRoulette.png", L"Player_Gun_Rusiian");

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
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Player_Gun_Rusiian"), )
}

void Gun::Release()
{
}

void Gun::FIre(bool _IsShot)
{
	CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PlayerBullet>::Create(this->m_tInfo.fX,this->m_tInfo.fY,this->m_fAngle));
}
