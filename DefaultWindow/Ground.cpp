#include "stdafx.h"
#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Initialize()
{



	m_eRender = GAMEOBJECT;
}

int Ground::Update()
{

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void Ground::Late_Update()
{
}

void Ground::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left ,
		m_tRect.top ,
		m_tRect.right ,
		m_tRect.bottom );

}

void Ground::Release()
{
}
