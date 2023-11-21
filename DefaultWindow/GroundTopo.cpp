#include "stdafx.h"
#include "GroundTopo.h"

GroundTopo::GroundTopo()
{
}

GroundTopo::~GroundTopo()
{
}

void GroundTopo::Initialize()
{
    m_eRender = GAMEOBJECT;
}

int GroundTopo::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void GroundTopo::Late_Update()
{
}

void GroundTopo::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void GroundTopo::Release()
{
}
