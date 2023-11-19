#include "stdafx.h"
#include "Normal.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "DefalutMonster.h"
#include "LineMgr.h"
#include "PngMrg.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "StageEntry.h"
#include "Entry.h"
#include "SoundMgr.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

Normal::Normal()
{
}

Normal::~Normal()
{
	Release();
}

void Normal::Initialize()
{
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/BossMap/Tile/BGLayer_1 #231958.png", L"Map_Layer");
	//PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Exit.png", L"Exit");
	//CObj* DefaultMonster = CAbstractFactory<DefalutMonster>::Create(WINCX * 0.5, 400.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(MONSTER, DefaultMonster);
	//
	//DefaultMonster = CAbstractFactory<DefalutMonster>::Create(WINCX * 0.3, 400.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(MONSTER, DefaultMonster);
	//
	// DefaultMonster = CAbstractFactory<DefalutMonster>::Create(WINCX *0.1, 400.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(MONSTER, DefaultMonster);
	

	//CObj* pStageEntry= CAbstractFactory<StageEntry>::Create(100.f, 700.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, pStageEntry);
	//
	//pStageEntry= CAbstractFactory<StageEntry>::Create(200.f, 400.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, pStageEntry);
	//
	//pStageEntry= CAbstractFactory<StageEntry>::Create(300.f, 400.f, 0.f);
	//CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, pStageEntry);

	CLineMgr::Get_Instance()->Initialize();

}

void Normal::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void Normal::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (CKeyMgr::Get_Instance()->Key_Pressing('0'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	}

}

void Normal::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Map_Layer"), 0,0,1280,800);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void Normal::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(STAGE_ENTRY);
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
