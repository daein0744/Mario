#include "stdafx.h"
#include "CollilsionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

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
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}


}

void CCollilsionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	float   fX = 0.f, fY = 0.f;

	if (_Dest.size() == 0 || _Src.size() == 0)
		return;


	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			// dest : 플레이어 src : 블록
			if (Check_Rect(Dest, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Dest->Hit_Down(Src);
						Src->Hit_Up(Dest);
					}
					else
					{
						Src->Hit_Down(Dest);
						Dest->Hit_Up(Src);
					}

				}
				else // 좌우 충돌
				{
					Dest->Hit_LeftRight(Src);
					Src->Hit_LeftRight(Dest);

					 //좌 충돌
					//if (Dest->Get_Info().fX < Src->Get_Info().fX)
					//{
					//   Dest->Hit_Right(Src); 
					//   Src->Hit_Left(Dest); 
					//}
					//else // 우 충돌
					//{
					//   Dest->Hit_Right(Src); 
					//   Src->Hit_Left(Dest);  
					//}
				}

			}
		}
	}
}

CBlock* CCollilsionMgr::Collision_Block(CObj * _obj, list<CBlock*>* _block)
{
	float	fX = 0.f, fY = 0.f;
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for (auto& Block : _block[i])
		{
			if (Check_Rect(_obj, Block, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (_obj->Get_Info().fY < Block->Get_Info().fY)
					{
						_obj->Set_Y(-fY);
						return Block;
					}
					else // 하 충돌
					{
						//_obj->Set_Y(fY);
						
					}

				}
				else // 좌우 충돌
				{
					// 좌 충돌
					if (_obj->Get_Info().fX < Block->Get_Info().fX)
					{
						_obj->Set_X(-fX);
						return Block;
					}
					else // 우 충돌
					{
						_obj->Set_X(fX);
						return Block;
					}
				}

			}
		}
	}
	return nullptr;
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


void CCollilsionMgr::Collision_BlockEx(list<CBlock*> _Dest, list<CObj*> _Src)
{
	float   fX = 0.f, fY = 0.f;

	if (_Dest.size() == 0 || _Src.size() == 0)
		return;

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_BlockRect(Dest, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Dest->HitBlock_Up(Src);
						Src->HitBlock_Down(Dest);

					}

					// 하 충돌
					else
					{
						cout << Src->Get_Info().fY << "\t" << Dest->Get_Info().fY << endl;
						Src->HitBlock_Up(Dest);
						Dest->HitBlock_Down(Src);
					}
				}
				else
				{
					//좌우충돌
					{
						Dest->HitBlock_LeftRight(Src);
						Src->HitBlock_LeftRight(Dest);
					}
				}
			}
		}
	}
}

bool CCollilsionMgr::Check_BlockRect(CBlock * pDest, CObj * pSrc, float * pX, float * pY)
{
	float   fX = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float   fY = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float   fRadiusX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float   fRadiusY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;

		return true;
	}

	return false;
}