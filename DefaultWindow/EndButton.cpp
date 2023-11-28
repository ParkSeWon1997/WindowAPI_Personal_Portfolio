#include "stdafx.h"
#include "EndButton.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PngMrg.h"

EndButton::EndButton() : m_iDrawID(0)
{
}

EndButton::~EndButton()
{
    Release();
}

void EndButton::Initialize()
{
    m_tInfo.fCX = 94.f;
    m_tInfo.fCY = 19.f;

    m_eRender = UI;
}

int EndButton::Update()
{
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void EndButton::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))		// 마우스와 렉트 충돌 함수
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"EndButton", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_VILLAGE);
			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void EndButton::Render(HDC hDC)
{
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey),
		Rect(m_tRect.left, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY),
		m_tInfo.fCX * m_iDrawID,
		m_tInfo.fCY * 0,
		m_tInfo.fCX, m_tInfo.fCY, UnitPixel);
}

void EndButton::Release()
{
}
