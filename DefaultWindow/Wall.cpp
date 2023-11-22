#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
	m_eRender = GAMEOBJECT;
}

int Wall::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Wall::Late_Update()
{
}

void Wall::Render(HDC hDC)
{
	Rectangle(hDC,
				m_tRect.left ,
				m_tRect.top ,
				m_tRect.right ,
				m_tRect.bottom );
}

void Wall::Release()
{
}
