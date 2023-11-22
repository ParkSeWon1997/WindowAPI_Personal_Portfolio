#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "PngMrg.h"


CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
}

void CGuideBullet::Initialize()
{
	m_tInfo.fCX = 36.f;
	m_tInfo.fCY = 72.f;
	m_fDamage = 1.f;
	m_fSpeed = 5.f;
	m_eRender = GAMEOBJECT;

	
	
}

int CGuideBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(PLAYER, this);
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


	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update()
{
}

void CGuideBullet::Render(HDC hDC)
{

	Graphics g(hDC);
	g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	g.RotateTransform(m_fAngle);
	g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);

	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SubMonster_Bullet"),
		(m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), 18.f, 36.f);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SubMonster_Bullet"),
	//	Rect((m_tInfo.fX - m_tInfo.fCX * 0.5),
	//		(m_tInfo.fY - m_tInfo.fCY * 0.5),
	//		m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX, m_tInfo.fCY, 9.f, 18.f, UnitPixel);
	//Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right, m_tRect.bottom );
}

void CGuideBullet::Release()
{
}

void CGuideBullet::Move_LastTarget_Local()
{
	m_pTarget->Get_Info().fX;
	m_pTarget->Get_Info().fY;
}
