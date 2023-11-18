#include "stdafx.h"
#include "Village.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Entry.h"
#include "AbstractFactory.h"
#include "AbstractFactory.h"
#include "LineMgr.h"

Village::Village()
{


}

Village::~Village()
{
}

void Village::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CPlayer::Get_Instance());
	CObjMgr::Get_Instance()->Add_Object(ENTRY, CAbstractFactory<Entry>::Create());
	CLineMgr::Get_Instance()->Initialize();
}

void Village::Update()
{
}

void Village::Late_Update()
{
}

void Village::Render(HDC hDC)
{




	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void Village::Release()
{
}
