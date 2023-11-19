#include "stdafx.h"
#include "StageEntry.h"
#include"PngMrg.h"
#include "KeyMgr.h"
#include"SoundMgr.h"




static float  g_fVolume = 1.0f;


StageEntry::StageEntry()
{
}

StageEntry::~StageEntry()
{
	Release();
}

void StageEntry::Initialize()
{

	m_tInfo = { 100.f,300.f,132.f,40.f };


	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/Stele.png", L"World_Stage_Entry");
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
	Move_Frame();








	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void StageEntry::Late_Update()
{
	Motion_Change();


}

void StageEntry::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Graphics g(hDC);
	g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
		Rect((m_tInfo.fX - m_tInfo.fCX * 0.5), (m_tInfo.fY - m_tInfo.fCY * 0.5), m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 132, 40, UnitPixel);


}

void StageEntry::Release()
{
}

void StageEntry::EntryOpen()
{



	
}

void StageEntry::EntryClose()
{
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
