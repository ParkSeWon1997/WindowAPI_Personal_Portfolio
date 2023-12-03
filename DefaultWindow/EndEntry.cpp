#include "stdafx.h"
#include "EndEntry.h"
#include "PngMrg.h"

EndEntry::EndEntry()
{
}

EndEntry::~EndEntry()
{
}

void EndEntry::Initialize()
{
    m_tInfo.fCX = 508.f;
    m_tInfo.fCY = 340.f;
    // m_tInfo = { 500.f,WINCY-200,240.f,170.f };



    m_pStateKey = L"EndEntry";
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 6;
    m_tFrame.iMotion = 0;

    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount();
    m_eRender = UI;
}

int EndEntry::Update()
{
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void EndEntry::Late_Update()
{
    
}

void EndEntry::Render(HDC hDC)
{
    Graphics g(hDC);
    Move_Frame();
    g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
        Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) ,
            (m_tInfo.fY - m_tInfo.fCY * 0.5) ,
            m_tInfo.fCX, m_tInfo.fCY),
        m_tInfo.fCX * m_tFrame.iFrameStart,
        m_tInfo.fCY * m_tFrame.iMotion,
        m_tInfo.fCX, m_tInfo.fCY, UnitPixel);
}

void EndEntry::Release()
{
}
