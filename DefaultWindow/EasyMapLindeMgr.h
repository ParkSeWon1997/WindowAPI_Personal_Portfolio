#pragma once
#include"Line.h"
class EasyMapLindeMgr
{
private:
	EasyMapLindeMgr();
	~EasyMapLindeMgr();

public:
	enum MAPLINE { VILLAGE, EASY, NORMAL, BOSS, END };


	void			Initialize(void);
	void			Render(HDC hDC);
	void			Release();

	bool			Collision_Line(float* pHeight, float& _fX, float _fCY);
	bool			DropItemCollision_Line(float* pHeight, float& _fX, float _fY, float _fCY);
	
	void			Load_Line();

	list<CLine*>* Get_LineList() { return &m_LineList; }
	void			SelectMapLine(MAPLINE _ID);

public:
	static	EasyMapLindeMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new EasyMapLindeMgr;

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
	static EasyMapLindeMgr* m_pInstance;




	DWORD					dwFrameTime = GetTickCount();


};

