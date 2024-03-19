#include "stdafx.h"
#include "Stage2.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "CollilsionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	BLOCK->Load_File(L"../Data/Blocks2.dat");
	MOBJ->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(400, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(500, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(600, 150));

	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create(1400, 150));

	MSCROLL->ScrollClear();
}

void CStage2::Update()
{
	MOBJ->Update();
	BLOCK->Update();

	if (MKEY->Key_Down('L'))
		MSCENE->Scene_Change(SC_STAGE3);
}

void CStage2::Late_Update()
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

void CStage2::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, 0, 0, 800, 600);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	HDC hMemDC = MBITMAP->Find_Img(GOALFLAG);
	GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
		1500 + iScrollX, // 복사 받을 텍스처 위치 좌표 X
		210, // 복사 받을 텍스처 위치 좌표 Y
		48, // 텍스처 가로 사이즈
		334, // 텍스처 세로 사이즈
		hMemDC,   // 복사할 DC
		0,   // 비트맵 출력 좌표 X
		0,   // 비트맵 출력 좌표 Y
		48, // 복사할 비트맵 텍스처 가로 사이즈
		334, // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상

	list<CObj*>* playerlist = MOBJ->GetObjList(PLAYER);
	if (playerlist)
	{
		CObj* player = playerlist->front();
		if (player)
		{
			cout << player->Get_Info().fX << " " << 1500 + iScrollX << endl;
			if (player->Get_Info().fX >= 1500)
			{
				MSCENE->Scene_Change(SC_STAGE3);
			}
		}
	}

	MOBJ->Render(hDC);
	BLOCK->Render(hDC);
}

void CStage2::Release()
{
	MOBJ->DeleteObject(PLAYER);
	MOBJ->Release();
	MOBJ->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
}
