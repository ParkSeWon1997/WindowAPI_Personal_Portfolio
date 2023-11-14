#pragma once
#include "Define.h"

class MyPng;


class PngMrg
{
private:
	PngMrg();
	~PngMrg();

public:
	void		Insert_Png(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Release();
	Image*		Get_Image(const TCHAR* pImgKey);
	


public:
	static PngMrg* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new PngMrg;
		}

		return m_pInstance;

	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	static PngMrg* m_pInstance;
	map<const TCHAR*, MyPng*>		m_mapBit;
	

};

