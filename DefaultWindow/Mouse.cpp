#include "stdafx.h"
#include "Mouse.h"

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
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	ShowCursor(FALSE);

}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMouse::Release()
{
}
