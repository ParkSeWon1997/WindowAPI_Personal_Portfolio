#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include"PngMrg.h"

CMyButton::CMyButton()
	: m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 12.f;

	m_eRender = UI;
}

int CMyButton::Update()
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))		// 마우스와 렉트 충돌 함수
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;


}

void CMyButton::Render(HDC hDC)
{
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);


	Graphics g(hDC);

	//PngMrg::Get_Instance()->Get_Image(m_pFrameKey);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey), 0, 0);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey),
		Rect( m_tInfo.fX,m_tInfo.fY,m_tInfo.fCX,m_tInfo.fCY ),
		m_tInfo.fCX * m_iDrawID,
		m_tInfo.fCY, 
		72, 12, UnitPixel);



}

void CMyButton::Release()
{
}
