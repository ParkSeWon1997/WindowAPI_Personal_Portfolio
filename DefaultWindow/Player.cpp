#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include"PngMrg.h"
#include"AnimSprite.h"
#include"ElapseTimeMgr.h"
#include"Mouse.h"
#include "CTimeMgr.h"
#include "SoundMgr.h"
#include"Gun.h"
#include "PlayerBullet.h"


CObj* CPlayer::m_Instance = nullptr;
static float  g_fVolume = 1.0f;


bool testLand = false;
CPlayer::CPlayer() : m_bJump(false), m_fPower(0.f), m_fAccelTime(0.f)
, m_eCurState(IDLE), m_ePreState(PS_END), m_pWeaponList{}
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
	m_pMouse = CMouse::Get_Instance();
	Initialize();
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

	//m_tInfo.fCX = 64.f;
	//m_tInfo.fCY = 64.f;
	m_tInfo = { 100.f, 500.f, 64, 64 };

	m_fSpeed = 5.f;
	m_fDiagonal = 100.f;
	m_fPower = 20.f;


	//아이들, 점프, 달리기,죽음 이미지 
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();


	//m_bDead = true;
	m_pStateKey = L"Player";

	m_eRender = GAMEOBJECT;



}

int CPlayer::Update()
{

	Jump();

	Key_Input();
	

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	
	Set_Posin();
	//Offset();
	Move_Frame();
	WeaponChage();
	Motion_Change();





#ifdef _DEBUG
	if (dwFrameTime + 1000 < GetTickCount()) {
		cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		dwFrameTime = GetTickCount();
	}



	if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY))
	{
		m_bJump = false;
	}
	else
	{
		m_bJump = true;
	}
#endif
}

void CPlayer::Render(HDC hDC)
{
	



	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY + iScrollY, nullptr);
	//LineTo(hDC, m_tPosin.x + iScrollX, m_tPosin.y + iScrollY);

	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original




	Graphics g(hDC);


	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);



	if (Posin_half_Check()) {
		g.DrawImage(img,
			Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
				(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY,
				m_tInfo.fCX, m_tInfo.fCY),
			m_tInfo.fCX * m_tFrame.iFrameStart,
			m_tInfo.fCY * m_tFrame.iMotion,
			64, 64, UnitPixel);
	}
	else {
		g.DrawImage(img, destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 64, 64, UnitPixel);

	}





}

void CPlayer::Release()
{

	

}

void CPlayer::Key_Input()
{
	if (m_bDead) {
		//dead-sharedassets2.assets-304
		m_eCurState = DEAD;
	}
	else {
		m_eCurState = IDLE;

		if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			m_eCurState = RUN;
			m_tInfo.fX -= m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			m_tInfo.fX += m_fSpeed;
			m_eCurState = RUN;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_bJump = true;
			m_eCurState = JUMP;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('2'))
		{
			m_eWeaponMode = CPlayer::GUN;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
		{
			m_eWeaponMode = CPlayer::SWORD;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (m_eWeaponMode == CPlayer::GUN)
			{
				dynamic_cast<Gun*>(CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN))->FIre(true);
				
				//CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<PlayerBullet>::Create(m_tPosin.x, m_tPosin.y, this->m_fAngle));
				CSoundMgr::Get_Instance()->PlaySound(L"Gun-sharedassets22.assets-357.wav", SOUND_EFFECT, g_fVolume);

			}

			//dynamic_cast<Gun*>(m_pWeaponList.back())->FIre(true);

		}

	}

}

void CPlayer::Jump()
{
	//float	fY(0.f);

	//bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(&fY, m_tInfo.fX);

	if (m_bJump)
	{

		m_tInfo.fY -= (m_fPower * m_fAccelTime) - (9.8f * m_fAccelTime * m_fAccelTime * 0.5f);

		m_fAccelTime += 0.2f;

	}

	else
		m_fAccelTime = 0.f;


	//else if (bLineCol)
	//{
	//	m_tInfo.fY = fY;
	//}


}



void CPlayer::Offset()
{
	int		iOffSetMinX = 100;
	int		iOffSetMaxX = 1280;

	int		iOffSetMinY = 100;
	int		iOffSetMaxY = 800;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();

			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;

			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();

			break;

		case RUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK:

			break;

		case HIT:

			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;


		}

		m_ePreState = m_eCurState;
	}

}

void CPlayer::WeaponChage()
{
	switch (m_eWeaponMode)
	{
	case CPlayer::GUN:
		
		//CObjMgr::Get_Instance()->Add_Object(OBJID::GUN, CAbstractFactory<Gun>::Create(this->m_tInfo.fX, this->m_tInfo.fY, this->m_fAngle));
		//if (CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN)==NULL)
		//{
		//
		//}

		if (m_pWeaponList[CPlayer::GUN] == nullptr)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::GUN, CAbstractFactory<Gun>::Create(this->m_tPosin.x, this->m_tPosin.y, this->m_fAngle));
			m_pWeaponList[CPlayer::GUN] = CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN);
			//m_pWeaponList[CPlayer::GUN] = new Gun;
			//m_pWeaponList[CPlayer::GUN]->Set_Pos(m_tPosin.x, m_tPosin.y);
			//m_pWeaponList[CPlayer::GUN]->Set_Angle(this->m_fAngle);
		}
		else
		{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN)->Set_Pos(m_tPosin.x, m_tPosin.y);
			CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN)->Set_Angle(m_fAngle);

		}
		break;
	case CPlayer::SWORD:
		break;
	}

}

void CPlayer::Set_Posin()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	float m_pMouse_X = (m_pMouse->Get_Info().fX - m_tInfo.fX) + iScrollX;
	float m_pMouse_Y = (m_pMouse->Get_Info().fY - m_tInfo.fY) + iScrollY;
	float m_pMouse_R = (float)sqrt(m_pMouse_X * m_pMouse_X + m_pMouse_Y * m_pMouse_Y);

	m_fAngle = (float)acos(m_pMouse_X / m_pMouse_R) * 180 / PI;

	m_tPosin.x = LONG(m_tInfo.fX + m_fDiagonal * cos(m_fAngle * (PI / 180.f)));

	if (m_pMouse_Y < 0)
	{
		m_fAngle *= -1;
	}

	m_tPosin.y =  LONG(m_tInfo.fY + m_fDiagonal * sin(m_fAngle * (PI / 180.f))) ;

}

bool CPlayer::Posin_half_Check()
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	return m_pMouse->Get_Info().fX > this->m_tInfo.fX + iScrollX;
}


