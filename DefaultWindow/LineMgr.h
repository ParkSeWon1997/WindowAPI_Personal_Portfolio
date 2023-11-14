#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void			Initialize(void);
	void			Render(HDC hDC);
	void			Release();

	bool			Collision_Line(float* pHeight, float& _fX);
	void			Load_Line();

public:
	static	CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

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
	list<CLine*>		m_LineList;	
	static CLineMgr*	m_pInstance;
};

