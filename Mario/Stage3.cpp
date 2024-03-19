#include "stdafx.h"
#include "Stage3.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "CollilsionMgr.h"
#include "BitmapMgr.h"

CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	BLOCK->Load_File(L"../Data/Blocks3.dat");
	MOBJ->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CKoopa>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(500,100));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(550, 100));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(600, 100));

	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(1500, 100));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(1550, 100));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(1600, 100));
	MSCROLL->ScrollClear();

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 150;
	m_tFrame.dwTime = GetTickCount();
}

void CStage3::Update()
{
	MOBJ->Update();
	BLOCK->Update();
}

void CStage3::Late_Update()
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

	Move_Frame();
}

void CStage3::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, 0, 0, 800, 600);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	HDC      hMemDC = CBitmapMgr::Get_Instance()->Find_Img(BOSSAXE);

	int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
		int(2000 + iScrollX), // 복사 받을 텍스처 위치 좌표 X
		int(505), // 복사 받을 텍스처 위치 좌표 Y
		int(32), // 텍스처 가로 사이즈
		int(32), // 텍스처 세로 사이즈
		hMemDC,   // 복사할 DC
		m_tFrame.iFrameStart * int(32 + 6.f),   // 비트맵 출력 좌표 X
		m_tFrame.iMotion * int(32 + 6.f),   // 비트맵 출력 좌표 Y
		int(32), // 복사할 비트맵 텍스처 가로 사이즈
		int(32), // 복사할 비트맵 텍스처 세로 사이즈
		RGB(1, 1, 1)); // 제거할 픽셀 색상
	
	//HDC hMemDC = MBITMAP->Find_Img(GOALFLAG);
	//GdiTransparentBlt(hDC,      // 복사 받을 최종 DC
	//	1500 + iScrollX, // 복사 받을 텍스처 위치 좌표 X
	//	210, // 복사 받을 텍스처 위치 좌표 Y
	//	48, // 텍스처 가로 사이즈
	//	334, // 텍스처 세로 사이즈
	//	hMemDC,   // 복사할 DC
	//	0,   // 비트맵 출력 좌표 X
	//	0,   // 비트맵 출력 좌표 Y
	//	48, // 복사할 비트맵 텍스처 가로 사이즈
	//	334, // 복사할 비트맵 텍스처 세로 사이즈
	//	RGB(1, 1, 1)); // 제거할 픽셀 색상



	list<CObj*>* playerlist = MOBJ->GetObjList(PLAYER);
	if (playerlist)
	{
		CObj* player = playerlist->front();
		if (player)
		{
			if (player->Get_Info().fX >= 1995)
			{
				MSCENE->Scene_Change(SC_STAGE4);
			}
			
		}
	}

	MOBJ->Render(hDC);
	BLOCK->Render(hDC);
}

void CStage3::Release()
{
	MOBJ->DeleteObject(PLAYER);
	MOBJ->Release();
	MOBJ->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
}

void CStage3::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}
