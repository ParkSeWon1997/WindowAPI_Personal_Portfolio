#include "stdafx.h"
#include "Mouse.h"
#include"PngMrg.h"
#include "ScrollMgr.h"

CObj* CMouse::m_Instance = nullptr;
CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	//PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Cusor/BasicCursor.png", L"Mouse_cousor");
}

int CMouse::Update()
{
	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x+ iScrollX;
	m_tInfo.fY = (float)ptMouse.y+ iScrollY;




#ifdef _DEBUG

	if (dwFrameTime + 1000 < GetTickCount())
	{
		cout << "¸¶¿ì½º ÁÂÇ¥ : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		dwFrameTime = GetTickCount();
	}

#endif


	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	//Offset();
	ShowCursor(TRUE);

}

void CMouse::Render(HDC hDC)
{

	//Graphics	g(hDC);
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Mouse_cousor"), ptMouse.x,ptMouse.y);



}

void CMouse::Release()
{
}

void CMouse::Offset()
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
