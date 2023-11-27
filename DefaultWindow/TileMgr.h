#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();


	/*void		Picking(POINT _ptMouse, int _iDrawID, int _iOption);*/
	void		Picking(float _x, float _y, int _iDrawID, int _iOption);
	void		Save_Data();
	void		Save_Data2();
	void		Save_Data3();
	void		Save_Data4();
	void		Save_Data5();
	void		Load_Data();
	void		Load_Data2();
	void		Load_Data3();
	void		Load_Data4();
	void		Load_Data5();
public:
	static	CTileMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;

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
	static CTileMgr*	m_pInstance;

	vector<CObj*>		m_vecTile;


};

