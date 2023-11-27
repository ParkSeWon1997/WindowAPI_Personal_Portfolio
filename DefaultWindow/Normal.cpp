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
#include "TileMgr.h"

#include"EasyMapLindeMgr.h"


static float g_fVolume = 0.7f;
Normal::Normal()
{
}

Normal::~Normal()
{
	Release();

	
}

void Normal::Initialize()
{
	dynamic_cast<CPlayer*>(CPlayer::Get_Instance())->Set_SC_ID(SCENEID::SC_NORMAL);
	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(0.f,600.f,0));
	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(100.f, 200.f, 0));
	CSoundMgr::Get_Instance()->PlaySound(L"2.IceField-sharedassets10.assets-124.wav", SOUND_BGM, g_fVolume);

	EasyMapLindeMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Data2();
}

void Normal::Update()
{
	//if (CKeyMgr::Get_Instance()->Key_Pressing('0'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	//}

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void Normal::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();


}

void Normal::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"MapBack");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Map_Layer"), 0,0,1280,800);



	//bmp파일  특정 색상을 빼주는 작업
	// //추후 수정하기
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


	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	EasyMapLindeMgr::Get_Instance()->Render(hDC);
}

void Normal::Release()
{
	
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(STAGE_ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
