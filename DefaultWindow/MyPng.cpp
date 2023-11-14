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

    m_pImage =Image::FromFile(pFilePath);



}

void MyPng::Release(void)
{



}