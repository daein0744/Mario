#pragma once

#include "Obj.h"
#include "Block.h"
#include "Define.h"
#include "Player.h"
#include "Coin.h"
#include "Flower.h"
#include "Mushroom.h"

class CCollilsionMgr
{
public:
	CCollilsionMgr();
	~CCollilsionMgr();

public:
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static CBlock* Collision_Block(CObj* _obj, list<CBlock*>* _block);

	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static	bool Check_Sphere(CObj* pDest, CObj* pSrc);
	static	bool Check_Rect(CObj* pDest, CObj* pSrc, float* pX, float* pY);

	static void Collision_BlockEx(list<CBlock*> _Dest, list<CObj*> _Src);
	static bool Check_BlockRect(CBlock * pDest, CObj * pSrc, float * pX, float * pY);
private:
	int iRandValue = 0;
};

