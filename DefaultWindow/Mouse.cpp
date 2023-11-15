#include "stdafx.h"
#include "Mouse.h"
#include"PngMrg.h"

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
	

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
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
