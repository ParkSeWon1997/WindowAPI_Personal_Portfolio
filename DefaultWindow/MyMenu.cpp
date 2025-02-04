#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include"PngMrg.h"
#include "SoundMgr.h"

extern	float g_fVolume(1.f);

float	MoveSky(1.0f);
CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;

	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();



	
	CObj*	pObj = CAbstractFactory<CMyButton>::Create(WINCX*0.5, 400.f, 0.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(WINCX * 0.5, 500.f, 0.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(WINCX * 0.5, 600.f, 0.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	CSoundMgr::Get_Instance()->PlaySound(L"title-sharedassets1.assets-54.wav", SOUND_BGM, g_fVolume);
}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update()
{
	Move_Frame();
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	
	MoveSky += 0.2f;

	//�����
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	Graphics graphics(hDC);


	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Sky_Day"), 0, 0,
		1280, 800);

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackCloud"),
		Rect(0, 0, 1280, 360),
		316 + MoveSky,
		156 ,
		1280, 360, UnitPixel);
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"FrontCloud"),
		Rect(300, 0, 1200, 360),
		316 - MoveSky,
		156 ,
		1280, 360, UnitPixel);


	PngMrg::Get_Instance()->Get_Image(L"MainLogo");
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"MainLogo"),
		Rect((WINCX*0.5)*0.75, (WINCY*0.2) , 316, 156),
		316 * m_tFrame.iFrameStart,
		156 * m_tFrame.iMotion,
		316, 156, UnitPixel);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
