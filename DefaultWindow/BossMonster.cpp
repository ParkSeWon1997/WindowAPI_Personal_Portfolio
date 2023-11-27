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
#include"IcicleBullet.h"
#include"BossUI.h"


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

	m_fHP = 200.f;

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_pStateKey = L"Boss_Monster";

	m_eRender = GAMEOBJECT;
	//m_bDead = true;

	CObjMgr::Get_Instance()->Add_Object(OBJID::MOSTER_UI, CAbstractFactory<BossUI>::Create(WINCX*0.5,WINCY*0.8,0.f));

	m_eBOSS_STATE = BossMonster::SC_BOSS_CREATE_SUB;
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
	//if (dwFrameTime + 1000 < GetTickCount()) {
	//
	//	cout << "BOSS HP : " << m_fHP << endl;
	//
	//	dwFrameTime = GetTickCount();
	//}


	dynamic_cast<BossUI*>(CObjMgr::Get_Instance()->Get_ObjList(MOSTER_UI))->Set_UI_HpBar(200.f, m_fHP);

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
	//CObjMgr::Get_Instance()->Delete_ID(MOSTER_UI);



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



void BossMonster::CreateSpear(int _Dir, float _X, float _Y)
{
	if (_Dir == 1) {
		//왼쪽에서 오른쪽으로 이동
		CObj* RightSpear = new MonsterIceSpear;
		RightSpear->Set_Pos(_X, _Y);
		RightSpear->Initialize();
		dynamic_cast<MonsterIceSpear*>(RightSpear)->Set_RotaeImage(90);
		dynamic_cast<MonsterIceSpear*>(RightSpear)->SEt_Move_DIR(BOSSMONSTER_SPEAR_DIR::MOVE_RIGHT);
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, RightSpear);

	}
	if (_Dir == 2) {
		//오른쪽에서 왼쪽으로 이동
		CObj* RightSpear = new MonsterIceSpear;
		RightSpear->Set_Pos(_X, _Y);
		RightSpear->Initialize();
		dynamic_cast<MonsterIceSpear*>(RightSpear)->Set_RotaeImage(270);
		dynamic_cast<MonsterIceSpear*>(RightSpear)->SEt_Move_DIR(BOSSMONSTER_SPEAR_DIR::MOVE_LEFT);
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, RightSpear);


	}
	if (_Dir == 3) {
		//아래에서 위로 이동
		CObj* RightSpear = new MonsterIceSpear;
		RightSpear->Set_Pos(_X, _Y);
		RightSpear->Initialize();
		dynamic_cast<MonsterIceSpear*>(RightSpear)->Set_RotaeImage(0);
		dynamic_cast<MonsterIceSpear*>(RightSpear)->SEt_Move_DIR(BOSSMONSTER_SPEAR_DIR::MOVE_UP);
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, RightSpear);

	}
	if (_Dir == 4) {
		//위에서 아래로 이동
		CObj* RightSpear = new MonsterIceSpear;
		RightSpear->Set_Pos(_X, _Y);
		RightSpear->Initialize();
		dynamic_cast<MonsterIceSpear*>(RightSpear)->Set_RotaeImage(180);
		dynamic_cast<MonsterIceSpear*>(RightSpear)->SEt_Move_DIR(BOSSMONSTER_SPEAR_DIR::MOVE_DOWN);
		CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, RightSpear);

	}


	
	
	
}

void BossMonster::CreateIcicle(float _X)
{
	CObj* pIcicle = new IcicleBullet;
	pIcicle->Set_Pos(_X,0);
	pIcicle->Initialize();
	if (m_fHP < 100)
	{
		pIcicle->Set_Speed(7.0f);
	}
	else
		pIcicle->Set_Speed(2.0f);
	CObjMgr::Get_Instance()->Add_Object(BOSS_BULLET, pIcicle);
}

void BossMonster::Boss_pattern()
{
	switch (m_eBOSS_STATE)
	{

	case BossMonster::SC_BOSS_CREATE_SUB:
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
				m_eBOSS_STATE = BossMonster::SC_BOSS_IDLE;
			}
		}

		break;
	case BossMonster::SC_BOSS_IDLE:
	{
		m_eCurState = ImageSTATE::IDLE;
		if (m_fHP < 200)
		{
			m_tInfo.fX = 200.f;
			m_tInfo.fY = 200.f;

			m_eBOSS_STATE = BOSS_STATE::SC_BOSS_EASY;
			FrameCheck = 0;

		}
		else if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBOSS_STATE = BossMonster::SC_BOSS_CREATE_SUB;
		}


		break;
	}




	case BOSS_STATE::SC_BOSS_EASY:
	{
		if (FrameCheck > 50)
		{
			m_tInfo.fX = WINCX * 0.5;
			m_tInfo.fY = WINCY * 0.3;
			if (CreateSpearCount < 3)
			{
				m_eCurState = ImageSTATE::ATTACK;
				CreateSpear(1, 0, 200);
				CreateSpear(2, 1280, 600);
				CreateSpearCount++;
			}
			else {
				m_eCurState = ImageSTATE::IDLE;
			}
		

			FrameCheck = 0;
			
		}
		if (m_fHP<150) {
			m_eBOSS_STATE = BOSS_STATE::SC_BOSS_NORMAL;
		
			CreateSpearCount = 0;
		}
	

		else if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBOSS_STATE = BossMonster::SC_BOSS_CREATE_SUB;
		}
		break;
	}

	case BOSS_STATE::SC_BOSS_NORMAL:
	{

		if (FrameCheck>50)
		{
			if (CreateIcicleCount < 3)
			{
				m_eCurState = ImageSTATE::ATTACK;
				CreateIcicle(270);
				CreateIcicle(540);
				CreateIcicle(810);
				CreateIcicle(1080);
				CreateIcicleCount++;
			}
			
			else
			{
				m_eCurState = ImageSTATE::IDLE;
			}
			FrameCheck = 0;
		}
		
		if (m_fHP < 100) {
			m_eBOSS_STATE = BOSS_STATE::SC_BOSS_HARD;
			m_tInfo.fX = 900.f;
			CreateSpearCount = 0;
			CreateIcicleCount = 0;
		}


		if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBOSS_STATE = BossMonster::SC_BOSS_CREATE_SUB;
		}
		break;

	}
	case BOSS_STATE::SC_BOSS_HARD:
	{
		if (dwFrameTime + 3000 < GetTickCount()) 
		{

				m_eCurState = ImageSTATE::ATTACK;
				CreateSpear(1, 0, 200);
				CreateSpear(2, 1280, 600);
				CreateSpear(3, 300, 800);
				CreateSpear(4, 1000, 0);

				CreateIcicle(270);
				CreateIcicle(540);
				CreateIcicle(810);
				CreateIcicle(1080);


			dwFrameTime = GetTickCount();
		}
		else
		{
			m_eCurState = ImageSTATE::IDLE;
		}
			
	
		if (m_fHP < 0)
		{
			m_eBOSS_STATE = BOSS_STATE::SC__BOSS_DEAD;

		}
		if (IsSubMonsterAlive())
		{
			CreateSubCount = 0;
			m_eBOSS_STATE = BossMonster::SC_BOSS_CREATE_SUB;
		}
		break;
	}
	case BOSS_STATE::SC__BOSS_DEAD:
	{
		m_eCurState = ImageSTATE::DEAD;

		break;
	}

	}




}
