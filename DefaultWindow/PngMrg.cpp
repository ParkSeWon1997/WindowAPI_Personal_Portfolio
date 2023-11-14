#include "stdafx.h"
#include "PngMrg.h"
#include"MyPng.h"

PngMrg* PngMrg::m_pInstance = nullptr;


PngMrg::PngMrg()
{
}

PngMrg::~PngMrg()
{
	Release();
}

void PngMrg::Insert_Png(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		MyPng* pBmp = new MyPng;

		pBmp->Save_Png(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}


}




void PngMrg::Release()
{

	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}

Image* PngMrg::Get_Image(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_Image();

}


