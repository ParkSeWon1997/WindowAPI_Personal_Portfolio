// 23.11.09 (¸ñ) _Á¶¹Î±â

#include "stdafx.h"
#include "CTimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	:m_dwCurTime(0.f)
	, m_dwPrevTime(0.f)
	, m_fDT(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}


void CTimeMgr::Update()
{
	m_dwCurTime = GetTickCount64();
	m_fDT = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
}

void CTimeMgr::Initialize()
{
	m_dwCurTime = GetTickCount64();
	m_dwPrevTime = GetTickCount64();

}

