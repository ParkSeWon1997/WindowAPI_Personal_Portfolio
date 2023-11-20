#include "stdafx.h"
#include "BossField.h"
#include"StageEntry.h"
#include"DefalutMonster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossMonster.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include"PngMrg.h"
#include "Entry.h"

BossField::BossField()
{
}

BossField::~BossField()
{
	Release();
}

void BossField::Initialize()
{

	//PngMrg::Get_Instance()->Insert_Png()
	CObjMgr::Get_Instance()->Add_Object(BOSS_MONSTER, CAbstractFactory<BossMonster>::Create(200.f,500.f,0));

	CLineMgr::Get_Instance()->Initialize();

}

void BossField::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void BossField::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void BossField::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"MapBack");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Map_Layer"), 0, 0, 1280, 800);

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Map_Layer_Bmp");

	GdiTransparentBlt(hDC,
		0,
		0,
		1280,
		800,
		hMemDC,
		0,
		0,
		1280,
		800,
		RGB(255, 255, 255));


	CObjMgr::Get_Instance()->Render(hDC);

	CLineMgr::Get_Instance()->Render(hDC);
}

void BossField::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BOSS_MONSTER);

}
