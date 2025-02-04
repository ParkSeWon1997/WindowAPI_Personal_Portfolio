#include "stdafx.h"
#include "HpPotion.h"
#include"PngMrg.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "EasyMapLindeMgr.h"
#include "LineMgr.h"

HpPotion::HpPotion()
{
}

HpPotion::~HpPotion()
{
	Release();
}

void HpPotion::Initialize()
{

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 28.f;



	m_fSpeed = 3.f;
	m_fHP = 20.f;
	m_fPower = 5.f;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eCurState = HpItemImageSTATE::IDLE;
	m_bJump = true;
	m_eRender = GAMEOBJECT;
}

int HpPotion::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


	DropMove();
	


    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void HpPotion::Late_Update()
{

	Move_Frame();
	Motion_Change();

	if (CCollisionMgr::Check_Sphere(CPlayer::Get_Instance(), this) && (CPlayer::Get_Instance()->Get_HP()-5) < this->m_fHP)
	{
		CPlayer::Get_Instance()->Add_HP(this->m_fHP);
		this->m_bDead = true;
	
	}
}

void HpPotion::Render(HDC hDC)
{

	Graphics g(hDC);

	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Item_HP"),
		Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
			(m_tInfo.fY - m_tInfo.fCY * 0.5),
			m_tInfo.fCX, m_tInfo.fCY), 
			m_tInfo.fCX * m_tFrame.iFrameStart, 
			m_tInfo.fCY * m_tFrame.iMotion,
			m_tInfo.fCX, m_tInfo.fCY,
			UnitPixel);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void HpPotion::Release()
{
}

void HpPotion::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		}

		m_ePreState = m_eCurState;
	}
}



void HpPotion::Move()
{
}

void HpPotion::DropMove()
{
	float	fY(0.f);

	bool bLineCol = EasyMapLindeMgr::Get_Instance()->DropItemCollision_Line(&fY, m_tInfo.fX,0,0);

	if (m_bJump)
	{
		m_tInfo.fY -= (m_fPower * m_fAccelTime) - (9.0f * m_fAccelTime * m_fAccelTime * 0.5f);

		m_fAccelTime += 0.2f;

		if (bLineCol && fY < m_tInfo.fY)
		{
			m_bJump = false;
			m_fAccelTime = 0.f;
			m_tInfo.fY = fY;
		}

	}

	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}


}
