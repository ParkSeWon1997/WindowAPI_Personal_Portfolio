#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"


CMonster::CMonster()
{
	ZeroMemory(m_tPoint, sizeof(m_tPoint));
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");

	m_fSpeed = 3.f;

	m_eRender = GAMEOBJECT;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	float	fDiagonal = sqrt((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) + (m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

	// 좌 상단
	m_tPoint[0].x = LONG((m_tInfo.fCX / 2.f) + cos((m_fAngle + 135.f) * PI / 180.f) * fDiagonal);
	m_tPoint[0].y = LONG((m_tInfo.fCY / 2.f) - sin((m_fAngle + 135.f) * PI / 180.f) * fDiagonal);

	// 우 상단
	m_tPoint[1].x = LONG((m_tInfo.fCX / 2.f) + cos((m_fAngle + 45.f) * PI / 180.f) * fDiagonal);
	m_tPoint[1].y = LONG((m_tInfo.fCY / 2.f) - sin((m_fAngle + 45.f) * PI / 180.f) * fDiagonal);
	
	// 좌 하단
	m_tPoint[2].x = LONG((m_tInfo.fCX / 2.f) + cos((m_fAngle + 225.f) * PI / 180.f) * fDiagonal);
	m_tPoint[2].y = LONG((m_tInfo.fCY / 2.f) - sin((m_fAngle + 225.f) * PI / 180.f) * fDiagonal);
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
		m_fAngle += 3.f;
}

void CMonster::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Monster");
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Img(L"Plg");
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"Reset");

	PlgBlt(hPlgDC,		// 회전 시킬 이미지를 어디에 그릴 것인지 설정한다.
			m_tPoint,	// 그림을 그릴 사각형의 좌표 포인터 변수 3개, 즉 배열을 전달한다.
			hMemDC,		// 어디에 있는 이미지를 그릴 것인지 설정
			0, 0,		// 그림을 그릴 이미지의 X,Y 시작 좌표
			(int)m_tInfo.fCX,	// 그림을 그릴 이미지의 가로, 세로 길이
			(int)m_tInfo.fCY,
			NULL,
			NULL,
			NULL);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

	BitBlt(hPlgDC, 0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC, 
		0, 0, SRCCOPY);

}

void CMonster::Release()
{
}
