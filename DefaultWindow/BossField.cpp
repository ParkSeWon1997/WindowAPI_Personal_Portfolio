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
#include"BossMapLineMgr.h"
#include "EndButton.h"
#include "EndEntry.h"

static float g_fVolume = 0.7f;
static float g_fBG_Volume = 0.9f;
BossField::BossField():m_pEndBotton(nullptr)
{
}

BossField::~BossField()
{
	Release();
}

void BossField::Initialize()
{
	CPlayer::Get_Instance()->Set_Pos(100.f, 680.f);
	dynamic_cast<CPlayer*>(CPlayer::Get_Instance())->Set_SC_ID(SCENEID::SC_BOSS);
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CPlayer::Get_Instance());
	//PngMrg::Get_Instance()->Insert_Png()
	CObjMgr::Get_Instance()->Add_Object(BOSS_MONSTER, CAbstractFactory<BossMonster>::Create(WINCX*0.5,WINCY*0.3,0));
	BossMapLineMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"2.IceBoss-sharedassets12.assets-132.wav", SOUND_BGM, g_fVolume);
	CSoundMgr::Get_Instance()->PlaySound(L"sakuraburst ambience & foley ICY PEAKK-sharedassets10.assets-125.wav", SOUND_BGM_BG, g_fBG_Volume);

	//CTileMgr::Get_Instance()->Load_Data();
	m_pEndBotton = CAbstractFactory<EndButton>::Create(1120, 700.f, 0.f);
	m_pEndBotton->Set_FrameKey(L"EndButton");
	m_pEndEntry= CAbstractFactory<EndEntry>::Create(800, 600.f, 0.f);
	m_pEndEntry->Set_FrameKey(L"EndEntry");
}

void BossField::Update()
{
	m_pEndBotton->Update();
	m_pEndEntry->Update();
	CPlayer::Get_Instance()->Update();

	//CreateSnow();
	CObjMgr::Get_Instance()->Update();
	//CTileMgr::Get_Instance()->Update();
}

void BossField::Late_Update()
{
	//CheckWindowOver();
	CPlayer::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	if (CPlayer::Get_Instance()->Get_Dead()|| !CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))
	{
		m_pEndBotton->Late_Update();
		//m_pEndEntry->Late_Update();
	}
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

	CPlayer::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	if (CPlayer::Get_Instance()->Get_Dead())
	{
		//TCHAR	szBuff[32] = L"Test";
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Fail_Ending"), 0, 0, 1280, 800);
	
		m_pEndBotton->Render(hDC);
		m_pEndEntry->Render(hDC);
		
	}
	if (!CObjMgr::Get_Instance()->Get_ObjList(BOSS_MONSTER))
	{
		iFrameCheck++;
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		if (!CObjMgr::Get_Instance()->Get_ObjList(ITEM_BOX)) {

			if (iFrameCheck>400) {
				g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Success_Ending"), 0, 0, 1280, 800);
				m_pEndBotton->Render(hDC);
				m_pEndEntry->Render(hDC);
				
			}
		
		}
		
	}
	

	BossMapLineMgr::Get_Instance()->Render(hDC);
}

void BossField::Release()
{

	Safe_Delete(m_pEndBotton);
	Safe_Delete(m_pEndEntry);
	CObjMgr::Get_Instance()->Delete_ID(BOSS_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(SUB_MONSTER_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(BOSS_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(MOSTER_UI);
	CObjMgr::Get_Instance()->Delete_ID(COLLISIONBOX);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM_BG);

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
