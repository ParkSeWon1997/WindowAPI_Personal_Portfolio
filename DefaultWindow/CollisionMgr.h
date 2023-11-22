#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> Dst, list<CObj*> Src);
	// 추가
	static bool CollisionRect_to_Rect(CObj* _tmp, CObj* _Src);
	static bool CollisionPoint_to_Point(CObj* _tmp, CObj* _Src);

	//첫 번쨰 인자: 데미지를 받을 Obj, 2번 째 인자: 데미지를 줄 Obj 
	static void DoDamageObj_to_Obj(list<CObj*> Dst, list<CObj*> Src);



	static void	Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList);
	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);

	static void	Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

};


