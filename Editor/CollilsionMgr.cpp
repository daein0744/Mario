#include "stdafx.h"
#include "CollilsionMgr.h"


CCollilsionMgr::CCollilsionMgr()
{
}


CCollilsionMgr::~CCollilsionMgr()
{
}

void CCollilsionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			RECT drct = Dest->Get_Rect();
			RECT srct = Src->Get_Rect();

			if (IntersectRect(&rc, &drct, &srct))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}


}

void CCollilsionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	float	fX = 0.f, fY = 0.f;


	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{

			if (Check_Rect(Dest, Src, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					// �� �浹
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Dest->Set_Y(-fY);
					}
					else // �� �浹
					{
						Dest->Set_Y(fY);
					}

				}
				else // �¿� �浹
				{
					// �� �浹
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						Dest->Set_X(-fX);
					}
					else // �� �浹
					{
						Dest->Set_X(fX);
					}
				}

			}
		}
	}
}

void CCollilsionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollilsionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float		fWidth =  fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDistance;
}

bool CCollilsionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float * pX, float * pY)
{
	float	fX = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float	fY = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float	fRadiusX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float	fRadiusY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;

		return true;
	}

	return false;
}
