#include "stdafx.h"
#include "CollisionMgr.h"
#include"Player.h"
#include"Monster.h"
#include "SoundMgr.h"

static float g_fVolume = 1.0f;
CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
	// 1인자 : 결과 값을 저장할 렉트의 주소
	// 2, 3인자 : 충돌을 수행할 렉트의 주소

	RECT	rc{};

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
			{
				DstList->Set_Dead();
				SrcList->Set_Dead();
			}
		}
	}


}

bool CCollisionMgr::CollisionRect_to_Rect(CObj* _tmp, CObj* _Src)
{
	RECT	rc{};

	return IntersectRect(&rc, &_tmp->Get_Rect(), &_Src->Get_Rect());
}

bool CCollisionMgr::CollisionPoint_to_Point(CObj* _tmp, CObj* _Src)
{
	if (_tmp->Get_Info().fX == _Src->Get_Info().fX && _tmp->Get_Info().fY == _Src->Get_Info().fY) {
		return true;
	}
	return false;
}


//첫 번쨰 인자: 데미지를 받을 Obj, 2번 째 인자: 데미지를 줄 Obj 
void CCollisionMgr::DoDamageObj_to_Obj(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				if (DstList->Get_Dead() == false)
				{

					DstList->TakeDamage(SrcList->GetDamage());
					DstList->Set_IsHit(true);
					CSoundMgr::Get_Instance()->PlaySound(L"Hit_Player-resources.assets-1729.wav", SOUND_HIT, g_fVolume);
					if (DstList->Get_HP() <= 0)
					{
						DstList->Set_Dead();
					}
					SrcList->Set_Dead();
				}
			}
		}
	}
}

void CCollisionMgr::DoDamageObj_to_Obj(CObj* _Player, list<CObj*> Src)
{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(_Player, SrcList))
			{
				if (_Player->Get_Dead() == false)
				{

					_Player->TakeDamage(SrcList->GetDamage());
					_Player->Set_IsHit(true);
					dynamic_cast<CPlayer*>(_Player)->Knock_back(SrcList->Get_Info().fX);
					CSoundMgr::Get_Instance()->PlaySound(L"Hit_Player-resources.assets-1729.wav", SOUND_HIT, g_fVolume);
					if (_Player->Get_HP() <= 0)
					{
						_Player->Set_Dead();
					}
					SrcList->Set_Dead();
				}
			}
		}
	
}

void CCollisionMgr::Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				if (fX > fY)	// 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Dst->Set_PosY(-fY);

					// 하 충돌
					else
						Dst->Set_PosY(fY);

				}
				else			// 좌우 충돌	
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Dst->Set_PosX(-fX);

					// 우 충돌
					else
						Dst->Set_PosX(fX);
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc)
{
	float		fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				DstList->Set_Dead();
				SrcList->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float		fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDistance;
}
