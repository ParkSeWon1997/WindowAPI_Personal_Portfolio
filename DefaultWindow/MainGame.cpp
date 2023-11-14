#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "PngMrg.h"
#include"ElapseTimeMgr.h"
#include "CTimeMgr.h"
CMainGame::CMainGame() 
	: m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CTimeMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
	CMouse::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
	CMouse::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CMouse::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
#pragma region 프레임 출력

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

#pragma endregion 프레임 출력

	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);
	CMouse::Get_Instance()->Render(hMemDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	// 윈도우 문자열 출력 함수

	//TCHAR	szBuff[32] = L"";

	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[BULLET].size()); 

	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	
	// wsprintf : winapi 라이브러리에서 제공하는 함수
	// swprintf_s : visual c++ 라이브러리에서 제공하는 함수, 모든 서식 문자를 지원

	//TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	//RECT	rc{ 100, 100, 200, 200 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);

}

void CMainGame::Release(void)
{

	CBmpMgr::Destroy_Instance();
	PngMrg::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CMouse::Destroy_Instance();
	CTimeMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
