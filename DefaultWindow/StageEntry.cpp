#include "stdafx.h"
#include "StageEntry.h"
#include"PngMrg.h"
#include "KeyMgr.h"
#include"SoundMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"




static float  g_fVolume = 1.0f;


StageEntry::StageEntry():m_bOpenCondition(false), IsOpenCondition(false)
{
}

StageEntry::StageEntry(float _X, float _Y)
{
	m_tInfo.fX = _X;
	m_tInfo.fY = _Y;
}

StageEntry::~StageEntry()
{
	Release();
}

void StageEntry::Initialize()
{

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 132.f;

	m_pStateKey = L"World_Stage_Entry";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 1;

	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_eRender = GAMEOBJECT;
}

int StageEntry::Update()
{

	Motion_Change();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void StageEntry::Late_Update()
{
	Move_Frame();
	EntryOpen();
	EntryClose();
	if (IsOpenCondition) {
		if (CCollisionMgr::Check_Sphere(CPlayer::Get_Instance(), this))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);

		}
	}
	
	//if (CCollisionMgr::CollisionRect_to_Rect(CObjMgr::Get_Instance()->Get_Player(), this))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	//
	//}


}

void StageEntry::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Graphics g(hDC);
	g.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	g.RotateTransform(90);
	g.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
		Rect((m_tInfo.fX - 132.f * 0.5), 
			(m_tInfo.fY - 40.f * 0.5),
				132.f, 40.f),
				132.f * m_tFrame.iFrameStart, 
				40.f * m_tFrame.iMotion,
				132, 40, UnitPixel);


}

void StageEntry::Release()
{
}

void StageEntry::EntryOpen()
{
	if (m_bOpenCondition)
	{
		m_eCurState = STAGESTATE::OPEN;
		if (m_tFrame.iFrameStart == 7) {
			m_eCurState = END;
			m_bOpenCondition = false;
		}
	}


	
}

void StageEntry::EntryClose()
{
	if (m_bCloseCondition)
	{
		//CPlayer::Get_Instance().SEt
		m_eCurState = STAGESTATE::CLOSE;
		if (m_tFrame.iFrameStart == 7) {
			m_eCurState = IDLE;
			m_bCloseCondition = false;
		}


	}
}

void StageEntry::Motion_Change()
{

	if (m_ePreState != m_eCurState)
	{

		switch (m_eCurState)
		{

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case OPEN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 2;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			break;

		case CLOSE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case END:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}


}
