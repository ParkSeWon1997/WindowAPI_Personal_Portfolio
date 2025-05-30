#include "stdafx.h"
#include "SubMonster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include"MonsterBullet.h"
#include"GuideBullet.h"
#include"BossMonster.h"
#include"PngMrg.h"
#include"SubMonsterHpBar.h"
SubMonster::SubMonster() : Monster_AngleAdd(0.f), m_fDistance(0.f), m_pSubMonsterHpBar(nullptr)
{

}

SubMonster::SubMonster(float _X, float _Y)
{
}

SubMonster::~SubMonster()
{
	Release();
}

void SubMonster::Initialize()
{
	m_tInfo.fCX = 112.f;
	m_tInfo.fCY = 44.f;
	m_fHP = 40.f;
	m_fDistance = 100.f;
	m_fSpeed = 2.75f;
	m_pSubMonsterHpBar= new SubMonsterHpBar;
	m_pSubMonsterHpBar->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<SubMonsterHpBar*>(m_pSubMonsterHpBar)->Set_MaxHp(m_fHP);
	m_pSubMonsterHpBar->Initialize();
	SubState = SUBMOSTER_STATE::IDLE;
	m_eRender = GAMEOBJECT;
}

int SubMonster::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	Monster_AngleAdd += 2;
	if (Monster_AngleAdd == 360.f)
	{
		Monster_AngleAdd = 0;
	}
	m_fRotateAngle += 2;
	if (m_fRotateAngle == 360.f)
	{
		m_fRotateAngle = 0;
	}

	m_pSubMonsterHpBar->Update();
	//m_fAngle123 += 2.0f;
	FrameChek++;
	GFireCount++;

	m_bIsHit = false;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void SubMonster::Late_Update()
{
	//CheckOverrWindow();

	if (dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))) {
		SubMonster_pattern();
		m_pSubMonsterHpBar->Set_Pos(m_tInfo.fX, m_tInfo.fY+10);
		dynamic_cast<SubMonsterHpBar*>(m_pSubMonsterHpBar)->Set_CurHp(m_fHP);
		m_pSubMonsterHpBar->Late_Update();
	}
}

void SubMonster::Render(HDC hDC)
{
	Graphics g(hDC);

	g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
	g.RotateTransform(m_fRotateAngle);
	g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SubMonster"), (m_tInfo.fX-m_tInfo.fCX*0.5), (m_tInfo.fY-m_tInfo.fCY*0.5), m_tInfo.fCX, m_tInfo.fCY);
	m_pSubMonsterHpBar->Render(hDC);

	//Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right, m_tRect.bottom );
	if (m_bIsHit)
	{
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Monster_Hit_Effect"), m_tInfo.fX, m_tInfo.fY, 38.f, 47.f);
	}
}

void SubMonster::Release()
{
	Safe_Delete(m_pSubMonsterHpBar);
}

void SubMonster::Attack()
{
	if (dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))->Get_HP() < 100) {
		if (dwFrameTime + 100 < GetTickCount()) {
			if (dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))->Get_HP() < 20)
			{
				CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<MonsterBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd, 3.f));

			}

			else
			{
				CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<MonsterBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd, 7.f));

			}
			dwFrameTime = GetTickCount();
		}
		

	}
	else {
		if (dwFrameTime + 200 < GetTickCount()) {
			CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<MonsterBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd));
			dwFrameTime = GetTickCount();
		}
	}
	
}

void SubMonster::Target_Attack()
{
	if (dwFrameTime + 400 < GetTickCount()) {
		
		
			CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<CGuideBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd));
			
		
		dwFrameTime = GetTickCount();

	}
}

void SubMonster::MoveToBoss()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(BOSS_MONSTER, this);

	float		fWidth, fHeight, fDiagonal, fRadian;

	if (m_pTarget)
	{
		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		fRadian = acos(fWidth / fDiagonal);

		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sin(m_fAngle * PI / 180.f);

}

void SubMonster::AroundBOss()
{
	
		this->Set_Target((dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))));
		m_fAngle += m_fSpeed;
		m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sin(m_fAngle * (PI / 180.f));


}

void SubMonster::CheckOverrWindow()
{
	if (CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET))
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET)->Get_Info().fX > WINCX ||
			CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET)->Get_Info().fX < 0 ||
			CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET)->Get_Info().fY > WINCY ||
			CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET)->Get_Info().fY < 0)
		{
			CObjMgr::Get_Instance()->Get_ObjList(SUB_MONSTER_BULLET)->Set_Dead();
		}

	}
}

void SubMonster::Motion_Change()
{
}

void SubMonster::MoveReflection()
{
	if (m_tInfo.fX >= WINCX)
	{
		mDirX = -1.0f;
	}
	else if (m_tInfo.fX <= 0.0f)
	{
		mDirX = 1.0f;
	}
	m_tInfo.fX = m_tInfo.fX + mDirX * m_fSpeed;

	if (m_tInfo.fY >= 664.f)
	{
		mDirY = -1.0f;
	}
	else if (m_tInfo.fY <= 0.0f)
	{
		mDirY = 1.0f;
	}
	m_tInfo.fY = m_tInfo.fY + mDirY * m_fSpeed;
}

void SubMonster::SubMonster_pattern()
{
	switch (SubState)
	{
	case SUBMOSTER_STATE::IDLE:
	{   //Move()
		AroundBOss();
		
		if (FrameChek>300)
		{
			
			SubState = SUBMOSTER_STATE::ATTACK;
			FrameChek = 0;
		}

		if (dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))->Get_HP() < 20)
		{
			SubState = SUBMOSTER_STATE::MOVE_TO_BOSS;
		}
	}  break;

	case SUBMOSTER_STATE::ATTACK:
	{
		Attack();
		if (FrameChek > 200)
		{
			SubState = SUBMOSTER_STATE::TARGET_SHOT;
			FrameChek = 0;
		}

		break;
	}
	case SUBMOSTER_STATE::TARGET_SHOT:
	{
		
		m_tInfo.fX += m_fSpeed * cos(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sin(m_fAngle * PI / 180.f);
		if (FrameChek > 300)
		{
			SubState = SUBMOSTER_STATE::IDLE;
			GFireCount = 0;
			FrameChek = 0;
		}
		break;
	}
	case SUBMOSTER_STATE::MOVE_TO_BOSS:
	{
		
		
			MoveReflection();
			Target_Attack();
		
			break;
	}

	case SUBMOSTER_STATE::SUB_STATE_END:
	{
		if (FrameChek > 300)
		{
			SubState = SUBMOSTER_STATE::IDLE;
			FrameChek=0;
		}
		break;
	}

	}


}
