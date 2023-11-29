#include "stdafx.h"
#include "NPC.h"
#include"PngMrg.h"
#include "CollisionMgr.h"

#include"Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "HpPotion.h"
#include "Sword.h"
#include "DragonSword.h"

NPC::NPC()
{
}

NPC::~NPC()
{
	Release();
}

void NPC::Initialize()
{
	
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 192.f;
	m_fSpeed = 3.0f;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eCurState = IDLE;
	m_eRender = GAMEOBJECT;
}

int NPC::Update()
{
	//m_bIsHit = false;
	Move();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void NPC::Late_Update()
{

	Move_Frame();
	Motion_Change();
}

void NPC::Render(HDC hDC)
{

	Graphics g(hDC);


	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"NPC_Giant"), 0.f* m_tFrame.iFrameStart, 0.f* m_tFrame.iFrameEnd , m_tInfo.fCX, m_tInfo.fCY);
	
	//Rectangle(hDC, m_tRect.left, m_tRect.top , m_tRect.right , m_tRect.bottom );

	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"NPC_Giant"),
		Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
			(m_tInfo.fY - m_tInfo.fCY * 0.5),
			m_tInfo.fCX, m_tInfo.fCY),
		m_tInfo.fCX * m_tFrame.iFrameStart,
		m_tInfo.fCY * m_tFrame.iMotion,
		200, 192, UnitPixel);

	if (CCollisionMgr::CollisionRect_to_Rect(CPlayer::Get_Instance(),this))
	{
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"F_Button"), m_tInfo.fX, m_tInfo.fY-200.f, 52.f, 56.f);


	}

}

void NPC::Release()
{
}

void NPC::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

			break;

		}
			m_ePreState = m_eCurState;
	}


}

void NPC::Create_Weapon()
{
	
	CObjMgr::Get_Instance()->Add_Object(SWORD, CAbstractFactory<DragonSword>::Create(m_tInfo.fX, m_tInfo.fY, 0));



}

void NPC::Move()
{
	if (m_tInfo.fX >= 1280.f)
	{
		mDirX = -1.0f;
	}
	else if (m_tInfo.fX <= 0.f)
	{
		mDirX = 1.0f;
	}
	m_tInfo.fX = m_tInfo.fX + mDirX * m_fSpeed;
}
