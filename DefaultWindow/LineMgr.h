#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	enum MAPLINE {VILLAGE,EASY,NORMAL,BOSS,END};


	void			Initialize(void);
	void			Render(HDC hDC);
	void			Release();

	bool			Collision_Line(float* pHeight, float& _fX, float _fY,float _fCY);
	bool			DropItemCollision_Line(float* pHeight, float& _fX, float _fY,float _fCY);
	bool			IsCollision_Line_to_item(float pHeight, float _fX, float _fY);
	void			Load_Line();

	list<CLine*>*	Get_LineList() { return &m_LineList; }
	void			SelectMapLine(MAPLINE _ID);

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




	DWORD					dwFrameTime = GetTickCount();
};

