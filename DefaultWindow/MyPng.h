#pragma once
#include "Define.h"

class MyPng
{
public:
	MyPng();
	~MyPng();

public:
	Image*		Get_Image() { return m_pImage; }
	void		Save_Png(const TCHAR* pFilePath);
	void		Release(void);
	HDC			Get_MemDC() { return m_hMemDC; }

private:
	HDC			m_hMemDC;
	Image*		m_pImage;

};

