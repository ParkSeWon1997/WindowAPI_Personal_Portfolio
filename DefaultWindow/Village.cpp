#include "stdafx.h"
#include "Village.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Entry.h"
#include "AbstractFactory.h"

#include "LineMgr.h"
#include "BmpMgr.h"
#include "PngMrg.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "StageEntry.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include"SubMonster.h"

#include"BossMonster.h"
#include"Shield.h"
#include "PlayerUI.h"
#include"Ground.h"

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

	

}

void Village::Update()
{
	CObjMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"0.Town-sharedassets3.assets-340.wav", SOUND_BGM, g_fVolume);
	
}

void Village::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	
	


	
}

void Village::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	//
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"TownBGbmp");
	//
	//
	//GdiTransparentBlt(hDC,
	//	100,
	//	100,
	//	1280,
	//	800,
	//	hMemDC,
	//	0,
	//	0,
	//	1280,
	//	532,
	//	RGB(255, 255, 255));







	
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer1"), 0 - (iScrollX * 0.05), 400 + iScrollY, 1280, 532);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SecondFloor3"), 0 + iScrollX, (WINCY - 400) + iScrollY, 1388, 288);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Tree0"), 400 , 700-122 , 104, 122);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Tree1"), 600 , 400-77 , 67, 77);


	//CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

}

void Village::Release()
{


	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(ENTRY);
	//CObjMgr::Get_Instance()->Delete_ID(ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
