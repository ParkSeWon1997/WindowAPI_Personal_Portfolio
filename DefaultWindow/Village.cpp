#include "stdafx.h"
#include "Village.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Entry.h"
#include "AbstractFactory.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "PngMrg.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"

static float g_fVolume = 1.f;
Village::Village()
{
}

Village::~Village()
{
	Release();
}

void Village::Initialize()
{

	CObjMgr::Get_Instance()->Add_Object(PLAYER, CPlayer::Get_Instance());
	CObjMgr::Get_Instance()->Add_Object(ENTRY, CAbstractFactory<Entry>::Create());



	CLineMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownSky_Xmas.bmp", L"Ground");


	//고정 이미지

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Temple.png", L"Temple");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TempleFront.png", L"Temple_front");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree0.png", L"Tree0");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree1.png", L"Tree1");


	//맵 중앙
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor3.png", L"SecondFloor3");

	//맵 좌측의 위치
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor_Broken0.png", L"SecondFloor_Broken0");



	//움직임 1번째 느림
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownBG_Day.png", L"BackLayer1");

	//움직임 2번째 느림
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownLayer_Day.png", L"BackLayer2");

}

void Village::Update()
{
	CObjMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"0.Town-sharedassets3.assets-340.wav", SOUND_BGM, g_fVolume);
	//CTileMgr::Get_Instance()->Update();
}

void Village::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();





	//CTileMgr::Get_Instance()->Late_Update();
}

void Village::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();




	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	//Back 배경
	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer0"), 0, 0, 1200, 675);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer1"), 0 - (iScrollX * 0.05), 400 + iScrollY, 1280, 532);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer2"), 0+ (iScrollX*0.3), 400+ iScrollY, 1200, 356);


	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SecondFloor3"), 0 + iScrollX, (WINCY - 400) + iScrollY, 1388, 288);


	//CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

}

void Village::Release()
{

	CObjMgr::Get_Instance()->Delete_ID(ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
