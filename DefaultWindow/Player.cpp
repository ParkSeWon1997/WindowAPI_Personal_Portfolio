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


CObj* CPlayer::m_Instance = nullptr;


CPlayer::CPlayer() : m_bJump(false), m_fPower(0.f), m_fAccelTime(0.f)
, m_eCurState(IDLE), m_ePreState(PS_END)
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
	m_tInfo = { 50.f, 300.f, 32, 32 };

	m_fSpeed = 5.f;
	m_fDiagonal = 100.f;
	m_fPower = 20.f;


	//아이들, 점프, 달리기 이미지 
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/Bear.png", L"Player");


	//Dead
	//PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/CharDie #238158.png", L"Player_Dead");

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();



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
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Offset();
	Move_Frame();
	Motion_Change();
	float m_pMouse_X = (m_pMouse->Get_Info().fX - m_tInfo.fX) + iScrollX;
	float m_pMouse_Y = (m_pMouse->Get_Info().fY - m_tInfo.fY)+ iScrollY;
	float m_pMouse_R = (float)sqrt(m_pMouse_X * m_pMouse_X + m_pMouse_Y * m_pMouse_Y);

	m_fAngle = (float)acos(m_pMouse_X / m_pMouse_R) * 180 / PI;

	m_tPosin.x = iScrollX +LONG(m_tInfo.fX + m_fDiagonal * cos(m_fAngle * (PI / 180.f)));

	if (m_pMouse_Y < 0)
	{
		m_fAngle *= -1;
	}

	m_tPosin.y = iScrollY +LONG(m_tInfo.fY + m_fDiagonal * sin(m_fAngle * (PI / 180.f)));




#ifdef _DEBUG
	if (dwFrameTime + 1000 < GetTickCount()){
		cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		dwFrameTime = GetTickCount();
	}
#endif



}

void CPlayer::Render(HDC hDC)
{





	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY + iScrollY, nullptr);
	LineTo(hDC, m_tPosin.x+ iScrollX, m_tPosin.y+ iScrollY);

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
		g.DrawImage(img, Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX, (m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY, m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 32, 32, UnitPixel);
	}
	else {
		g.DrawImage(img, destinationPoints, 3, m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 32, 32, UnitPixel);
	}





}

void CPlayer::Release()
{


}

void CPlayer::Key_Input()
{
	if (m_bDead) {
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

	}
}

void CPlayer::Jump()
{
	float	fY(0.f);

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(&fY, m_tInfo.fX);

	if (m_bJump)
	{
		m_tInfo.fY -= (m_fPower * m_fAccelTime) - (9.8f * m_fAccelTime * m_fAccelTime * 0.5f);

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

//void CPlayer::Offset()
//{
//	int		iOffSet = WINCX >> 1;
//
//	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
//
//	if (iOffSet > m_tInfo.fX + iScrollX)
//		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
//
//	if (iOffSet < m_tInfo.fX + iScrollX)
//		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
//}

void CPlayer::Offset()
{
	int		iOffSetMinX = 100;
	int		iOffSetMaxX = 800;

	int		iOffSetMinY = 100;
	int		iOffSetMaxY = 500;

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

void CPlayer::Set_Posin()
{

}

bool CPlayer::Posin_half_Check()
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	return m_pMouse->Get_Info().fX > this->m_tInfo.fX + iScrollX;
}


