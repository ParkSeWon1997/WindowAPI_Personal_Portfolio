#include "stdafx.h"
#include "MyEdit.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include"BmpMgr.h"

CMyEdit::CMyEdit():Image_NextX(0), Image_NextY(0)
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CTileMgr::Get_Instance()->Initialize();
}

void CMyEdit::Update()
{
	Key_Input();

	CTileMgr::Get_Instance()->Update();
}

void CMyEdit::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"MapBack");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);

	HDC		hMemDC123 = CBmpMgr::Get_Instance()->Find_Img(L"Tile1");
	BitBlt(hDC, 700, 100, TILECX, TILECY, hMemDC123, TILECX* Image_NextX, TILECY* Image_NextY, SRCCOPY);


}

void CMyEdit::Release()
{
	CTileMgr::Destroy_Instance();
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
		Image_NextX--;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
		Image_NextX++;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)) {
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);
		Image_NextY--;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)) {
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);
		Image_NextY++;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		CTileMgr::Get_Instance()->Picking(ptMouse.x, ptMouse.y, Image_NextX, Image_NextY);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Data();
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		CTileMgr::Get_Instance()->Load_Data();
		return;
	}

}

