#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "BlockMgr.h"
#include "CollilsionMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	MBITMAP->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	MOBJ->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(800, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(700, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(600, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create(1000, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create(1300, 150));
	BLOCK->Load_File(L"../Data/Blocks.dat");

	
}

void CStage1::Update()
{
	MOBJ->Update();
	BLOCK->Update();

		
}

void CStage1::Late_Update()
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

void CStage1::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(92, 148, 252));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, 0, 0, 800, 600);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	

	HDC hMemDC = MBITMAP->Find_Img(CLOUD1);
	int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	for (int i = 0; i < 20; i++)
	{
		GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
			i*500 + iScrollX, // 복사 받을 텍스처 위치 좌표 X
			100+i*10, // 복사 받을 텍스처 위치 좌표 Y
			96, // 텍스처 가로 사이즈
			55, // 텍스처 세로 사이즈
			hMemDC,   // 복사할 DC
			0,   // 비트맵 출력 좌표 X
			0,   // 비트맵 출력 좌표 Y
			96, // 복사할 비트맵 텍스처 가로 사이즈
			55, // 복사할 비트맵 텍스처 세로 사이즈
			RGB(1, 1, 1)); // 제거할 픽셀 색상
	}

	hMemDC = MBITMAP->Find_Img(MOUNTAIN2);
	GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
		200 + iScrollX, // 복사 받을 텍스처 위치 좌표 X
		500, // 복사 받을 텍스처 위치 좌표 Y
		160, // 텍스처 가로 사이즈
		69, // 텍스처 세로 사이즈
		hMemDC,   // 복사할 DC
		0,   // 비트맵 출력 좌표 X
		0,   // 비트맵 출력 좌표 Y
		160, // 복사할 비트맵 텍스처 가로 사이즈
		69, // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상

	hMemDC = MBITMAP->Find_Img(GRASS2);
	GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
		600 + iScrollX, // 복사 받을 텍스처 위치 좌표 X
		520, // 복사 받을 텍스처 위치 좌표 Y
		131, // 텍스처 가로 사이즈
		32, // 텍스처 세로 사이즈
		hMemDC,   // 복사할 DC
		0,   // 비트맵 출력 좌표 X
		0,   // 비트맵 출력 좌표 Y
		131, // 복사할 비트맵 텍스처 가로 사이즈
		32, // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상

	hMemDC = MBITMAP->Find_Img(GOALFLAG);
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
				MSCENE->Scene_Change(SC_STAGE2);
			}
		}
	}

	
	MOBJ->Render(hDC);
	BLOCK->Render(hDC);
}

void CStage1::Release()
{
	MOBJ->DeleteObject(PLAYER);
	MOBJ->Release();
	MOBJ->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
}
