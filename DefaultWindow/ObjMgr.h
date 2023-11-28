#pragma once

#include "Obj.h"
#include"Player.h"

class CObjMgr
{
public:
	
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* Get_Player() { return CPlayer::Get_Instance(); }//m_ObjList[PLAYER].front(); }
	CObj* Get_ObjList(OBJID eID);
	list<CObj*> Get_ObjListProperty(OBJID eID) { return m_ObjList[eID]; }
	CObj*	Get_Target(OBJID eID, CObj* pObj);
public:
	void	Add_Object(OBJID eID, CObj* pObj);
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Delete_ID(OBJID eID);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderSort[RENDER_END];

	static CObjMgr*		m_pInstance;

public:
	static	CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
};

