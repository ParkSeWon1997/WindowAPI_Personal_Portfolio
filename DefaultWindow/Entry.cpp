#include "stdafx.h"
#include "Entry.h"
#include"PngMrg.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include"CollisionMgr.h"
#include "ObjMgr.h"
Entry::Entry()
{

}

Entry::~Entry()
{
    Release();
}

void Entry::Initialize()
{

   // m_tInfo.fCX = 240.f;
   // m_tInfo.fCY = 170.f;
    m_tInfo = { WINCX*0.5,WINCY-200,240.f,170.f };
   


    m_pStateKey = L"Dungeon_Entry";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;

	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

    m_eRender = GAMEOBJECT;
}

int Entry::Update()
{



    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void Entry::Late_Update()
{
    Move_Frame();
   
    if (CCollisionMgr::CollisionRect_to_Rect(CObjMgr::Get_Instance()->Get_Player(), this))
    {
        CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);

    }

}

void Entry::Render(HDC hDC)
{
    //Rectangle(hDC, m_tRect.left, m_tRect.top , m_tRect.right , m_tRect.bottom );


    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    Graphics g(hDC);
    g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
        Rect((m_tInfo.fX - m_tInfo.fCX * 0.5)+ iScrollX,
            (m_tInfo.fY - m_tInfo.fCY * 0.5)+ iScrollY,
            m_tInfo.fCX, m_tInfo.fCY),
        m_tInfo.fCX * m_tFrame.iFrameStart,
        m_tInfo.fCY * m_tFrame.iMotion,
        240, 170, UnitPixel);



}

void Entry::Release()
{
    
}


