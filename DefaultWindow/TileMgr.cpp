#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"


CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr() 
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	/*for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX >> 1) + (TILECX * j));
			float	fY = float((TILECY >> 1) + (TILECY * i));

			CObj*	pObj = CAbstractFactory<CTile>::Create(fX, fY, 0.f);
			m_vecTile.push_back(pObj);
		}
	}*/

}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{


	
	for (auto& iter : m_vecTile)
	{
		
		
			iter->Render(hDC);
		
	}

}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

//void CTileMgr::Picking(POINT _ptMouse, int _iDrawID, int _iOption)
//{
//	int	x = _ptMouse.x / TILECX;
//	int	y = _ptMouse.y / TILECY;
//	int		iIndex = y * TILEX + x;
//	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
//		return;
//	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Tile(_iDrawID, _iOption);
//}

void CTileMgr::Picking(float _x, float _y, int _iDrawID, int _iOption)
{
	int x = _x;
	int y = _y;
	int XX = x % TILECX;
	int YY = y % TILECY;
	CObj* tile = CAbstractFactory<CTile>::Create(x - XX, y - YY, 0);
	static_cast<CTile*>(tile)->Set_Tile(_iDrawID, _iOption);
	m_vecTile.push_back(tile);
}

void CTileMgr::Save_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/1Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecTile)
	{
		m_iXNum = dynamic_cast<CTile*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<CTile*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void CTileMgr::Save_Data2()
{
	HANDLE	hFile = CreateFile(L"../Data/2Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecTile)
	{
		m_iXNum = dynamic_cast<CTile*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<CTile*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void CTileMgr::Save_Data3()
{
	HANDLE	hFile = CreateFile(L"../Data/3Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecTile)
	{
		m_iXNum = dynamic_cast<CTile*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<CTile*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void CTileMgr::Save_Data4()
{
	HANDLE	hFile = CreateFile(L"../Data/4Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecTile)
	{
		m_iXNum = dynamic_cast<CTile*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<CTile*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void CTileMgr::Save_Data5()
{
	HANDLE	hFile = CreateFile(L"../Data/5Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecTile)
	{
		m_iXNum = dynamic_cast<CTile*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<CTile*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void CTileMgr::Load_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/1Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while(true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<CTile*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Tile Load", L"己傍", MB_OK);*/
}

void CTileMgr::Load_Data2()
{
	HANDLE	hFile = CreateFile(L"../Data/2Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<CTile*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Tile Load", L"己傍", MB_OK);*/

}

void CTileMgr::Load_Data3()
{
	HANDLE	hFile = CreateFile(L"../Data/3Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<CTile*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Tile Load", L"己傍", MB_OK);*/
}

void CTileMgr::Load_Data4()
{
	HANDLE	hFile = CreateFile(L"../Data/4Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<CTile*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Tile Load", L"己傍", MB_OK);*/
}

void CTileMgr::Load_Data5()
{
	HANDLE	hFile = CreateFile(L"../Data/5Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<CTile*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Tile Load", L"己傍", MB_OK);*/
}
