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
#include "SoundMgr.h"
#include"Player.h"
#include"Snow.h"
#include "TileMgr.h"


static float g_fVolume = 0.7f;
BossField::BossField()
{
}

BossField::~BossField()
{
	Release();
}

void BossField::Initialize()
{
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CPlayer::Get_Instance());
	//PngMrg::Get_Instance()->Insert_Png()
	CObjMgr::Get_Instance()->Add_Object(BOSS_MONSTER, CAbstractFactory<BossMonster>::Create(WINCX*0.5,WINCY*0.3,0));
	CLineMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"2.IceBoss-sharedassets12.assets-132.wav", SOUND_BGM, g_fVolume);
	//CTileMgr::Get_Instance()->Load_Data();

	
}

void BossField::Update()
{
	if (CPlayer::Get_Instance()->Get_Dead())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlaySound(L"dead-sharedassets2.assets-304.wav", SOUND_PLAYER_DEAD, g_fVolume);
	}
	//CreateSnow();
	CObjMgr::Get_Instance()->Update();
	//CTileMgr::Get_Instance()->Update();
}

void BossField::Late_Update()
{
	//CheckWindowOver();
	CObjMgr::Get_Instance()->Late_Update();
	//CTileMgr::Get_Instance()->Late_Update();
}

void BossField::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"MapBack");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Map_Layer"), 0, 0, 1280, 800);

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"NewMap_Layer_Bmp");

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
	//CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);

	CLineMgr::Get_Instance()->Render(hDC);
}

void BossField::Release()
{

	CObjMgr::Get_Instance()->Delete_ID(BOSS_MONSTER);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

}

void BossField::CreateSnow()
{
	if (CObjMgr::Get_Instance()->Get_ObjListProperty(SNOW).size() < 1) {
		CObjMgr::Get_Instance()->Add_Object(SNOW, CAbstractFactory<Snow>::Create(WINCX*0.5, 0, 0));
	}
}

void BossField::CheckWindowOver()
{
	if (CObjMgr::Get_Instance()->Get_ObjList(SNOW))
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(SNOW)->Get_Info().fX > WINCX ||
			CObjMgr::Get_Instance()->Get_ObjList(SNOW)->Get_Info().fX < 0 ||
			CObjMgr::Get_Instance()->Get_ObjList(SNOW)->Get_Info().fY > WINCY ||
			CObjMgr::Get_Instance()->Get_ObjList(SNOW)->Get_Info().fY < 0)
		{
			CObjMgr::Get_Instance()->Get_ObjList(SNOW)->Set_Dead();
		}

	}
}
