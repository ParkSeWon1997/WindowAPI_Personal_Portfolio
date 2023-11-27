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
#include "SoundMgr.h"
#include"ImageCollection.h"
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

	
	CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
	CMouse::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	ImageCollection pImageCollection;



	CSoundMgr::Get_Instance()->Initialize();


#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

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
#pragma region ������ ���

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

#pragma endregion ������ ���

	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);
	CMouse::Get_Instance()->Render(hMemDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	// ������ ���ڿ� ��� �Լ�

	//TCHAR	szBuff[32] = L"";

	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[BULLET].size()); 

	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	
	// wsprintf : winapi ���̺귯������ �����ϴ� �Լ�
	// swprintf_s : visual c++ ���̺귯������ �����ϴ� �Լ�, ��� ���� ���ڸ� ����

	//TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	//RECT	rc{ 100, 100, 200, 200 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);

}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CTileMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CMouse::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	PngMrg::Destroy_Instance();
	CSoundMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
