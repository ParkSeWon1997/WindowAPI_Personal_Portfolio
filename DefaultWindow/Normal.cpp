#include "stdafx.h"
#include "Normal.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "DefalutMonster.h"
#include "LineMgr.h"
#include "PngMrg.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

Normal::Normal()
{
}

Normal::~Normal()
{
	Release();
}

void Normal::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create());
	CLineMgr::Get_Instance()->Initialize();
}

void Normal::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void Normal::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void Normal::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer1"), 0 - (iScrollX * 0.05), 400 + iScrollY, 1280, 532);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void Normal::Release()
{
}
