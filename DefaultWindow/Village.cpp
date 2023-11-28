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
#include "TileMgr.h"

static float g_fVolume = 1.f;
Village::Village()
{
	//m_pCPlayer = CPlayer::Get_Instance();
}

Village::~Village()
{
	Release();
}

void Village::Initialize()
{
	//if (m_pCPlayer==nullptr) {
	//	CObjMgr::Get_Instance()->Add_Object(PLAYER, m_pCPlayer);
	//}
	dynamic_cast<CPlayer*>(CPlayer::Get_Instance())->Set_SC_ID(SCENEID::SC_VILLAGE);
	CObjMgr::Get_Instance()->Add_Object(ENTRY, CAbstractFactory<Entry>::Create());
	//CTileMgr::Get_Instance()->Load_Data4();

	CLineMgr::Get_Instance()->Initialize();

	

}

void Village::Update()
{
	CPlayer::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"0.Town-sharedassets3.assets-340.wav", SOUND_BGM, g_fVolume);
	
}

void Village::Late_Update()
{




	if (CCollisionMgr::CollisionRect_to_Rect(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_ObjList(ENTRY)))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_NORMAL);

	}


	CTileMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

	
	


	
}

void Village::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	HDC		NewhGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"NewTownBGbmp");
	BitBlt(hDC, 50+ iScrollX, 175+ iScrollY, 1200, 732, NewhGroundDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(hDC,
		0,
		0,
		1280,
		800,
		NewhGroundDC,
		0,
		0,
		1280,
		800,
		RGB(255, 255, 255));
	

	
	Graphics g(hDC);
	//g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BackLayer1"), 0 , 400 , 1280, 532);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"SecondFloor3"), 0+200+ iScrollX, (WINCY - 300) + iScrollY, 900, 188);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Tree0"), 400+ iScrollX, 700-122+ iScrollY, 104, 122);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Tree1"), 600+ iScrollX, 500-77+ iScrollY, 67, 77);

	


	CTileMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

}

void Village::Release()
{


	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	//CPlayer::Destroy_Instance();

}
