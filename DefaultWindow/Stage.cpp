#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include"BossMonster.h"
#include"Entry.h"
#include"PngMrg.h"
#include"DefalutMonster.h"
#include"StageEntry.h"
#include "SceneMgr.h"
#include "Normal.h"
#include "SoundMgr.h"

static float g_fVolume = 1.f;

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{



}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	//CSoundMgr::Get_Instance()->PlaySound(L"0.Town-sharedassets3.assets-340.wav", SOUND_BGM, g_fVolume);

}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	


	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	//Back ¹è°æ
	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer0"), 0, 0, 1200, 675);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer1"), 0-(iScrollX*0.05), 400+ iScrollY, 1280, 532);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer2"), 0+ (iScrollX*0.3), 400+ iScrollY, 1200, 356);


	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SecondFloor3"), 0+ iScrollX,  (WINCY-400) + iScrollY, 1388, 288);


	//CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

}

void CStage::Release()
{

	CObjMgr::Get_Instance()->Delete_ID(ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
