#include "stdafx.h"
#include "Stage4.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "CollilsionMgr.h"
#include "BitmapMgr.h"

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
	BLOCK->Load_File(L"../Data/Blocks4.dat");
	MOBJ->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	MSCROLL->ScrollClear();
}

void CStage4::Update()
{
	MOBJ->Update();
	BLOCK->Update();
}

void CStage4::Late_Update()
{
	MOBJ->Late_Update();
	BLOCK->Late_Update();
	CCollilsionMgr::Collision_RectEx(*MOBJ->GetObjList(PLAYER), *MOBJ->GetObjList(MONSTER));
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for (size_t j = 0; j < OBJ_END; ++j)
		{
			CCollilsionMgr::Collision_BlockEx(*BLOCK->GetBlockList((BLOCKID)i), *MOBJ->GetObjList((OBJID)j));
		}
	}
}

void CStage4::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(77, 77, 77));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, 0, 0, 800, 600);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	MOBJ->Render(hDC);
	BLOCK->Render(hDC);
}

void CStage4::Release()
{
	MOBJ->DeleteObject(PLAYER);
	MOBJ->Release();
	MOBJ->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
}
