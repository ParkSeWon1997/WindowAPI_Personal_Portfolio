#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - 64 * TILEX > m_fScrollX)
		m_fScrollX = WINCX - 64 * TILEX;

	if (WINCY - 64 * TILEY > m_fScrollY)
		m_fScrollY = WINCY - 64 * TILEY;

}
