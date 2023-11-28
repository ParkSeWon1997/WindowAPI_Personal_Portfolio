#include "stdafx.h"
#include "GameEnd.h"
#include "ObjMgr.h"

GameEnd::GameEnd()
{
}

GameEnd::~GameEnd()
{
	Release();
}

void GameEnd::Initialize()
{
}

void GameEnd::Update()
{
}

void GameEnd::Late_Update()
{
}

void GameEnd::Render(HDC hDC)
{
}

void GameEnd::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
}
