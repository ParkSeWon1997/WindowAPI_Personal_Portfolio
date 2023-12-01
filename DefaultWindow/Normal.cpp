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
#include "EndButton.h"
#include "HpPotion.h"


static float g_fVolume = 0.7f;
Normal::Normal():m_pEndBotton(nullptr)
{
}

Normal::~Normal()
{
	Release();

	
}

void Normal::Initialize()
{
	CPlayer::Get_Instance()->Set_Pos(50.f, 285.f);
	dynamic_cast<CPlayer*>(CPlayer::Get_Instance())->Set_SC_ID(SCENEID::SC_NORMAL);
	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(15.f,214.f,90));
	CObjMgr::Get_Instance()->Add_Object(STAGE_ENTRY, CAbstractFactory<StageEntry>::Create(934.f, 134.f, 0));
	//아이템
	//CObjMgr::Get_Instance()->Add_Object(ITEM_HP, CAbstractFactory<HpPotion>::Create(333.f, 333.f, 0));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create(100.f, 200.f, 0));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create(600.f, 300.f, 0));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create(800.f, 500.f, 0));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create(800.f, 500.f, 0));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<DefalutMonster>::Create(800.f, 500.f, 0));

	CSoundMgr::Get_Instance()->PlaySound(L"2.IceField-sharedassets10.assets-124.wav", SOUND_BGM, g_fVolume);

	EasyMapLindeMgr::Get_Instance()->Initialize();
	m_pEndBotton = CAbstractFactory<EndButton>::Create(1116, 700.f, 0.f);
	m_pEndBotton->Set_FrameKey(L"EndButton");
	//CTileMgr::Get_Instance()->Load_Data2();
}

void Normal::Update()
{
	m_pEndBotton->Update();
	//if (CKeyMgr::Get_Instance()->Key_Pressing('0'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	//}
	CPlayer::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void Normal::Late_Update()
{

	if (!CObjMgr::Get_Instance()->Get_ObjList(MONSTER,new DefalutMonster)) {
		m_iOpenCheckCount++;
		if (m_iOpenCheckCount>100) {
			m_bOpenDoor = true;
			for (auto& iter : CObjMgr::Get_Instance()->Get_ObjListProperty(STAGE_ENTRY))
			{
				dynamic_cast<StageEntry*>(iter)->SetOpenCondition(m_bOpenDoor);
			}
			//dynamic_cast<StageEntry*>(CObjMgr::Get_Instance()->Get_ObjListProperty(STAGE_ENTRY))->SetOpenCondition(m_bOpenDoor);
			m_bOpenDoor = false;
			m_iOpenCheckCount = -1000;
			//dynamic_cast<StageEntry*>(CObjMgr::Get_Instance()->Get_ObjList(STAGE_ENTRY))->SetOpenCondition(true);
	
	
		}
	}
	else
	{
		m_iCloseCheckCount++;
		if (m_iCloseCheckCount>50)
		{
			for (auto& iter : CObjMgr::Get_Instance()->Get_ObjListProperty(STAGE_ENTRY))
			{
				dynamic_cast<StageEntry*>(iter)->SetcloseCondition(false);
			}
		}
	}
	CPlayer::Get_Instance()->Late_Update();

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	if (CPlayer::Get_Instance()->Get_Dead())
	{
		m_pEndBotton->Late_Update();
	}
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


	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Render(hDC);
	if (CPlayer::Get_Instance()->Get_Dead())
	{
		g.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Fail_Ending"), 0, 0, 1280, 800);
		m_pEndBotton->Render(hDC);

	}
	EasyMapLindeMgr::Get_Instance()->Render(hDC);
}

void Normal::Release()
{
	CTileMgr::Destroy_Instance();
	Safe_Delete(m_pEndBotton);
	CObjMgr::Get_Instance()->Delete_ID(BOSS_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(ITEM_HP);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(SUB_MONSTER_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(BOSS_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(MOSTER_UI);
	CObjMgr::Get_Instance()->Delete_ID(COLLISIONBOX);
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(STAGE_ENTRY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
