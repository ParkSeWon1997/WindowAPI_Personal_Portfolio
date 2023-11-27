#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include"Mouse.h"
//Mnager
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include"PngMrg.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

//weapon
#include"Gun.h"
#include"Sword.h"
#include "PlayerBullet.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "Bullet.h"
//UI
#include"PlayerUI.h"
#include"PlayerWeaponBox.h"


CObj* CPlayer::m_Instance = nullptr;
static float  g_fVolume = 1.0f;


bool testLand = false;
CPlayer::CPlayer() : m_bJump(false), m_fPower(0.f), m_fAccelTime(0.f)
, m_eCurState(IDLE), m_ePreState(PS_END), m_pWeaponList{}, IsGround(false), nSoundCount(0)
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

	m_InitX = 100.f;
	m_InitY = 500.f;

	m_tInfo = { m_InitX, m_InitY, 64, 64 };

	m_fSpeed = 5.f;
	m_fDiagonal = 20.f;
	m_fPower = 10.f;

	
	this->m_fHP = 100.f;
	this->m_fDamage = 10.f;
	
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	DashCount = 2;

	
	CObjMgr::Get_Instance()->Add_Object(OBJID::PlAYER_UI, CAbstractFactory<PlayerUI>::Create(80.f, 50.f, 0));
	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER_WEAPON_BOX, CAbstractFactory<PlayerWeaponBox>::Create());
	
	

	//m_bDead = true;
	m_pStateKey = L"Player";
	

	m_eRender = GAMEOBJECT;



}

int CPlayer::Update()
{

	dynamic_cast<PlayerUI*>(CObjMgr::Get_Instance()->Get_ObjList(PlAYER_UI))->Set_UI_HpBar(100.f, m_fHP);
	Jump();

	Key_Input();
	nSoundCount++;


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
		cout << "�÷��̾� ��ǥ : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		cout << "�÷��̾� HP : " << m_fHP << endl;

		dwFrameTime = GetTickCount();
	}




#endif
}

void CPlayer::Render(HDC hDC)
{
	



	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	//MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY + iScrollY, nullptr);
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
	CObjMgr::Get_Instance()->Delete_ID(PlAYER_UI);
	CObjMgr::Get_Instance()->Delete_ID(PLAYER_WEAPON_BOX);
	

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
			CSoundMgr::Get_Instance()->PlaySound(L"step_lth1-sharedassets2.assets-325.wav", SOUND_PLAYER_WALK, g_fVolume);
			m_tInfo.fX -= m_fSpeed;
			
		}
	
		if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		{
			m_eCurState = RUN;
			CSoundMgr::Get_Instance()->PlaySound(L"step_lth1-sharedassets2.assets-325.wav", SOUND_PLAYER_WALK, g_fVolume);
			m_tInfo.fX += m_fSpeed;
		}

		
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_InitSpeedY = -m_fGravity * 3.0f;

			m_InitX= m_tInfo.fX;
			m_InitY = m_tInfo.fY;
			m_bJump = true;
			
			
			m_eCurState = JUMP;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
		{
			if (DashCount > 0 && DashCount <= 2) {
				m_InitSpeedY = -m_fGravity * 3.0f;

				m_InitX = m_tInfo.fX;
				m_InitY = m_tInfo.fY;
				m_bJump = true;
				DashCount--;

				m_eCurState = JUMP;
			}
		}

		
	





		if (CKeyMgr::Get_Instance()->Key_Down('2'))
		{
			//���� �Ȱ��� OBJID�� ������ �Ѵٸ� ���� ���� �θ� Ŭ�������� ������ �Լ��� �־�� �Ѵ� (�ϴ� �ٿ� ĳ������ ��쿡�� Ȯ�ε�) 
			//���൵�� �ش� �Լ��� �����Ϸ��� �� �� ������ OBJID�� Set_ImageKey()�Լ��� ������ ������ �� ( Get_ObjList()�� OBJID�� front()�� ��ȯ�ϰ� ���� )
			//Get_ObjList()�� �����θ� �� ���� ��
			dynamic_cast<PlayerWeaponBox*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER_WEAPON_BOX))->Set_ImageKey(L"Player_Gun_Rusiian");
			m_eWeaponMode = CPlayer::GUN;
			CObjMgr::Get_Instance()->Delete_ID(OBJID::SWORD);
			m_pWeaponList[CPlayer::SWORD] = nullptr;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
		{
			dynamic_cast<PlayerWeaponBox*>(CObjMgr::Get_Instance()->Get_ObjList(PLAYER_WEAPON_BOX))->Set_ImageKey(L"Player_Sword_FireDragon");
			m_eWeaponMode = CPlayer::SWORD;
			CObjMgr::Get_Instance()->Delete_ID(OBJID::GUN);
			m_pWeaponList[CPlayer::GUN] = nullptr;

		}
		if (CKeyMgr::Get_Instance()->Key_Pressing('0'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
		}


		//if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		{
			if (m_eWeaponMode == CPlayer::GUN)
			{
				dynamic_cast<Gun*>(CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN))->FIre(true);
			}
			if (m_eWeaponMode == CPlayer::SWORD)
			{
				dynamic_cast<Sword*>(CObjMgr::Get_Instance()->Get_ObjList(OBJID::SWORD))->AttachCollisionBox(m_tPosin.x, m_tPosin.y);
			}

		}
	
	}

}

void CPlayer::Jump()
{


	if (m_bJump)
	{
		//y���� ��� �(���ӵ��� �߷� ���ӵ�)
		//y�� �ӵ� ����
		m_InitSpeedY = m_InitSpeedY + m_fGravity * m_t;

		//y�� ��ġ ����
		m_tInfo.fY = m_tInfo.fY + m_InitSpeedY * m_t;
	}



	//t�� �ð��� ���������� ������ ������� t�� �þ�ٸ� �����ϴ� �ӵ� ���� 
	//�׸��� �����ϴ� �ӵ��� ����
	m_t = 1.0f;

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


		if (m_pWeaponList[CPlayer::GUN] == nullptr)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::GUN, CAbstractFactory<Gun>::Create(this->m_tPosin.x, this->m_tPosin.y, this->m_fAngle));
			
			m_pWeaponList[CPlayer::GUN] = CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN);
		}
		else
		{

			CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN)->Set_Pos(m_tPosin.x, m_tPosin.y);
			CObjMgr::Get_Instance()->Get_ObjList(OBJID::GUN)->Set_Angle(m_fAngle);

		}
		break;
	case CPlayer::SWORD:
		if (m_pWeaponList[CPlayer::SWORD] == nullptr)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::SWORD, CAbstractFactory<Sword>::Create(this->m_tPosin.x, this->m_tPosin.y-20, this->m_fAngle));

			m_pWeaponList[CPlayer::SWORD] = CObjMgr::Get_Instance()->Get_ObjList(OBJID::SWORD);
		}
		else
		{

			CObjMgr::Get_Instance()->Get_ObjList(OBJID::SWORD)->Set_Pos(m_tPosin.x, m_tPosin.y - 20);
			CObjMgr::Get_Instance()->Get_ObjList(OBJID::SWORD)->Set_Angle(m_fAngle);

		}
		break;
	}

}

void CPlayer::Set_Posin()
{
	if (!m_bDead)
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

	m_tPosin.y =  LONG(m_tInfo.fY + m_fDiagonal * sin(m_fAngle * (PI / 180.f)))+10 ;//�㸮�㿡 ���� +10����
	}

}

bool CPlayer::Posin_half_Check()
{
	if (!m_bDead)
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		return m_pMouse->Get_Info().fX > this->m_tInfo.fX + iScrollX;

	}
	else
		return false;
}


