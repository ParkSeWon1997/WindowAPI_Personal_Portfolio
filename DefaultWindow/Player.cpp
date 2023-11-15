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
#include "CTimeMgr.h"

CPlayer::CPlayer() : m_bJump(false), m_fPower(0.f), m_fAccelTime(0.f)
, m_eCurState(IDLE), m_ePreState(PS_END)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 50.f, 300.f, 128, 128 };

	m_fSpeed = 5.f;
	m_fDiagonal = 100.f;
	m_fPower = 20.f;


	//idle
	//BearIdle0-resources.assets-230
	//BearIdle1-resources.assets-575
	//BearIdle2-resources.assets-253
	//BearIdle3-resources.assets-614
	//BearIdle4-resources.assets-596
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearIdle0-resources.assets-230.png", L"Player_Idle_01");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearIdle1-resources.assets-575.png", L"Player_Idle_02");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearIdle2-resources.assets-253.png", L"Player_Idle_03");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearIdle3-resources.assets-614.png", L"Player_Idle_04");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearIdle4-resources.assets-596.png", L"Player_Idle_05");
		m_IDLE_Sprite.push_back(L"Player_Idle_01");
		m_IDLE_Sprite.push_back(L"Player_Idle_02");
		m_IDLE_Sprite.push_back(L"Player_Idle_03");
		m_IDLE_Sprite.push_back(L"Player_Idle_04");
		m_IDLE_Sprite.push_back(L"Player_Idle_05");


	

	//jump
	//BearJump0-resources.assets-834
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearJump0-resources.assets-834.png", L"Player_Jump_00");
	m_JUMPSprite.push_back(L"Player_Jump_00");

	//Run
	//BearRun0-resources.assets-884
	//BearRun1-resources.assets-1408
	//BearRun2-resources.assets-880
	//BearRun3-resources.assets-1349
	//BearRun4-resources.assets-1184
	//BearRun5-resources.assets-623
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun0-resources.assets-884.png", L"Player_Run_01");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun1-resources.assets-1408.png", L"Player_Run_02");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun2-resources.assets-880.png", L"Player_Run_03");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun3-resources.assets-1349.png", L"Player_Run_04");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun4-resources.assets-1184.png", L"Player_Run_05");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/BearRun5-resources.assets-623.png", L"Player_Run_06");
	m_RUNSprite.push_back(L"Player_Run_01");
	m_RUNSprite.push_back(L"Player_Run_02");
	m_RUNSprite.push_back(L"Player_Run_03");
	m_RUNSprite.push_back(L"Player_Run_04");
	m_RUNSprite.push_back(L"Player_Run_05");
	m_RUNSprite.push_back(L"Player_Run_06");

	//auto iter = m_AnimBox[IDLE];
	//m_AnimBox[IDLE].front()



	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_AnimBox[IDLE].push_back(m_IDLE_Sprite);
	m_AnimBox[JUMP].push_back(m_JUMPSprite);
	m_AnimBox[RUN].push_back(m_RUNSprite);

	m_pStateKey = L"Player_Idle_01";

	m_eRender = GAMEOBJECT;

}

int CPlayer::Update()
{
	Start_Animation = ElapseTimeMgr::GetInstance().GetElapsedTime();
	Jump();

	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	
	Offset();
	Move_Frame();
	Motion_Change();
	
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);



	// HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	ElapseTimeMgr::GetInstance().GetElapsedTime();
	Graphics g(hDC);


	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);

	float ImageHarf_X = img->GetWidth() / 2;
	float ImageY = img->GetHeight()/2;


	//g.DrawImage(img, (m_tRect.left - ImageHarf_X) + iScrollX, (m_tRect.top - ImageY) + iScrollY, img->GetWidth()*2 , img->GetHeight()*2 );
	g.DrawImage(img, Rect(m_tInfo.fX- 64, m_tInfo.fY-64, m_tInfo.fCX, m_tInfo.fCY), 0, 0, 32, 32, UnitPixel);






}

void CPlayer::Release()
{


}

void CPlayer::Key_Input()
{


	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_eCurState = RUN;
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = RUN;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_bJump = true;
		m_eCurState = JUMP;
	}


	else
	{

		m_eCurState = IDLE;

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
	int		iOffSetMaxX = 700;

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
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			
			for (auto& iter : m_AnimBox[IDLE])
			{
				for (auto& IDLE_iter : iter)
				{
					
					m_pStateKey = IDLE_iter;
					
				}
			}

			
			break;
	
		case RUN:
		
			for (auto& iter : m_AnimBox[RUN])
			{
				for (auto& RUN_iter : iter)
				{
					m_pStateKey = RUN_iter;
				}
			}
			break;
	
		case ATTACK:
	
			break;
	
		case HIT:
		
			break;
	
		case DEAD:
		
			break;
	
	
		case JUMP:
			for (auto& iter : m_AnimBox[JUMP])
			{
				for (auto& JUMP_iter : iter)
				{
					m_pStateKey = JUMP_iter;
				}
			}
		

			break;
		}
	
		m_ePreState = m_eCurState;
	}

}


