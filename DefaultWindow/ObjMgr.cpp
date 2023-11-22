#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_ObjList(OBJID eID)
{
	if (m_ObjList[eID].empty())
		return nullptr;
	


	 return m_ObjList[eID].front(); 
}

CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if(iter->Get_Dead())
			continue;

		float	fWidth = pObj->Get_Info().fX - iter->Get_Info().fX;
		float	fHeight = pObj->Get_Info().fY - iter->Get_Info().fY;

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);


		if (!pTarget || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update()
{
	int iResult = 0;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return iResult;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eID = iter->Get_RenderID();
			m_RenderSort[eID].push_back(iter);
		}
	}

	//CCollisionMgr::Collision_RectEx(m_ObjList[MONSTER], m_ObjList[PLAYER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[MONSTER], m_ObjList[BULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[BULLET], m_ObjList[SUB_MONSTER_BULLET]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[BULLET], m_ObjList[BOSS_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[PLAYER], m_ObjList[SUB_MONSTER_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[PLAYER], m_ObjList[BOSS_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[BOSS_MONSTER], m_ObjList[BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[MONSTER], m_ObjList[BULLET]);

	//CCollisionMgr::Collision_RectEx(m_ObjList[MONSTER], m_ObjList[BULLET]);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort([](CObj* pDst, CObj* pSrc)->bool {
		
			return pDst->Get_Info().fY < pSrc->Get_Info().fY;
		});

		for (auto& iter : m_RenderSort[i])
		{
			iter->Render(hDC);
		}

		m_RenderSort[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
