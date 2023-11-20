#include "stdafx.h"
#include "SubMonster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include"MonsterBullet.h"
#include"GuideBullet.h"
#include"BossMonster.h"

SubMonster::SubMonster() : Monster_AngleAdd(0.f), m_fDistance(0.f)
{

}

SubMonster::SubMonster(float _X, float _Y)
{
}

SubMonster::~SubMonster()
{

}

void SubMonster::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDistance = 100.f;
	m_fSpeed = 2.75f;
	SubState = SUBMOSTER_TATE123::IDLE;
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
	FrameChek++;


	


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void SubMonster::Late_Update()
{
	CheckOverrWindow();

	if (dynamic_cast<BossMonster*>(CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))) {
		SubMonster_pattern();
	}
}

void SubMonster::Render(HDC hDC)
{
	Graphics g(hDC);
	//g.DrawImage();

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void SubMonster::Release()
{

}

void SubMonster::Attack()
{
	if (dwFrameTime + 200 < GetTickCount()) {
		if (FireCount < 10)
		{
			++FireCount;
		CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<MonsterBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd));
		dwFrameTime = GetTickCount();
		}


	}


}

void SubMonster::Target_Attack()
{
	if (GFireCount <20)
	{
	CObjMgr::Get_Instance()->Add_Object(SUB_MONSTER_BULLET, CAbstractFactory<CGuideBullet>::Create(this->m_tInfo.fX, this->m_tInfo.fY, Monster_AngleAdd));
		++GFireCount;
	
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

void SubMonster::SubMonster_pattern()
{
	switch (SubState)
	{
	case SUBMOSTER_TATE123::IDLE:
	{   //Move()
		AroundBOss();
		Attack();
		if (FrameChek>500)
		{
			
			SubState = SUBMOSTER_TATE123::ATTACK;
			FrameChek = 0;
		}
	}  break;

	case SUBMOSTER_TATE123::ATTACK:
	{
		
		//for (auto iter : CObjMgr::Get_Instance()->Get_ObjListProperty(MONSTER))
		//{
		//	if (this->m_tInfo.fX> iter->Get_Info().fX)
		//	{
		//		m_tInfo.fX = iter->Get_Info().fX + m_fSpeed;
		//			//this->m_tInfo.fX += m_fSpeed;
		//	}
		//	
		//
		//}

		//if(CObjMgr::Get_Instance()->Get_ObjList(MONSTER)->Get_Info().fX)

		break;
	}
	case SUBMOSTER_TATE123::TARGET_SHOT:
	{
		

	}
	case SUBMOSTER_TATE123::MOVE_TO_BOSS:
	{
	

		break;

	}

	case SUBMOSTER_TATE123::END:
	{
		break;
	}

	}


}
