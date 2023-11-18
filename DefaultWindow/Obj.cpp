#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_pTarget(nullptr)
, m_pFrameKey(nullptr), m_eRender(RENDER_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd) {
			
			m_tFrame.iFrameStart = 0;
		}
		m_tFrame.dwTime = GetTickCount();
	}

}
