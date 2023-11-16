#include "stdafx.h"
#include "Entry.h"
#include"PngMrg.h"
Entry::Entry()
{

}

Entry::~Entry()
{
    Release();
}

void Entry::Initialize()
{
    m_tInfo = { 50.f,200.f,240.f,170.f };
    PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World//Entry/DungeonEntry.png", L"Dungeon_Entry");


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
}

void Entry::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right , m_tRect.bottom );
    Graphics g(hDC);
    g.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pStateKey),
        Rect((m_tInfo.fX - m_tInfo.fCX * 0.5) , (m_tInfo.fY - m_tInfo.fCY * 0.5), m_tInfo.fCX, m_tInfo.fCY), m_tInfo.fCX * m_tFrame.iFrameStart, m_tInfo.fCY * m_tFrame.iMotion, 240, 170, UnitPixel);



}

void Entry::Release()
{
}


