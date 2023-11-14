#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> Dst, list<CObj*> Src);

	static void	Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList);
	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);

	static void	Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

};


