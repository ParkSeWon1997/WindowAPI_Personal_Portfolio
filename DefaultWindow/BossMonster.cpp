#include "stdafx.h"
#include "BossMonster.h"
#include"PngMrg.h"
#include"ScrollMgr.h"
#include "KeyMgr.h"
#include"ObjMgr.h"
#include"Player.h"
#include"SubMonster.h"
#include "AbstractFactory.h"
#include"MonsterIceSpear.h"


BossMonster::BossMonster()
{
}

BossMonster::BossMonster(float _X, float _Y)
{
	m_tInfo.fX = _X;
	m_tInfo.fY = _Y;
}

BossMonster::~BossMonster()
{
	Release();
}

void BossMonster::Initialize()
{

	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	// m_tInfo = { 700.f, 300.f, 80, 80 };

	m_fHP = 300.f;

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pStateKey = L"Boss_Monster";

	m_eRender = GAMEOBJECT;
	//m_bDead = true;

	m_eBossSTATE = BossMonster::SC_CREATE_SUB;
}

int BossMonster::Update()
{
	if (m_bDead) {
		for (size_t i = 0; i < m_pSubMonsterList.size(); i++)
		{
			m_pSubMonsterList.clear();
		}

		return OBJ_DEAD;
	}
	//CObjMgr::Get_Instance()->Get_Target(PLAYER,CPlayer)
#ifdef _DEBUG
	//if (dwFrameTime + 1000 < GetTickCount()) {
	//	cout << "몬스터 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
	//	dwFrameTime = GetTickCount();
	//}
#endif

	FrameCheck++;





	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void BossMonster::Late_Update()
{


	Move_Frame();
	Motion_Change();
	Boss_pattern();





#ifdef _DEBUG
	if (dwFrameTime + 1000 < GetTickCount()) {

		cout << "보스 몬스터 HP : " << m_fHP << endl;

		dwFrameTime = GetTickCount();
	}
#endif
}

void BossMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Point destinationPoints[] = {
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),   // destination for upper-left point of original
		Point((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX,
			  (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY),  // destination for upper-right point of original
		Point((int)(m_tInfo.fX + m_tInfo.fCX * 0.5) + iScrollX,
			   (int)(m_tInfo.fY + m_tInfo.fCY * 0.5) + iScrollY) };  // destination for lower-left point of original

	Graphics g(hDC);
	Image* img = PngMrg::Get_Instance()->Get_Image(m_pStateKey);

	if (Turn_By_Player()) {
		g.DrawImage(img,
			Rect((int)(m_tInfo.fX - m_tInfo.fCX * 0.5) + iScrollX
				, (int)(m_tInfo.fY - m_tInfo.fCY * 0.5) + iScrollY
				, (int)m_tInfo.fCX, (int)m_tInfo.fCY),
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion, 78, 78, UnitPixel);
	}
	else {
		g.DrawImage(img, destinationPoints, 3, (int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iMotion, 78, 78, UnitPixel);

	}


}

void BossMonster::Release()
{

	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	//for (int i = 0; i < m_pSubMonsterList.size(); i++)
	//{
	//	m_pSubMonsterList.clear();
	//}


}

void BossMonster::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 1;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 2;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;


		}

		m_ePreState = m_eCurState;
	}
}

bool BossMonster::IsSubMonsterAlive()
{
	if (CObjMgr::Get_Instance()->Get_ObjListProperty(MONSTER).empty())
		return true;
	else
		return false;

}

void BossMonster::MoveSubMonster()
{
	for (auto& iter : CObjMgr::Get_Instance()->Get_ObjListProperty(MONSTER))
	{
		
		dynamic_cast<SubMonster*>(iter)->MoveToBoss();
		
	}

	
}

void BossMonster::CheckSpearOverrWindow()
{

	if (CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET))
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET)->Get_Info().fX > WINCX ||
			CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET)->Get_Info().fX < 0 ||
			CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET)->Get_Info().fY > WINCY ||
			CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET)->Get_Info().fY < 0)
		{
			CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET)->Set_Dead();
		}

	}

}

void BossMonster::Around_To_THis()
{
	for (auto& iter : CObjMgr::Get_Instance()->Get_ObjListProperty(MONSTER))
	{

		dynamic_cast<SubMonster*>(iter)->AroundBOss();

	}
}

void BossMonster::CreateSpear(int _Dir)
{
	switch (_Dir)
	{
	case 1:
		if (CreateSpearCount < 1) {
			CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, CAbstractFactory<MonsterIceSpear>::Create(0, this->m_tInfo.fY, 0));
			dynamic_cast<MonsterIceSpear*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_BULLET))->Set_RotaeImage(90);
			++CreateSpearCount;
		}
		break;

	case 2:
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, CAbstractFactory<MonsterIceSpear>::Create(WINCX, 400, 0));
		break;

	case 3:
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, CAbstractFactory<MonsterIceSpear>::Create(WINCX * 0.5, WINCY, 0));
		break;

	default:
		break;
	}

	
	
	
}

void BossMonster::Boss_pattern()
{
	switch (m_eBossSTATE)
	{

	case BossMonster::SC_CREATE_SUB:
		if (!m_bDead)
		{
			if (CreateSubCount < 4)
			{
				if (dwFrameTime + 500 < GetTickCount64()) {
					CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<SubMonster>::Create(this->m_tInfo.fX, this->m_tInfo.fY, 0));
					++CreateSubCount;
					dwFrameTime = GetTickCount64();
				}
			}
			else
			{
				m_eBossSTATE = BossMonster::SC_IDLE;
			}
		}

		break;
	case BossMonster::SC_IDLE:
	{
		m_eCurState = ImageSTATE::IDLE;
		if (m_fHP < 200)
		{
			m_tInfo.fX = 200.f;
			m_tInfo.fY = 200.f;

			m_eBossSTATE = BossMonster::SC_EASY;

		}
		else if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBossSTATE = BossMonster::SC_CREATE_SUB;
		}


		break;
	}




	case BossMonster::SC_EASY:
	{
		m_eCurState = ImageSTATE::ATTACK;
		CreateSpear(1);
		//MoveSubMonster();
		
		if (FrameCheck > 500)
		{
			m_tInfo.fX = WINCX * 0.5;
			m_tInfo.fY = WINCY * 0.3;

			FrameCheck = 0;
			m_eBossSTATE = BossMonster::SC_NORMAL;
		}

	

		if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBossSTATE = BossMonster::SC_CREATE_SUB;
		}
		break;
	}

	case BossMonster::SC_NORMAL:
	{
		m_eCurState = ImageSTATE::IDLE;
		break;

	}
	case BossMonster::SC_HARD:
	{
		m_eCurState = ImageSTATE::IDLE;

		break;
	}
	case BossMonster::SC_DEAD:
	{
		m_eCurState = ImageSTATE::DEAD;

		break;
	}

	}




}
