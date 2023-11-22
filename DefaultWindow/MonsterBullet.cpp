#include "stdafx.h"
#include "MonsterBullet.h"
#include"PngMrg.h"
MonsterBullet::MonsterBullet()
{
}

MonsterBullet::~MonsterBullet()
{
	Release();
}

void MonsterBullet::Initialize()
{

	m_tInfo.fCX = 18.f;
	m_tInfo.fCY = 36.f;

	m_fSpeed = 1.f;

	m_fDamage = 0.f;
	m_fHP = 1.f;
	m_eRender = GAMEOBJECT;
}

int MonsterBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));

	//if (m_tInfo.fX>WINCX||m_tInfo.fX<0||m_tInfo.fY>WINCY||m_tInfo.fY<0)
	//{
	//	delete this;
	//}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void MonsterBullet::Late_Update()
{
}

void MonsterBullet::Render(HDC hDC)
{

	Graphics g(hDC);
	g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	g.RotateTransform(m_fAngle+90);
	g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);


	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SubMonster_Bullet"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 18.f, 36.f);
	//Rectangle(hDC, m_tRect.left, m_tRect.top , m_tRect.right , m_tRect.bottom );
}

void MonsterBullet::Release()
{
}
