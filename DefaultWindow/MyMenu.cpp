#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	CObj*	pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);


}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
}
