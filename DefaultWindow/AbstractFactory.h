#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj*		Create(float _fX, float _fY, float _fAngle, float _fSpeed)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Speed(_fSpeed);

		return pObj;
	}

	static CObj*		Create(CObj* pTarget)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(pTarget);

		return pObj;
	}

public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

