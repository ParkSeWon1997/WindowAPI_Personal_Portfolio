#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include"Player.h"
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


//m_ObjList의 eID값을 가지는 객체를 2번째 인자값과 비교해서 찾은 객체를 넘겨줌 단, 인자값은 m_ObjList의 타입과 상속관계에 있어야 하고 m_ObjList의 타입 클래스에 가상 함수가 있어야 함
CObj* CObjMgr::Get_ObjList(OBJID eID, CObj* _pCOjType)
{
	if (m_ObjList[eID].empty() || _pCOjType == nullptr)
	{
		delete _pCOjType;
		return nullptr;
	}
	for (CObj* pObj : m_ObjList[eID])
	{
		if (typeid(*pObj) == typeid(*_pCOjType))
		{
			delete _pCOjType;
			return pObj;
		}
	}

	delete _pCOjType;
	return nullptr;
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
	CCollisionMgr::Collision_Sphere(m_ObjList[COLLISIONBOX], m_ObjList[SUB_MONSTER_BULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[BULLET], m_ObjList[SUB_MONSTER_BULLET]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[BULLET], m_ObjList[BOSS_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(CPlayer::Get_Instance(), m_ObjList[SUB_MONSTER_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(CPlayer::Get_Instance(), m_ObjList[BOSS_BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[BOSS_MONSTER], m_ObjList[BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[BOSS_MONSTER], m_ObjList[COLLISIONBOX]);
	//CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[BOSS_MONSTER], m_ObjList[BULLET]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[MONSTER], m_ObjList[COLLISIONBOX]);
	CCollisionMgr::DoDamageObj_to_Obj(m_ObjList[MONSTER], m_ObjList[BULLET]);




	

	//CCollisionMgr::Collision_RectEx(m_ObjList[MONSTER], m_ObjList[BULLET]);
}

void CObjMgr::Render(HDC hDC)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hDC);
		}
	}



	//for (size_t i = 0; i < RENDER_END; ++i)
	//{
	//	m_RenderSort[i].sort([](CObj* pDst, CObj* pSrc)->bool {
	//	
	//		return pDst->Get_Info().fY < pSrc->Get_Info().fY;
	//	});
	//
	//	for (auto& iter : m_RenderSort[i])
	//	{
	//		iter->Render(hDC);
	//	}
	//
	//	m_RenderSort[i].clear();
	//}
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

void CObjMgr::Delete_ID(OBJID eID, CObj* _pObjType)
{
	if (m_ObjList[eID].empty() || _pObjType == nullptr)
	{
		delete _pObjType;
		return;
	}
	for (auto& iter = m_ObjList[eID].begin(); iter != m_ObjList[eID].end();)
	{
		if (typeid(**iter) == typeid(*_pObjType))
		{
			delete _pObjType;
			Safe_Delete(*iter);
			iter = m_ObjList[eID].erase(iter);
		}
		else
			++iter;
	}
}
