#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "Block.h"
#include "BlockMgr.h"

CMainGame::CMainGame()
	:m_dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{	
	m_hDC = GetDC(g_hWnd);
	
	LINEMGR->Initialize();

	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/GroundTile.bmp", L"GroundTile");

	// ������
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/BrickWall1.bmp", L"BrickOverWorld");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/BrickWall2.bmp", L"BrickUnderWorld");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/BrickWall3.bmp", L"BrickBossWorld");

	// ������
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/CrackedBlock1.bmp", L"TerrainOverWorld");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/CrackedBlock2.bmp", L"TerrainUnderWorld"); 
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/CrackedBlock3.bmp", L"TerrainBossWorld");

	// ����ǥ��
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/QuestionBlock1_48x16.bmp", L"QuestionOverWorld");
	CBitmapMgr::Get_Instance()->Insert_Bmp(L"../Image/Blocks/QuestionBlock2_48x16.bmp", L"QuestionUnderWorld");
	

	BLOCK->Initialize();
}

void CMainGame::Update(void)
{
	LINEMGR->Update();
	BLOCK->Update();

}

void CMainGame::Late_Update(void)
{
	LINEMGR->Late_Update();

}

void CMainGame::Render(void)
{
	HDC		hBackDC = CBitmapMgr::Get_Instance()->Find_Img(L"Back");
	HDC		hGroundDC = CBitmapMgr::Get_Instance()->Find_Img(L"Ground");

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

	//MSCENE->Render(hBackDC);
	LINEMGR->Render(hBackDC);
	BLOCK->Render(hBackDC);

	TextOut(hBackDC, 675, 100, L"Z: ����ǥ��", 8);
	TextOut(hBackDC, 675, 150, L"X: ������", 7);
	TextOut(hBackDC, 675, 200, L"C: ������", 7);
	TextOut(hBackDC, 675, 250, L"V: �����", 6);
	TextOut(hBackDC, 675, 300, L"A D: ȭ�齺ũ��", 10);
	TextOut(hBackDC, 675, 350, L"S: ����", 5);
	TextOut(hBackDC, 675, 400, L"L: �ε�", 5);
	TextOut(hBackDC, 675, 450, L"Q,W,E: �� ����", 12);
	switch(CBlockMgr::Get_Instance()->GetWorldID())
	{
	case OverWorld:
		TextOut(hBackDC, 675, 525, L"��������", 4);
		break;
	case UnderWorld:
		TextOut(hBackDC, 675, 525, L"�������", 4);
		break;
	case BossWorld:
		TextOut(hBackDC, 675, 525, L"��������", 4);
		break;
	case WorldEnd:
		TextOut(hBackDC, 675, 525, L"��������", 4);
		break;
	}

	switch (CBlockMgr::Get_Instance()->GetBlockID())
	{
	case QuestionBlock:
		TextOut(hBackDC, 675, 550, L"����ǥ��", 5);
		break;
	case BrickBlock:
		TextOut(hBackDC, 675, 550, L"������", 4);
		break;
	case TerrainBlock:
		TextOut(hBackDC, 675, 550, L"������", 4);
		break;
	case BlockEnd:
		TextOut(hBackDC, 675, 550, L"��Ͼ���", 4);
		break;
	}
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	/*MSCENE->Release();
	MSCENE->Destroy_Instance();*/
	/*OBJMGR->Release();
	OBJMGR->Destroy_Instance();*/
	LINEMGR->Release();
	LINEMGR->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
