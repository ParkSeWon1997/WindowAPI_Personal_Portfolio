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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Exit.png", L"Exit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Option.png", L"Edit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Play.png", L"Start");



	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/BackCloud.png", L"BackCloud");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/Sky_Day.png", L"Sky_Day");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/MapBase 1_1.png", L"MapBase");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/MainLogo01.png", L"MainLogo");

	
	CObj*	pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f, 0.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	CSoundMgr::Get_Instance()->PlaySound(L"title-sharedassets1.assets-54.wav", SOUND_EFFECT, g_fVolume);
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
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	Graphics graphics(hDC);



	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"MapBase"), 0, 0, 
		1200,800);
	PngMrg::Get_Instance()->Get_Image(L"MainLogo");

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Sky_Day"), 0, 0,
		1200, 800);


	PngMrg::Get_Instance()->Get_Image(L"MainLogo");
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"MainLogo"),
		Rect(((WINCX*0.5)-316) , (WINCY*0.3) , 316, 156),
		316 * m_tFrame.iFrameStart,
		156 * m_tFrame.iMotion,
		316, 156, UnitPixel);

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackCloud"),
		Rect(0, 0, 1200, 360),
		316 + MoveSky,
		156 ,
		1280, 360, UnitPixel);

	//int Harf_Width = PngMrg::Get_Instance()->Get_Image(L"Default_Map2")->GetWidth()*0.5;
	//graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Default_Map2"),
	//	(800- PngMrg::Get_Instance()->Get_Image(L"Default_Map2")->GetWidth())*0.5,0,300- Harf_Width,200);




	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
