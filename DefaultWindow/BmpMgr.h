#pragma once

#include "MyBmp.h"
#include "Define.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release();

public:
	static	CBmpMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr*	m_pInstance;

	map<const TCHAR*, CMyBmp*>		m_mapBit;
};

