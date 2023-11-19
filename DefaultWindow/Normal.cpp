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

	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(0.f,600.f,0));
	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(100.f, 200.f, 0));


	CLineMgr::Get_Instance()->Initialize();

}

void Normal::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('0'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	}

	CObjMgr::Get_Instance()->Update();
}

void Normal::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();


}

void Normal::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"MapBack");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Map_Layer"), 0,0,1280,800);

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void Normal::Release()
{
	
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(STAGE_ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
