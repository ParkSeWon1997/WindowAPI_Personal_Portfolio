#include "stdafx.h"
#include "MyPng.h"


MyPng::MyPng()
{

}
MyPng::~MyPng()
{
	Release();
}



void MyPng::Save_Png(const TCHAR* pFilePath)
{

	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개변수와 호환되는 dc를 생성

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);


    m_pImage =Image::FromFile(pFilePath);



}

void MyPng::Release(void)
{

	DeleteDC(m_hMemDC);

}