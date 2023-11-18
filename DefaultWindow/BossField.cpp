#include "stdafx.h"
#include "BossField.h"
#include"StageEntry.h"
#include"DefalutMonster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossMonster.h"
#include "LineMgr.h"

BossField::BossField()
{
}

BossField::~BossField()
{
	Release();
}

void BossField::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<BossMonster>::Create());
	CLineMgr::Get_Instance()->Initialize();
}

void BossField::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void BossField::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void BossField::Render(HDC hDC)
{
	Graphics g(hDC);
}

void BossField::Release()
{
}
