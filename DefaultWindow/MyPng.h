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


private:

	Image*		m_pImage;

};

