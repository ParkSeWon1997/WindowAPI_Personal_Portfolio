#include "stdafx.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개변수와 호환되는 dc를 생성

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);


	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// 프로그램 인스턴스 핸들(이미지는 프로그램에서 얻어오는 것이 아니기 때문에 NULL)
									pFilePath,	// 파일의 경로 전달
									IMAGE_BITMAP,  // 어떤 타입을 읽어들일지 전달
									0,		// 가로 크기
									0,		// 세로 크기
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);
									// LR_LOADFROMFILE : 파일로 부터 이미지 불러오기
									// LR_CREATEDIBSECTION : 읽이온 파일을 DIB 형태로 변환

	// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 갖고 있던 오브젝트를 반환하는 함수

	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}


void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
