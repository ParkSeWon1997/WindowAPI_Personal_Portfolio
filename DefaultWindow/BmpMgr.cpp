#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*	CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CMyBmp*		pBmp = new CMyBmp;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}
}

HDC CBmpMgr::Find_Img(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;
	
	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
