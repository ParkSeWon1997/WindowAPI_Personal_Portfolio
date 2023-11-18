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

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	// 플레이어 추가	
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CPlayer::Get_Instance());
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<BossMonster>::Create());
	CObjMgr::Get_Instance()->Add_Object(ENTRY, CAbstractFactory<Entry>::Create());
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create());
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<StageEntry>::Create());

	CLineMgr::Get_Instance()->Initialize();

	CTileMgr::Get_Instance()->Load_Data();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	//CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

}

void CStage::Release()
{

}
