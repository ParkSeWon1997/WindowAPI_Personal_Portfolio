#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include"PngMrg.h"
#include "SoundMgr.h"

float g_fVolume(1.f);
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
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");



	//PngMrg::Get_Instance()->Insert_Png(L"../Image/Button/ExitOff_Kor.png", L"ExitOff");
	//PngMrg::Get_Instance()->Insert_Png(L"../Image/Button/ExitOn_Kor.png", L"ExitOn");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Menu/Sky_Day.png", L"Default_Map");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Menu/MainLogo.png", L"Default_Map2");

	
	CObj*	pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	CSoundMgr::Get_Instance()->PlaySound(L"0.Town-sharedassets3.assets-340.wav", SOUND_EFFECT, g_fVolume);
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
	
	Graphics graphics(hMemDC);
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Default_Map"), 0, 0, 
		800,600);

	int Harf_Width = PngMrg::Get_Instance()->Get_Image(L"Default_Map2")->GetWidth()*0.5;
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Default_Map2"),
		(800- PngMrg::Get_Instance()->Get_Image(L"Default_Map2")->GetWidth())*0.5,0,300- Harf_Width,200);


	
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
