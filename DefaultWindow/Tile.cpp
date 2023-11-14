#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
	: m_iDrawID(0), m_iOption(0)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_eRender = BACKGROUND;
}

int CTile::Update()
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX, TILECY, hMemDC, TILECX * m_iDrawID, 0, SRCCOPY);
}

void CTile::Release()
{
}
